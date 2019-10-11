#pragma once
#include "Message.h"

namespace panda { namespace protocol { namespace http {

struct Request;

struct Response : Message {
    using State = Message::State;
    struct Builder; template <class T> struct BuilderImpl;

    int    code;
    string message;

    Response () : code() {}
    Response (int code, const string& message, Header&& header, Body&& body, const string& http_version, bool chunked = false);

    string full_message () { return panda::to_string(code) + " " + message; }

    std::vector<string> to_vector (const Request* = nullptr);
    string              to_string (const Request* = nullptr);

protected:
    ~Response () {}

private:
    friend struct ResponseParser;

    string _http_header (const Request*, size_t);
};
using ResponseSP = iptr<Response>;

template <class T>
struct Response::BuilderImpl : Message::Builder<T> {
    BuilderImpl () {}

    T& code (int code) {
        _code = code;
        return this->self();
    }

    T& message (const string& message) {
        _message = message;
        return this->self();
    }

    ResponseSP build () {
        return new Response(_code, _message, std::move(this->_headers), std::move(this->_body), this->_http_version, this->_chunked);
    }

protected:
    int    _code;
    string _message;
};
struct Response::Builder : Response::BuilderImpl<Builder> {};

}}}
