#include "Message.h"

#include <vector>
#include <algorithm>

namespace panda { namespace protocol { namespace http {

Message::Message() :
    headers(),
    body(make_iptr<Body>()),
    is_valid_(false),
    has_header_(false),
    has_body_(false) {
}

Message::Message(
        Header&& header,
        BodySP body,
        const string& http_version
        ) :
    headers(std::move(header)),
    body(body),
    is_valid_(true),
    http_version_(http_version),
    has_header_(!header.fields.empty()),
    has_body_(!body->parts.empty())
{
}

void Message::add_header_field(const string& key, const string& value) {
    headers.fields.emplace_back(key, value);
}

void Message::add_body_part(const string& bodypart) {
    body->parts.emplace_back(bodypart);
}

bool Message::is_valid() const {
    return is_valid_;
}

void Message::set_valid() {
   is_valid_ = true;
}

bool Message::has_header() const {
    return has_header_;
}

void Message::set_header() {
   has_header_ = true;
}

bool Message::has_body() const {
    return has_body_;
}

void Message::set_body() {
   has_body_ = true;
}

std::ostream& operator<<(std::ostream& os, const Message& message) {
    return message.print(os);
}

std::ostream& Message::print(std::ostream& os) const {
    os << headers;

    os << "\r\n";

    for(auto part : body->parts) {
        os << part;
    }

    return os;
}

}}} // namespace panda::protocol::http
