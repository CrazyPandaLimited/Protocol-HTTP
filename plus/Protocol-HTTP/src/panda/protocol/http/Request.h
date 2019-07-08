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

    Request(Method method, URISP uri, Header&& header, BodySP body, const string& http_version);

    Method method;
    URISP uri;

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

inline std::vector<string> to_vector(Request* request_ptr) {
    std::vector<string> result;
    result.reserve(1 + request_ptr->body->parts.size());

    string header_str;
    header_str += string(to_string(request_ptr->method)) + " " + request_ptr->uri->relative() + " " + "HTTP/" + request_ptr->http_version() + "\r\n";
    for(auto field : request_ptr->headers.fields) {
        header_str += field.name + ": " + field.value + "\r\n";
    }

    header_str += "\r\n";

    result.emplace_back(header_str);
    for(auto part : request_ptr->body->parts) {
        result.emplace_back(part);
    }

    return result;
}

}}} // namespace panda::protocol::http
