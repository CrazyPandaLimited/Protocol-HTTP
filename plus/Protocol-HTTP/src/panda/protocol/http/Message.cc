#include "Message.h"

#include <vector>
#include <algorithm>

namespace panda { namespace protocol { namespace http {

Message::Message() :
    is_valid_(false),
    header_(),
    body_(make_iptr<Body>()),
    has_header_(false),
    has_body_(false) {
}

Message::Message(
        Header&& header,
        BodySP body,
        const string& http_version
        ) :
    is_valid_(true),
    header_(std::move(header)),
    body_(body),
    http_version_(http_version),
    has_header_(!header.fields.empty()),
    has_body_(!body->parts.empty())
{
}

const Header& Message::header() const {
    return header_;
}

Header& Message::header() {
    return header_;
}

BodySP Message::body() const {
    return body_;
}

void Message::add_header_field(const string& key, const string& value) {
    header_.fields.emplace_back(key, value);
}

void Message::add_body_part(const string& body_part) {
    body_->parts.emplace_back(body_part);
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
    os << header_;

    os << "\r\n";

    for(auto part : body_->parts) {
        os << part;
    }

    return os;
}

}}} // namespace panda::protocol::http
