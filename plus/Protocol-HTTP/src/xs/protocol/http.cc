#include "http.h"

namespace xs {
namespace protocol {
namespace http {

void http_packet_set_headers (pTHX_ panda::protocol::http::Message* p, const Hash& hv) {
    p->headers.clear();
    for (const auto& row : hv) p->headers.add_field(string(row.key()), xs::in<string>(aTHX_ row.value()));
}

void http_packet_set_body (pTHX_ panda::protocol::http::Message* p, const Simple& sv) {
    p->body->parts.clear();
    auto newbody = xs::in<string>(aTHX_ sv);
    if (newbody.length()) p->body->parts.push_back(newbody);
}

}
}
}
