#include "http.h"
#include <cstring>

namespace xs {
namespace protocol {
namespace http {

void http_packet_set_headers (panda::protocol::http::Message* p, const Hash& hv) {
    p->headers.clear();
    for (const auto& row : hv) p->headers.add_field(string(row.key()), xs::in<string>(row.value()));
}

void http_packet_set_body (panda::protocol::http::Message* p, const Simple& sv) {
    p->body->parts.clear();
    auto newbody = xs::in<string>(sv);
    if (newbody.length()) p->body->parts.push_back(newbody);
}

Simple strings_to_sv (const string& s1, const string& s2) {
    auto len = s1.length() + s2.length();
    if (!len) return Simple::undef;

    auto ret = Simple::create(len);
    char* dest = SvPVX(ret);
    std::memcpy(dest, s1.data(), s1.length());
    std::memcpy(dest + s1.length(), s2.data(), s2.length());
    dest[len] = 0;
    ret.length(len);
    return ret;
}

}
}
}
