#include "Message.h"
#include <algorithm>

namespace panda { namespace protocol { namespace http {

Message::Message () : body(make_iptr<Body>()), is_valid_(), http_version_("1.1"), has_header_(), has_body_(), _buf_size() {}

Message::Message (Header&& headers, const BodySP& body, const string& http_version) :
    headers(std::move(headers)), body(body), is_valid_(true), http_version_(http_version), has_header_(!headers.empty()),
    has_body_(!body->parts.empty()), _buf_size()
{}

void Message::add_header_field (const string& key, const string& value) {
    headers.add_field(key, value);
    _buf_size += key.size() + value.size();
}

void Message::add_body_part (const string& bodypart) {
    body->parts.emplace_back(bodypart);
    _buf_size += bodypart.size();
}

std::ostream& Message::print (std::ostream& os) const {
    os << headers;
    os << "\r\n";
    for (auto part : body->parts) os << part;
    return os;
}

std::ostream& operator<< (std::ostream& os, const Message& message) {
    return message.print(os);
}

}}}
