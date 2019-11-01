#include "Message.h"
#include <algorithm>

namespace panda { namespace protocol { namespace http {

void Message::add_header (const string& key, const string& value) {
    headers.add(key, value);
    _buf_size += key.size() + value.size();
}

void Message::add_body_part (const string& bodypart) {
    body.parts.emplace_back(bodypart);
    _buf_size += bodypart.size();
}

bool Message::keep_alive () const {
    auto conn = headers.connection();
    if (http_version == HttpVersion::v1_1) return !iequals(conn, "close");
    else                                   return iequals(conn, "keep-alive");
}

}}}
