#pragma once
#include "Request.h"
#include "ParserError.h"
#include "MessageParser.h"
#include "MessageIterator.h"
#include <panda/excepted.h>

namespace panda { namespace protocol { namespace http {

struct RequestFactory : virtual Refcnt {
    virtual RequestSP create () const = 0;
};
using RequestFactorySP = iptr<RequestFactory>;

struct RequestParser : MessageParser<Request> {
    struct Result {
        RequestSP request;
        size_t    position;
        excepted<State, ParserError> state;
    };
    using ResultSP = iptr<Result>;
    using ResultIterator = MessageIterator<RequestParser, Result>;

    RequestParser (const RequestFactorySP& request_factory = {});

    virtual ~RequestParser () {}

    Result parse_first (const string& buffer);
    ResultIterator parse (const string& buffer);

private:
    using MessageParser::FinalFlag;

    RequestFactorySP request_factory;

    RequestSP new_request () const { return request_factory ? request_factory->create() : make_iptr<Request>(); }

    Result build_result           (FinalFlag reset, size_t position);
    Result reset_and_build_result (bool is_valid, size_t position, const excepted<State, ParserError>& state);
};
using RequestParserSP = iptr<RequestParser>;

}}}
