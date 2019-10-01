#pragma once
#include "Message.h"

namespace panda { namespace protocol { namespace http {

struct Response : Message {
    struct Builder; template <class T> struct BuilderImpl;

    int    code;
    string message;

    Response () : code() {}
    Response (int code, const string& reason, Header&& header, Body&& body, const string& http_version, bool chunked = false);

    string full_message () { return panda::to_string(code) + " " + message; }

    std::vector<string> to_vector () const override;
    string              to_string () const override;

protected:
    ~Response () {}

private:
    string _http_header (size_t);
};
using ResponseSP = iptr<Response>;

template <class T>
struct Response::BuilderImpl : Message::Builder<T> {
    BuilderImpl () {}

    T& code (int code) {
        _code = code;
        return this->self();
    }

    T& reason (const string& reason) {
        _reason = reason;
        return this->self();
    }

    ResponseSP build () {
        return new Response(_code, _reason, std::move(this->_headers), std::move(this->_body), this->_http_version, this->_chunked);
    }

protected:
    int    _code;
    string _reason;
};
struct Response::Builder : Response::BuilderImpl<Builder> {};

}}}
