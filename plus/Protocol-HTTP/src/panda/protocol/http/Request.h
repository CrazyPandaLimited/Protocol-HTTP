#pragma once
#include "Message.h"
#include "Response.h"
#include <panda/uri/URI.h>
#include <panda/memory.h>

namespace panda { namespace protocol { namespace http {

using panda::uri::URI;
using panda::uri::URISP;

struct Request : Message, AllocatedObject<Request> {
    enum class Method {OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT};

    struct Builder; template <class T = void> struct BuilderImpl;

    Method method;
    URISP  uri;

    Request () : method(Method::GET) {}

    Request (Method method, const URISP& uri, Header&& header = Header(), Body&& body = Body(), bool chunked = false, int http_version = 0) :
        Message(std::move(header), std::move(body), chunked, http_version), method(method), uri(uri)
    {}

    ResponseSP response () const { return create_response(); }

    std::vector<string> to_vector ();
    string              to_string ();

protected:
    ~Request () {} // restrict stack allocation

    virtual ResponseSP create_response () const { return make_iptr<Response>(); }

private:
    friend struct RequestParser;

    string _http_header (size_t);
};
using RequestSP = iptr<Request>;

template <class T>
struct Request::BuilderImpl : Message::Builder<T> {
    BuilderImpl () : _method(Request::Method::GET) {}

    T& method (Request::Method method) {
        _method = method;
        return this->self();
    }

    T& uri (const string& uri) {
        _uri = new URI(uri);
        return this->self();
    }

    T& uri (const URISP& uri) {
        _uri = uri;
        return this->self();
    }

    RequestSP build () {
        return new Request(_method, _uri, std::move(this->_headers), std::move(this->_body), this->_chunked, this->_http_version);
    }

protected:
    Request::Method _method;
    URISP           _uri;
};
struct Request::Builder : Request::BuilderImpl<Builder> {};

}}}
