#include "RequestParser.h"

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <cstring>

#include <iostream>
#include <string>

#include <panda/string.h>
#include <panda/uri/URI.h>
#include <panda/log.h>

#include "MessageParser.h"
#include "Response.h"

namespace panda { namespace protocol { namespace http {

namespace {
    #define MACHINE_DATA
    #include "RequestParserGenerated.cc"
}

RequestParser::~RequestParser() { 
    _PDEBUG("dtor");
}

RequestParser::RequestParser(RequestFactorySP request_factory) : 
    MessageParser<RequestParser, Request>(request_factory->create(), http_request_parser_start),
    request_factory_(request_factory) {
    _PDEBUG("ctor");
}

RequestParser::Result RequestParser::reset_and_build_result(bool is_valid, size_t position, State state) {
    init();

    MessageSP result = current_message_;
    if(is_valid) {
        result->set_valid();
    }

    current_message_ = request_factory_->create();

    return {result, position, state};
}

RequestParser::ResultIterator RequestParser::parse(const string& buffer) {
    return ResultIterator(this, buffer);
}

RequestParser::Result RequestParser::parse_first(const string& buffer) {
    _PDEBUG("parsing [" << buffer << "]");

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
            return reset_and_build_result(true, position, state_);
        } else {
            size_t position = p - buffer_ptr;
            return {current_message_, position, state_};
        }
    }

    // generated parser logic
    #define MACHINE_EXEC
    #include "RequestParserGenerated.cc"
    
    size_t position = p - buffer_ptr;
    if(cs == http_request_parser_first_final) {
        if(state_ == State::in_body) {
            _PDEBUG("body not completed, mark: " << mark << " buffer: "<< marked_buffer_);
            return {current_message_, position, state_};
        }
        _PDEBUG("completed, mark: " << mark << " buffer: "<< marked_buffer_);
        return reset_and_build_result(true, position, state_);
    } else if(cs == http_request_parser_error) {
        _PDEBUG("error, mark: " << mark << " buffer: "<< marked_buffer_);
        return reset_and_build_result(false, position, state_);
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
        return {current_message_, position, state_};
    }    
}

}}} // namespace panda::protocol::http
