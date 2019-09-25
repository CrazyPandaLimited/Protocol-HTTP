#include "Response.h"

namespace panda { namespace protocol { namespace http {

Response::Response (int code, const string& reason, Header&& header, const BodySP& body, const string& http_version) :
    Message(std::move(header), body, http_version), code(code), message(reason)
{}

std::ostream& Response::print (std::ostream& os) const {
    os << "HTTP/" << http_version_ << " " << to_string(code) << " " << message << "\r\n";
    Message::print(os);
    return os;
}

std::ostream& operator<< (std::ostream& os, const ResponseSP& ptr) {
    if (ptr) os << *ptr;
    return os;
}

std::vector<string> to_vector (Response* r) {
    string header_str = string("HTTP/") + r->http_version() + " " + panda::to_string(r->code) + " " + r->message + "\r\n";
    for (auto& field : r->headers.fields) header_str += field.name + ": " + field.value + "\r\n";
    header_str += "\r\n";

    std::vector<string> result;
    result.reserve(1 + r->body->parts.size());
    result.emplace_back(header_str);
    for (auto part : r->body->parts) result.emplace_back(part);

    return result;
}

}}}
