#include "RequestParser.h"

namespace panda { namespace protocol { namespace http {

namespace {
    #define MACHINE_DATA
    #include "parser.icc"
}

RequestParser::RequestParser (IFactory* fac) : MessageParser<Request>(), factory(fac) {
    reset();
}

void RequestParser::reset () {
    MessageParser::reset();
    cs      = http_parser_en_request;
    message = new_request();
}

size_t RequestParser::machine_exec (const string& buffer, size_t off) {
    const char* ps = buffer.data();
    const char* p  = ps + off;
    const char* pe = ps + buffer.size();

    #define MACHINE_EXEC
    #include "parser.icc"

    return p - ps;
}

RequestParser::Result RequestParser::parse (const string& buffer) {
    auto   len = buffer.length();
    size_t pos = 0;

    while (pos != len) switch (state) {
        case State::headers:
            pos = machine_exec(buffer, pos);
            if (cs == http_parser_error) return finish(pos, State::error, errc::lexical_error);

            headers_so_far += pos;
            if (headers_so_far > max_headers_size) return finish(pos, State::error, errc::headers_too_large);

            if (cs < http_parser_first_final) {
                if (mark) {
                    acc = buffer.substr(mark - ps, p - mark);
                    mark = nullptr;
                }
                return {message, pos, state, {}};
            }

            if (message->chunked) {
                state = State::chunk;
                cs    = http_parser_en_first_chunk;
            }
            else if (has_content_length && content_length > 0) {
                if (content_length > max_body_size) {
                    return finish(position, State::error, max_body_size ? errc::body_too_large : errc::unexpected_body);
                }
                state = State::body;
            }
            else {
                return finish(pos, State::done);
            }
            continue;

        case State::body:
            auto left = content_length - body_so_far;
            if (pe - p >= left) {
                message->body.parts.push_back(buffer.substr(pos, left));
                return finish(off + left, State::done);
            }
            else {
                message->body.parts.push_back(buffer.substr(pos));
                return {message, len, state, {}};
            }

        case State::chunk:
            pos = machine_exec(buffer, pos);
            if (cs == http_parser_error) return finish(pos, State::error, errc::lexical_error);

            if (cs < http_parser_first_final) {
                if (mark) {
                    acc = buffer.substr(mark - ps, p - mark);
                    mark = nullptr;
                }
                return {message, pos, state, {}};
            }

            if (!chunk_length) { // final chunk
                state = State::chunk_trailer;
                cs    = http_parser_en_chunk_trailer;
                continue;
            }

            body_so_far += chunk_length;
            if (body_so_far > max_body_size) {
                return finish(position, State::error, max_body_size ? errc::body_too_large : errc::unexpected_body);
            }

            chunk_so_far = 0;
            state = State::chunk_body;
            cs    = http_parser_en_chunk_body;

        case State::chunk_body:
            auto left = chunk_length - chunk_so_far;
            auto have = len - off;

            if (have >= left) {
                message->body.parts.push_back(buffer.substr(off, left));
                off += left;
                state = State::chunk;
                cs    = http_parser_en_chunk;
                continue;
            } else {
                message->body.parts.push_back(buffer.substr(off));
                chunk_so_far += have;
                return {message, len, state, {}};
            }

        case State::chunk_trailer:
            pos = machine_exec(buffer, pos);
            if (cs == http_parser_error) return finish(pos, State::error, errc::lexical_error);

            if (cs < http_parser_first_final) {
                if (mark) {
                    acc = buffer.substr(mark - ps, p - mark);
                    mark = nullptr;
                }
                return {message, pos, state, {}};
            }

            return finish(pos, State::done);
    }
}

RequestParser::Result RequestParser::finish (size_t position, State state, std::error_code error) {
    MessageSP msg = message;
    reset();
    return {msg, position, state, this->error ? this->error : error};
}

}}}
