#pragma once
#include "Message.h"
#include <panda/memory.h>

namespace panda { namespace protocol { namespace http {

struct Request;

struct Response : Message, AllocatedObject<Response> {
    struct Builder; template <class T> struct BuilderImpl;

    int    code;
    string message;

    Response () : code() {}

    Response (int code, Header&& header = Header(), Body&& body = Body(), bool chunked = false, int http_version = 0, const string& message = {}) :
        Message(std::move(header), std::move(body), chunked, http_version), code(code), message(message)
    {}

    string full_message () { return panda::to_string(code) + " " + (message ? message : message_for_code(code)); }

    std::vector<string> to_vector (const Request* = nullptr);
    string              to_string (const Request* = nullptr);

    static string message_for_code (int code);

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
        return new Response(_code, std::move(this->_headers), std::move(this->_body), this->_chunked, this->_http_version, _message);
    }

protected:
    int    _code = 0;
    string _message;
};
struct Response::Builder : Response::BuilderImpl<Builder> {};

}}}
