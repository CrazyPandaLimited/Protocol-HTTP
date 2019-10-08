#include "RequestParser.h"
#include "parser.icc"

namespace panda { namespace protocol { namespace http {

namespace {
    #define MACHINE_DATA
    #include "RequestParserGenerated.icc"
}

RequestParser::RequestParser (IRequestFactory* fac) :
    MessageParser<Request>(fac ? fac->create_request() : make_iptr<Request>(), http_request_parser_start),
    request_factory(fac)
{}

RequestParser::Result RequestParser::parse (const string& buffer) {
    // pointer to current buffer, used by LEN, PTR_TO defines above
    const char *buffer_ptr = buffer.data();

    // start parsing from the beginning pointer
    const char *p = buffer_ptr;
    // to the end pointer
    const char *pe = buffer_ptr + buffer.size();
    //
    const char *eof = pe;

    if (state == State::in_body) {
        bool is_completed = process_body(buffer, p, pe);
        if (is_completed) {
            size_t position = p - buffer_ptr;
            return build_result(FinalFlag::RESET, position);
        } else {
            size_t position = p - buffer_ptr;
            return build_result(FinalFlag::CONTINUE, position);
        }
    }

    // generated parser logic
    #define MACHINE_EXEC
    #include "RequestParserGenerated.icc"

    size_t position = p - buffer_ptr;
    if (state == State::error) {
        return reset_and_build_result(position, make_unexpected(errc::semantic_error));
    } else if (cs == http_request_parser_first_final) {
        if(state == State::in_body) {
            return build_result(FinalFlag::CONTINUE, position);
        }
        return build_result(FinalFlag::RESET, position);
    } else if (cs == http_request_parser_error) {
        return reset_and_build_result(position, make_unexpected(errc::lexical_error));
    } else {
        // append into current marked buffer everything which is unparsed yet
        if (marked) {
            marked_buffer.append(buffer.substr(mark));
            // current block is over, but we are still copying the next block from the beginning into our buffer
            mark = 0;
        }
        return build_result(FinalFlag::CONTINUE, position);
    }
}

void RequestParser::reset () {
    MessageParser::reset();
    current_message = new_request();
}

RequestParser::Result RequestParser::reset_and_build_result (size_t position, const excepted<State, std::error_code>& state) {
    MessageSP result = current_message;
    reset();
    return {result, position, state};
}

RequestParser::Result RequestParser::build_result (FinalFlag flag, size_t position) {
    if (max_message_size != SIZE_UNLIMITED && current_message->buf_size() > max_message_size) {
        return reset_and_build_result(position, make_unexpected(errc::message_too_large));
    }

    // TODO: body->length() is linear, we need cache
    auto length = current_message->body.length();
    if (max_body_size == SIZE_PROHIBITED && length > 0) {
        return reset_and_build_result(position, make_unexpected(errc::unexpected_body));
    } else if (max_body_size != SIZE_UNLIMITED && length > max_body_size) {
        return reset_and_build_result(position, make_unexpected(errc::body_too_large));
    } else if (flag == FinalFlag::RESET) {
        return reset_and_build_result(position, state);
    } else {
        return {current_message, position, state};
    }
}

}}}
