#include "Request.h"

namespace panda { namespace protocol { namespace http {

Request::Request (Method method, const URISP& uri, Header&& header, const BodySP& body, const string& http_version) :
    Message(std::move(header), body, http_version), method(method), uri(uri)
{}

std::ostream& Request::print (std::ostream& os) const {
    os << to_string(method) << " " << uri->to_string() << " " << "HTTP/" << http_version_ << "\r\n";
    Message::print(os);
    return os;
}

std::ostream& operator<< (std::ostream& os, const RequestSP& ptr) {
    if (ptr) os << *ptr;
    return os;
}

std::vector<string> to_vector (Request* r) {
    std::vector<string> result;
    result.reserve(1 + r->body->parts.size());

    string header_str;
    header_str += string(to_string(r->method)) + " " + r->uri->relative() + " " + "HTTP/" + r->http_version() + "\r\n";
    for (auto& field : r->headers.fields) header_str += field.name + ": " + field.value + "\r\n";
    header_str += "\r\n";

    result.emplace_back(header_str);
    for (auto part : r->body->parts) result.emplace_back(part);

    return result;
}

}}}
