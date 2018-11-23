#pragma once

#include <panda/string.h>
#include <panda/refcnt.h>
#include <panda/uri/URI.h>

#include "Message.h"
#include "Defines.h"

namespace panda { namespace protocol { namespace http {

// Host field builder
inline string to_host(URISP uri) {
    if(uri->port() == 80) {
        return uri->host();
    } else {
        return uri->host() + ":" + to_string(uri->port());
    }
}

class Request : public Message {
public:
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

    Request();
    
    Request(Method method, URISP uri, HeaderSP header, BodySP body, const string& http_version);

    Method method() const {
        return method_;
    }
    
    void method(Method method) {
        method_ = method;
    }

    URISP uri() const {
        return uri_;
    }
    
    void uri(URISP uri) {
        uri_ = uri;
    }

    std::ostream& print(std::ostream& os) const override; 
    
    ResponseSP response() const;
    
protected:
    // restrict stack allocation
    virtual ~Request();
    
    virtual ResponseSP create_response() const; 

private:
    // disable copying as we disabled stack usage
    Request(const Request&) = delete;
    Request& operator=(const Request&) = delete;
    
protected:
    Method method_;
    URISP uri_;
};

inline
const char* to_string(Request::Method rm) {
    switch (rm) {
        case Request::Method::OPTIONS: return "OPTIONS";
        case Request::Method::GET: return "GET";
        case Request::Method::HEAD: return "HEAD";
        case Request::Method::POST: return "POST";
        case Request::Method::PUT: return "PUT";
        case Request::Method::DELETE: return "DELETE";
        case Request::Method::TRACE: return "TRACE";
        case Request::Method::CONNECT: return "CONNECT";
        default: return "[UNKNOWN]";
    }
}

inline
std::ostream& operator<<(std::ostream& os, const RequestSP& ptr) {
    if(ptr) {
        os << *ptr;
    }
    return os;
}

}}} // namespace panda::protocol::http
