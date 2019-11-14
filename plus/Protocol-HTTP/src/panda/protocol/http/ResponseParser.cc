#include "ResponseParser.h"
#include "parser.icc"

namespace panda { namespace protocol { namespace http {

namespace {
    #define MACHINE_DATA
    #include "ResponseParserGenerated.icc"
}

static void throw_no_request () { throw ParserError("Cannot create response as there are no corresponding request"); }

ResponseParser::ResponseParser () : MessageParser<Response>(nullptr, http_response_parser_start) {}

ResponseSP ResponseParser::create_message () {
    // we need requests to parse some responses correctly (for example HEAD response)
    // so something is terribly wrong if we have no corresponding request
    assert(!current_message);
    if (!_request) throw_no_request();
    current_message = _request->new_response();
    return current_message;
}

ResponseParser::Result ResponseParser::eof () {
    if (!_request) return {};
    if (current_message && !current_message->keep_alive() && !content_len && !current_message->chunked && state >= State::got_header) {
        state = State::done;
        return build_result(FinalFlag::RESET, 0);
    } else {
        return reset_and_build_result(0, errc::unexpected_eof);
    }
}

ResponseParser::Result ResponseParser::parse (const string& buffer) {
    if (!_request) {
        if (buffer.empty()) return { nullptr, nullptr, 0, State::not_yet, {} }; // stop iteration
        throw_no_request();
    }

    const char* buffer_ptr = buffer.data(); // pointer to current buffer, used by LEN, PTR_TO defines above
    const char* p          = buffer_ptr; // start parsing from the beginning pointer
    const char* pe         = buffer_ptr + buffer.size(); // to the end pointer
    //const char* eof        = pe;

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
    #include "ResponseParserGenerated.icc"

    size_t position = p - buffer_ptr;

    if (state == State::error) {
        return reset_and_build_result(position, errc::semantic_error);
    } else if (cs == http_response_parser_first_final) {
        if (state == State::in_body) {
            return build_result(FinalFlag::CONTINUE, position);
        }
        return build_result(FinalFlag::RESET, position);
    } else if (cs == http_response_parser_error) {
        state = State::error;
        return reset_and_build_result(position, errc::lexical_error);
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

void ResponseParser::reset () {
    MessageParser::reset();
    _request.reset();
}

ResponseParser::Result ResponseParser::reset_and_build_result (size_t position, const std::error_code& error) {
    //printf("ResponseParser::reset_and_build_result\n");
    State real_state = state; // state will be reset in MessageParser::reset;
    auto res = current_message;
    auto req = _request;

    if (res && res->code == 100 && !error) {
        if (!req->expects_continue()) {
            _request.reset();
            MessageParser::reset();
            return {req, res, position, State::error, errc::unexpected_continue};
        }
    }
    else _request.reset();

    MessageParser::reset();
    return {req, res, position, real_state, error};
}

ResponseParser::Result ResponseParser::build_result (FinalFlag flag, size_t position) {
    if (headers_so_far > max_headers_size) {
        return reset_and_build_result(position, errc::headers_too_large);
    }

    if (state >= State::got_header) {
        if (has_content_len) {
            if (content_len > max_body_size) {
                auto err = max_body_size ? errc::body_too_large : errc::unexpected_body;
                return reset_and_build_result(position, err);
            }
        }
        else if (body_so_far > max_body_size) {
            auto err = max_body_size ? errc::body_too_large : errc::unexpected_body;
            return reset_and_build_result(position, err);
        }
    }

    if (flag == FinalFlag::RESET) {
        return reset_and_build_result(position);
    } else {
        return {_request, current_message, position, state, {}};
    }
}

}}}
