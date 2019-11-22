#pragma once
#include "Error.h"
#include "Parser.h"

namespace panda { namespace protocol { namespace http {

struct ResponseParser : Parser {
    struct Result {
        ResponseSP response;
        size_t     position;
    };

    ResponseParser ();
    ResponseParser (ResponseParser&&) = default;

    const RequestSP& context_request () const { return _context_request; }

    void set_context_request (const RequestSP& request) {
        if (_context_request) throw ParserError("can't set another context request until response is done");
        _context_request = request;
    }

    Result parse (const string& buffer);

    ResponseSP parse_shift (string& s) {
        auto result = parse(s);
        s.offset(result.position);
        return result.response;
    }

    ResponseSP eof ();

    void reset () { _reset(false); }

private:
    RequestSP _context_request;

    void _reset (bool keep_context);

};

}}}
