#include "http.h"
#include <cstring>

namespace xs { namespace protocol { namespace http {

using panda::string;

static inline void msgfill (Message* m, const Hash& h) {
    Sv sv;
    if ((sv = h.fetch("headers")))      set_headers(m, sv);
    if ((sv = h.fetch("body")))         m->body         = xs::in<string>(sv);
    if ((sv = h.fetch("http_version"))) m->http_version = Simple(sv);
    if ((sv = h.fetch("chunked")))      m->chunked      = sv.is_true();
}

void fill (Request* req, const Hash& h) {
    msgfill(req, h);
    Sv sv;
    if ((sv = h.fetch("method")) && sv.defined()) set_method(req, sv);
    if ((sv = h.fetch("uri"))) req->uri = xs::in<URISP>(sv);
}

void fill (Response* res, const Hash& h) {
    msgfill(res, h);
    Simple v;
    if ((v = h.fetch("code")))    res->code = v;
    if ((v = h.fetch("message"))) res->message = v.as_string();
}

void set_headers (Message* p, const Hash& hv) {
    p->headers.clear();
    for (const auto& row : hv) p->headers.add(string(row.key()), xs::in<string>(row.value()));
}

void set_method (Request* req, const Sv& method) {
    using Method = Request::Method;
    int num = SvIV_nomg(method);
    if (num < (int)Method::OPTIONS || num > (int)Method::CONNECT) throw panda::exception("invalid http method");
    req->method = (Method)num;
}

}}}
