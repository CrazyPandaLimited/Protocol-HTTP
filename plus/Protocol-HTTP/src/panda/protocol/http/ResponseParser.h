#pragma once
#include "Request.h"
#include "Response.h"
#include "ParserError.h"
#include "MessageParser.h"
#include "MessageIterator.h"
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
    using ResultIterator = MessageIterator<ResponseParser, Result>;

    ResponseParser ();

    virtual ~ResponseParser () {}

    void append_request (const RequestSP& request);

    Result parse_first (const string& buffer);
    ResultIterator parse (const string& buffer);

    bool no_pending_requests () const { return requests.empty(); }

private:
    ResponseSP create_message ();

    Result build_result           (FinalFlag reset, size_t position);
    Result reset_and_build_result (bool is_valid, size_t position, const excepted<State, ParserError>& state);

    std::deque<RequestSP> requests;
};
using ResponseParserSP = iptr<ResponseParser>;

}}}
