#pragma once
#include "Error.h"
#include "Parser.h"

namespace panda { namespace protocol { namespace http {

struct IRequestFactory {
    virtual RequestSP new_request () = 0;
};

struct RequestParser : Parser {
    struct Result {
        RequestSP request;
        size_t    position;
    };

    struct IFactory {
        virtual RequestSP new_request () = 0;
    };

    RequestParser (IFactory* = nullptr);
    RequestParser (RequestParser&&) = default;

    Result parse (const string&);

    RequestSP parse_shift (string& s) {
        auto result = parse(s);
        s.offset(result.position);
        return result.request;
    }

    void reset ();

private:
    IFactory* factory;

    RequestSP new_request () const { return factory ? factory->new_request() : make_iptr<Request>(); }
};

}}}
