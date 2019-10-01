#include "Message.h"
#include <algorithm>

namespace panda { namespace protocol { namespace http {

Message::Message () : chunked(), _is_valid(), _has_header(), _has_body(), _buf_size() {}

Message::Message (Header&& headers, Body&& body, const string& http_version, bool chunked) :
    headers(std::move(headers)), body(std::move(body)), http_version(http_version), chunked(chunked),
    _is_valid(true), _has_header(!headers.empty()), _has_body(!body.parts.empty()), _buf_size()
{}

void Message::add_header_field (const string& key, const string& value) {
    headers.add_field(key, value);
    _buf_size += key.size() + value.size();
}

void Message::add_body_part (const string& bodypart) {
    body.parts.emplace_back(bodypart);
    _buf_size += bodypart.size();
}

std::ostream& operator<< (std::ostream& os, const Message& message) {
    return os << message.to_string();
}

}}}
