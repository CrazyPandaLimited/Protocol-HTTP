#include "Message.h"
#include <algorithm>

namespace panda { namespace protocol { namespace http {

Message::Message (Header&& headers, Body&& body, const string& http_version, bool chunked) :
    headers(std::move(headers)), body(std::move(body)), http_version(http_version), chunked(chunked), _buf_size()
{}

void Message::add_header_field (const string& key, const string& value) {
    headers.add_field(key, value);
    _buf_size += key.size() + value.size();
}

void Message::add_body_part (const string& bodypart) {
    body.parts.emplace_back(bodypart);
    _buf_size += bodypart.size();
}

bool Message::keep_alive () const {
    auto conn = headers.connection();
    if (http_version == "1.1") return !iequals(conn, "close");
    else                       return iequals(conn, "keep-alive");
}

std::ostream& operator<< (std::ostream& os, const Message& message) {
    return os << message.to_string();
}

}}}
