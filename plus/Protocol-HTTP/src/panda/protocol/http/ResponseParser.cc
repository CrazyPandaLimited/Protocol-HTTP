#include "ResponseParser.h"
#include "parser.icc"

namespace panda { namespace protocol { namespace http {

namespace {
    #define MACHINE_DATA
    #include "ResponseParserGenerated.cc"
}

ResponseParser::ResponseParser () : MessageParser<Response>(nullptr, http_response_parser_start) {}

void ResponseParser::append_request (const RequestSP& request) {
    requests.emplace_front(request);
}

ResponseSP ResponseParser::create_message () {
    // we need requests to parse some responses correctly (for example HEAD response)
    // so something is terribly wrong if we have no corresponding request
    assert(!current_message);
    if (requests.empty()) throw ParserError("Cannot create response as there are no corresponding request");
    current_message = requests.back()->response();
    return current_message;
}

ResponseParser::ResultIterator ResponseParser::parse (const string& buffer) {
    return ResultIterator(this, buffer);
}

ResponseParser::Result ResponseParser::parse_first (const string& buffer) {
    if (requests.empty()) {
        if (buffer.empty()) {
            // stop iteration
            return { nullptr, nullptr, 0, State::not_yet };
        } else {
            throw ParserError("Cannot parse message as there are no corresponding request");
        }
    }

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
    #include "ResponseParserGenerated.cc"

    size_t position = p - buffer_ptr;

    if (state == State::error) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("http parsing error")));
    } else if (cs == http_response_parser_first_final) {
        if (state == State::in_body) {
            return build_result(FinalFlag::CONTINUE, position);
        }
        return build_result(FinalFlag::RESET, position);
    } else if (cs == http_response_parser_error) {
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

ResponseParser::Result ResponseParser::reset_and_build_result (bool is_valid, size_t position, const excepted<State, ParserError>& state) {
    init();

    MessageSP message = current_message;
    if (is_valid) message->set_valid();

    RequestSP request = requests.back();
    requests.pop_back();

    current_message = nullptr;

    return {request, message, position, state};
}

ResponseParser::Result ResponseParser::build_result (FinalFlag flag, size_t position) {
    if (max_message_size != SIZE_UNLIMITED && current_message->buf_size() > max_message_size) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("message is bigger than max_message_size")));
    }

    // TODO: body->length() is linear, we need cache
    auto length = current_message->body->length();
    if (max_body_size == SIZE_PROHIBITED && length > 0) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("body is prohibited")));
    } else  if (max_body_size != SIZE_UNLIMITED && length > max_body_size) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("body is bigger than max_body_size")));
    } else if (flag == FinalFlag::RESET) {
        return reset_and_build_result(true, position, state);
    } else {
        return {requests.back(), current_message, position, state};
    }
}

}}}
