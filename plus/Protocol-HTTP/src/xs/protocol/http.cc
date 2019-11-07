#include "http.h"
#include <cstring>

namespace xs { namespace protocol { namespace http {

using panda::string;

static inline void fill_message (const Hash& p, Message* m) {
    Sv sv;
    if ((sv = p.fetch("headers")))      set_headers(m, sv);
    if ((sv = p.fetch("body")))         m->body         = xs::in<string>(sv);
    if ((sv = p.fetch("http_version"))) m->http_version = Simple(sv);
    if ((sv = p.fetch("chunked")))      m->chunked      = sv.is_true();
}

void fill_request (const Hash& p, Request* req) {
    fill_message(p, req);

    Sv sv;
    if ((sv = p.fetch("method")) && sv.defined()) set_method(req, sv);
    if ((sv = p.fetch("uri"))) req->uri = xs::in<URISP>(sv);
}

void fill_response (const Hash& p, Response* res) {
    fill_message(p, res);

    Simple v;
    if ((v = p.fetch("code")))    res->code = v;
    if ((v = p.fetch("message"))) res->message = v.as_string();
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
