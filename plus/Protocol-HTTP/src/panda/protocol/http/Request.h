#pragma once
#include "Response.h"
#include <panda/memory.h>
#include <panda/uri/URI.h>

namespace panda { namespace protocol { namespace http {

using panda::uri::URI;
using panda::uri::URISP;

struct Request : Message, AllocatedObject<Request> {
    enum class Method {OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT};

    struct Builder; template <class, class> struct BuilderImpl;
    using Cookies = Fields<string, true, 3>;

    Method  method = Method::GET;
    URISP   uri;
    Cookies cookies;

    Request () {}

    Request (Method method, const URISP& uri, Headers&& header = Headers(), Body&& body = Body(), bool chunked = false, int http_version = 0) :
        Message(std::move(header), std::move(body), chunked, http_version), method(method), uri(uri)
    {}

    bool expects_continue () const;

    std::vector<string> to_vector ();
    string              to_string ();

    virtual ResponseSP new_response () const { return make_iptr<Response>(); }

    void parse_cookie (const string& buffer);

protected:
    ~Request () {} // restrict stack allocation

private:
    friend struct RequestParser;

    string _http_header (size_t);


};
using RequestSP = iptr<Request>;

template <class T, class R>
struct Request::BuilderImpl : Message::Builder<T, R> {
    using Message::Builder<T, R>::Builder;

    T& method (Request::Method method) {
        this->_message->method = method;
        return this->self();
    }

    T& uri (const string& uri) {
        this->_message->uri = new URI(uri);
        return this->self();
    }

    T& uri (const URISP& uri) {
        this->_message->uri = uri;
        return this->self();
    }

    T& cookie (const string& name, const string& value) {
        this->_message->cookies.add(name, value);
        return this->self();
    }
};

struct Request::Builder : Request::BuilderImpl<Builder, RequestSP> {
    Builder () : BuilderImpl(new Request()) {}
};

}}}
