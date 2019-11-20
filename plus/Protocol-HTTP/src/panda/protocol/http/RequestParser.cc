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

RequestParser::Result RequestParser::parse (const string& _buffer) {
    auto   len = buffer.length();
    size_t pos = 0;

    while (pos != len) {
        switch (state) {
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

                //state = State::got_header;
                if (message->chunked) {
                    state = State::chunk_start;
                    cs    = http_parser_chunk_start;
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
                auto off = p - ps;
                if (pe - p >= left) {
                    message->body.parts.push_back(buffer.substr(off, left));
                    return finish(off + left, State::done);
                }
                else {
                    message->body.parts.push_back(buffer.substr(off));
                    return {message, buffer.length(), state, {}};
                }
            case State::chunk_start:

        }
    }

//    if (state == State::in_body) {
//        bool is_completed = process_body(buffer, p, pe);
//        if (is_completed) {
//            size_t position = p - buffer_ptr;
//            return build_result(FinalFlag::RESET, position);
//        } else {
//            size_t position = p - buffer_ptr;
//            return build_result(FinalFlag::CONTINUE, position);
//        }
//    }
//
//    // generated parser logic
//
//    size_t position = p - buffer_ptr;
//    if (state == State::error) {
//        return reset_and_build_result(position, state, errc::semantic_error);
//    } else if (cs == http_request_parser_first_final) {
//        if(state == State::in_body) {
//            return build_result(FinalFlag::CONTINUE, position);
//        }
//        return build_result(FinalFlag::RESET, position);
//    } else if (cs == http_request_parser_error) {
//        state = State::error;
//        return reset_and_build_result(position, state, errc::lexical_error);
//    } else {
//        // append into current marked buffer everything which is unparsed yet
//        if (marked) {
//            marked_buffer.append(buffer.substr(mark));
//            // current block is over, but we are still copying the next block from the beginning into our buffer
//            mark = 0;
//        }
//        return build_result(FinalFlag::CONTINUE, position);
//    }
}

RequestParser::Result RequestParser::finish (size_t position, State state, std::error_code error) {
    MessageSP msg = message;
    reset();
    return {msg, position, state, error};
}

RequestParser::Result RequestParser::build_result (FinalFlag flag, size_t position) {
    if (headers_so_far > max_headers_size) {
        return reset_and_build_result(position, state, errc::headers_too_large);
    }

    if (state >= State::got_header) {
        if (has_content_len) {
            if (content_len > max_body_size) {
                auto err = max_body_size ? errc::body_too_large : errc::unexpected_body;
                return reset_and_build_result(position, state, err);
            }
        }
        else if (body_so_far > max_body_size) {
            auto err = max_body_size ? errc::body_too_large : errc::unexpected_body;
            return reset_and_build_result(position, state, err);
        }
    }

    if (flag == FinalFlag::RESET) {
        return reset_and_build_result(position, state);
    } else {
        return {current_message, position, state, {}};
    }
}

}}}
