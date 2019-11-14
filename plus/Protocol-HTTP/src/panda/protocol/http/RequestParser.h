#pragma once
#include "Error.h"
#include "Request.h"
#include "MessageParser.h"
#include <panda/excepted.h>

namespace panda { namespace protocol { namespace http {

struct IRequestFactory {
    virtual RequestSP new_request () = 0;
};

struct RequestParser : MessageParser<Request> {
    struct Result {
        RequestSP       request;
        size_t          position = 0;
        State           state    = State::not_yet;
        std::error_code error;
    };

    struct IFactory {
        virtual RequestSP new_request () = 0;
    };

    RequestParser (IFactory* = nullptr);
    RequestParser (RequestParser&&) = default;

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

    IFactory* factory;

    RequestSP new_request () const { return factory ? factory->new_request() : make_iptr<Request>(); }

    Result build_result           (FinalFlag reset, size_t position);
    Result reset_and_build_result (size_t position, State state, std::error_code error = {});
};

}}}
