#include "RequestParser.h"
#include "parser.icc"

namespace panda { namespace protocol { namespace http {

namespace {
    #define MACHINE_DATA
    #include "RequestParserGenerated.cc"
}

RequestParser::RequestParser (const RequestFactorySP& fac) :
    MessageParser<Request>(fac ? fac->create() : make_iptr<Request>(), http_request_parser_start),
    request_factory(fac)
{}

RequestParser::ResultIterator RequestParser::parse (const string& buffer) {
    return ResultIterator(this, buffer);
}

RequestParser::Result RequestParser::parse_first (const string& buffer) {
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
    #include "RequestParserGenerated.cc"

    size_t position = p - buffer_ptr;
    if (state == State::error) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("http parsing error")));
    } else if (cs == http_request_parser_first_final) {
        if(state == State::in_body) {
            return build_result(FinalFlag::CONTINUE, position);
        }
        return build_result(FinalFlag::RESET, position);
    } else if (cs == http_request_parser_error) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("http parsing error")));
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

RequestParser::Result RequestParser::reset_and_build_result (bool is_valid, size_t position, const excepted<State, ParserError>& state) {
    init();

    MessageSP result = current_message;
    if (is_valid) result->set_valid();

    current_message = new_request();

    return {result, position, state};
}

RequestParser::Result RequestParser::build_result (FinalFlag flag, size_t position) {
    if (max_message_size != SIZE_UNLIMITED && current_message->buf_size() > max_message_size) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("message is bigger than max_message_size")));
    }

    // TODO: body->length() is linear, we need cache
    auto length = current_message->body->length();
    if (max_body_size == SIZE_PROHIBITED && length > 0) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("body is prohibited")));
    } else if (max_body_size != SIZE_UNLIMITED && length > max_body_size) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("body is bigger than max_body_size")));
    } else if (flag == FinalFlag::RESET) {
        return reset_and_build_result(true, position, state);
    } else {
        return {current_message, position, state};
    }
}



}}}
