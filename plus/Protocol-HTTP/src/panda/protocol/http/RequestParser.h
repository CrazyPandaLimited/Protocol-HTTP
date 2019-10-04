#pragma once
#include "Error.h"
#include "Request.h"
#include "MessageParser.h"
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
        excepted<State, std::error_code> state;
    };
    using ResultSP = iptr<Result>;

    RequestParser (const RequestFactorySP& request_factory = {});

    virtual ~RequestParser () {}

    Result parse (const string&);

    Result parse_shift (string& s) {
        auto result = parse(s);
        s.offset(result.position);
        result.position = 0;
        return result;
    }

    void reset ();

private:
    using MessageParser::FinalFlag;

    RequestFactorySP request_factory;

    RequestSP new_request () const { return request_factory ? request_factory->create() : make_iptr<Request>(); }

    Result build_result           (FinalFlag reset, size_t position);
    Result reset_and_build_result (size_t position, const excepted<State, std::error_code>& state);
};

}}}
