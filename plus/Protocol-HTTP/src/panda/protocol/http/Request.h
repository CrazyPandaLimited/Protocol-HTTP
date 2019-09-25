#pragma once
#include "Message.h"
#include "Response.h"
#include <panda/uri/URI.h>

namespace panda { namespace protocol { namespace http {

using panda::uri::URI;
using panda::uri::URISP;

struct Request : Message {
    enum class Method {
        OPTIONS,
        GET,
        HEAD,
        POST,
        PUT,
        DELETE,
        TRACE,
        CONNECT,
    };

    Method method;
    URISP  uri;

    Request () {}
    Request (Method method, const URISP& uri, Header&& header, const BodySP& body, const string& http_version);

    ResponseSP response () const { return create_response(); }

    std::ostream& print (std::ostream&) const override;

protected:
    virtual ~Request() {} // restrict stack allocation

    virtual ResponseSP create_response () const { return make_iptr<Response>(); }

private:
    Request (const Request&) = delete;
    Request& operator= (const Request&) = delete;
};
using RequestSP = iptr<Request>;

inline const char* to_string (Request::Method rm) {
    using Method = Request::Method;
    switch (rm) {
        case Method::OPTIONS : return "OPTIONS";
        case Method::GET     : return "GET";
        case Method::HEAD    : return "HEAD";
        case Method::POST    : return "POST";
        case Method::PUT     : return "PUT";
        case Method::DELETE  : return "DELETE";
        case Method::TRACE   : return "TRACE";
        case Method::CONNECT : return "CONNECT";
        default: return "[UNKNOWN]";
    }
}

std::ostream& operator<< (std::ostream& os, const RequestSP& ptr);

std::vector<string> to_vector(Request* request_ptr);

}}}
