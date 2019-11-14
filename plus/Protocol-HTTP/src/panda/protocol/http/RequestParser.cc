#include "RequestParser.h"
#include "parser.icc"

namespace panda { namespace protocol { namespace http {

namespace {
    #define MACHINE_DATA
    #include "RequestParserGenerated.icc"
}

RequestParser::RequestParser (IFactory* fac) :
    MessageParser<Request>(fac ? fac->new_request() : make_iptr<Request>(), http_request_parser_start), factory(fac)
{}

RequestParser::Result RequestParser::parse (const string& buffer) {
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
    #include "RequestParserGenerated.icc"

    size_t position = p - buffer_ptr;
    if (state == State::error) {
        return reset_and_build_result(position, state, errc::semantic_error);
    } else if (cs == http_request_parser_first_final) {
        if(state == State::in_body) {
            return build_result(FinalFlag::CONTINUE, position);
        }
        return build_result(FinalFlag::RESET, position);
    } else if (cs == http_request_parser_error) {
        state = State::error;
        return reset_and_build_result(position, state, errc::lexical_error);
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

RequestParser::Result RequestParser::reset_and_build_result (size_t position, State state, std::error_code error) {
    MessageSP result = current_message;
    reset();
    return {result, position, state, error};
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
