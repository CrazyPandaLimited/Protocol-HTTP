#pragma once
#include "Error.h"
#include "Request.h"
#include "Response.h"
#include "MessageParser.h"
#include <panda/excepted.h>

namespace panda { namespace protocol { namespace http {

struct ResponseParser : MessageParser<Response> {
    struct Result {
        RequestSP       request;
        ResponseSP      response;
        size_t          position = 0;
        State           state    = State::not_yet;
        std::error_code error;
    };
    using ResultSP = iptr<Result>;

    ResponseParser ();

    virtual ~ResponseParser () {}

    const RequestSP& request () const { return _request; }

    void set_request (const RequestSP& request) {
        if (_request) throw ParserError("can't set another request until response is done");
        _request = request;
    }

    Result parse (const string& buffer);

    Result parse_shift (string& s) {
        auto result = parse(s);
        s.offset(result.position);
        result.position = 0;
        return result;
    }

    Result eof ();

    void reset ();

private:
    ResponseSP create_message ();

    Result build_result           (FinalFlag reset, size_t position);
    Result reset_and_build_result (size_t position, const std::error_code& error = {});

    RequestSP _request;
};

}}}
