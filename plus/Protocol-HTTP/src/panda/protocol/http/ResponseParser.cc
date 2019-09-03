#include "ResponseParser.h"

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <cstring>

#include <iostream>

#include <panda/string.h>
#include <panda/log.h>

#include "MessageParser.h"
#include "ParserError.h"

namespace panda { namespace protocol { namespace http {

namespace {
    #define MACHINE_DATA
    #include "ResponseParserGenerated.cc"
}

ResponseParser::~ResponseParser() {
    _PDEBUG("dtor");
}

ResponseParser::ResponseParser() :
    MessageParser<ResponseParser, Response>(nullptr, http_response_parser_start) {
    _PDEBUG("ctor");
}

ResponseParser::Result ResponseParser::reset_and_build_result(bool is_valid, size_t position, const excepted<State, ParserError>& state) {
    init();

    MessageSP message = current_message_;
    if(is_valid) {
        message->set_valid();
    }

    RequestSP request = requests_.back();

    requests_.pop_back();

    current_message_ = nullptr;

    return {request, message, position, state};
}

ResponseParser::Result ResponseParser::build_result(FinalFlag flag, size_t position) {
    if (max_message_size != SIZE_UNLIMITED && current_message_->buf_size() > max_message_size) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("message is bigger than max_message_size")));
    }

    // TODO: body->length() is linear, we need cache
    auto length = current_message_->body->length();
    if (max_body_size == SIZE_PROHIBITED && length > 0) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("body is prohibited")));
    } else  if (max_body_size != SIZE_UNLIMITED && length > max_body_size) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("body is bigger than max_body_size")));
    } else if (flag == FinalFlag::RESET) {
        return reset_and_build_result(true, position, state_);
    } else {
        return {requests_.back(), current_message_, position, state_};
    }
}

ResponseSP ResponseParser::create_message() {
    _PDEBUG("create_message");
    // we need requests to parse some responses correctly (for example HEAD response)
    // so something is terribly wrong if we have no corresponding request
    if(requests_.empty()) {
        throw ParserError("Cannot create response as there are no corresponding request");
    }

    if(current_message_ && current_message_->code) {
        throw ParserError("Programming error, there is incomplete message in the parser");
    }

    current_message_ = requests_.back()->response();
    return current_message_;
}

void ResponseParser::append_request(iptr<Request> request) {
    _PDEBUG("append_request");
    requests_.emplace_front(request);
}

ResponseSP ResponseParser::message() {
    if(!current_message_) {
        if(requests_.empty()) {
            throw ParserError("Cannot get response as there are no corresponding request");
        }
        current_message_ = requests_.back()->response();
    }

    return current_message_;
}

ResponseParser::ResultIterator ResponseParser::parse(const string& buffer) {
    return ResultIterator(this, buffer);
}

ResponseParser::Result ResponseParser::parse_first(const string& buffer) {
    _PDEBUG("parsing [" << buffer << "]");

    if(requests_.empty()) {
        if(buffer.empty()) {
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

    if(state_ == State::in_body) {
        bool is_completed = process_body(buffer, p, pe);
        if(is_completed) {
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

    if (state_ == State::error) {
        return reset_and_build_result(false, position, make_unexpected(ParserError("http parsing error")));
    } else if(cs == http_response_parser_first_final) {
        if(state_ == State::in_body) {
            _PDEBUG("body not completed, mark: " << mark << " buffer: "<< marked_buffer_);
            return build_result(FinalFlag::CONTINUE, position);
        }
        _PDEBUG("completed, mark: " << mark << " buffer: "<< marked_buffer_);
        return build_result(FinalFlag::RESET, position);
    } else if(cs == http_response_parser_error) {
        _PDEBUG("error, mark: " << mark << " buffer: "<< marked_buffer_);
        return reset_and_build_result(false, position, make_unexpected(ParserError("http parsing error")));
    } else {
        // append into current marked buffer everything which is unparsed yet
        if(marked) {
            _PDEBUG("not completed, mark: " << mark);
            marked_buffer_.append(buffer.substr(mark));
            // current block is over, but we are still copying the next block from the beginning into our buffer
            mark = 0;
        } else {
            _PDEBUG("not completed");
        }
        //_PDEBUG("not completed, mark: " << mark << " buffer: "<< marked_buffer_);
        return build_result(FinalFlag::CONTINUE, position);
    }
}

}}} // namespace panda::protocol::http
