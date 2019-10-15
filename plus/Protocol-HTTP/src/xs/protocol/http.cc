#include "http.h"
#include <cstring>

namespace xs { namespace protocol { namespace http {

using panda::string;

static inline void make_message (const Hash& p, Message* m) {
    Sv sv;
    if ((sv = p.fetch("headers")))      set_headers(m, sv);
    if ((sv = p.fetch("body")))         m->body         = xs::in<string>(sv);
    if ((sv = p.fetch("http_version"))) m->http_version = sv_to_http_version(sv);
    if ((sv = p.fetch("chunked")))      m->chunked      = sv.is_true();
}

RequestSP make_request (const Hash& p, const RequestSP& dest) {
    auto ret = dest ? dest : RequestSP(new Request());
    make_message(p, ret.get());

    Sv sv;
    if ((sv = p.fetch("method")) && sv.defined()) set_method(ret.get(), sv);
    if ((sv = p.fetch("uri"))) ret->uri = xs::in<URISP>(sv);

    return ret;
}

ResponseSP make_response (const Hash& p, const ResponseSP& dest) {
    auto ret = dest ? dest : ResponseSP(new Response());
    make_message(p, ret.get());

    Simple v;
    if ((v = p.fetch("code")))    ret->code = v;
    if ((v = p.fetch("message"))) ret->message = v.as_string();

    return ret;
}

void set_headers (Message* p, const Hash& hv) {
    p->headers.clear();
    for (const auto& row : hv) p->headers.add_field(string(row.key()), xs::in<string>(row.value()));
}

void set_method (Request* req, const Sv& method) {
    using Method = Request::Method;
    int num = SvIV_nomg(method);
    if (num < (int)Method::OPTIONS || num > (int)Method::CONNECT) throw panda::exception("invalid http method");
    req->method = (Method)num;
}

template <typename T>
Simple strings_to_sv_impl (const T& v) {
    size_t len = 0;
    for (const auto& s : v) len += s.length();
    if (!len) return Simple::undef;

    auto ret = Simple::create(len);
    char* dest = ret.get<char*>();
    for (const auto& s : v) {
        memcpy(dest, s.data(), s.length());
        dest += s.length();
    }
    *dest = 0;
    ret.length(len);
    return ret;
}

Simple strings_to_sv (const std::vector<string>& v) {
    return strings_to_sv_impl(v);
}

Simple strings_to_sv (const boost::container::small_vector_base<string>& v) {
    return strings_to_sv_impl(v);
}

}}}
