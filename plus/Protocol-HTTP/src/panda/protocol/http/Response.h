#pragma once

#include "Message.h"

#include <panda/string.h>
#include <panda/refcnt.h>

#include "Defines.h"

namespace panda { namespace protocol { namespace http {

class Response : public Message {
public:
    Response();

    Response(int code, const string& reason, Header&& header, BodySP body, const string& http_version);

    int code;
    string message;

    std::ostream& print(std::ostream& os) const override;

protected:
    // restrict stack allocation
    virtual ~Response();

private:
    // disable copying as we disabled stack usage
    Response(const Response&) = delete;
    Response& operator=(const Response&) = delete;

};

inline
std::ostream& operator<<(std::ostream& os, const ResponseSP& ptr) {
    if(ptr) {
        os << *ptr;
    }
    return os;
}

inline std::vector<string> to_vector(Response* response_ptr) {
    string header_str;
    header_str += string("HTTP/") + response_ptr->http_version() + " " + panda::to_string(response_ptr->code) + " " + response_ptr->message + "\r\n";
    for (auto field : response_ptr->headers.fields) {
        header_str += field.name + ": " + field.value + "\r\n";
    }

    header_str += "\r\n";

    std::vector<string> result;
    result.reserve(1 + response_ptr->body->parts.size());
    result.emplace_back(header_str);
    for (auto part : response_ptr->body->parts) {
        result.emplace_back(part);
    }

    return result;
}

}}} // namespace panda::protocol::http
