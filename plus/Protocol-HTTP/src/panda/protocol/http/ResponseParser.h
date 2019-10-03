#pragma once
#include "Request.h"
#include "Response.h"
#include "ParserError.h"
#include "MessageParser.h"
#include <deque>
#include <panda/excepted.h>

namespace panda { namespace protocol { namespace http {

struct ResponseParser : MessageParser<Response> {
    struct Result {
        RequestSP  request;
        ResponseSP response;
        size_t     position;
        excepted<State, ParserError> state;
    };
    using ResultSP = iptr<Result>;

    ResponseParser ();

    virtual ~ResponseParser () {}

    void append_request (const RequestSP& request);

    Result parse (const string& buffer);
    Result eof   ();

    void reset ();

    bool no_pending_requests () const { return requests.empty(); }

private:
    ResponseSP create_message ();

    Result build_result           (FinalFlag reset, size_t position);
    Result reset_and_build_result (size_t position, const excepted<State, ParserError>& state);

    std::deque<RequestSP> requests;
};

}}}
