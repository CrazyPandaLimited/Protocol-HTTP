#include "Request.h"

namespace panda { namespace protocol { namespace http {

static inline string _method_str (Request::Method rm) {
    using Method = Request::Method;
    switch (rm) {
        case Method::OPTIONS : return "OPTIONS";
        case Method::GET     : return "GET";
        case Method::HEAD    : return "HEAD";
        case Method::POST    : return "POST";
        case Method::PUT     : return "PUT";
        case Method::DELETE  : return "DELETE";
        case Method::TRACE   : return "TRACE";
        case Method::CONNECT : return "CONNECT";
        default: return "[UNKNOWN]";
    }
}

string Request::http_header (size_t reserve) {
    auto meth = _method_str(method);
    auto reluri  = uri ? uri->relative() : string("/");
    if (!http_version) http_version = 11;

    if (!chunked && body.parts.size() && !headers.has("Content-Length")) headers.add("Content-Length", panda::to_string(body.length()));

    if (!headers.has("Host") && uri && uri->host()) {
        // Host field builder
        // See https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Host
        auto host = uri->host();
        if (!uri->scheme() || (uri->scheme() == "http" && uri->port() != 80) || (uri->scheme() == "https" && uri->port() != 443)) {
            host.reserve(host.length()+6);
            host += ':';
            host += panda::to_string(uri->port());
        }
        headers.add("Host", host);
    }

    if (cookies.size()) {
        size_t len = 0;
        for (const auto& f : cookies.fields) len += f.name.length() + f.value.length() + 3; // 3 for ' ', '=' and ';' for each pair
        string coo(len);
        auto sz = cookies.size();
        for (size_t i = 0; i < sz; ++i) {
            if (i) { coo += "; "; }
            const auto& f = cookies.fields[i];
            coo += f.name;
            coo += '=';
            coo += f.value;
        }
        headers.add("Cookie", coo);
    }

    string s(meth.length() + 1 + reluri.length() + 6 + 5 + headers.length() + 2 + reserve);

    s += meth;
    s += ' ';
    s += reluri;
    s += " HTTP/";
    if (http_version == 11) s += "1.1\r\n";
    else                    s += "1.0\r\n";
    headers.write(s);
    s += "\r\n";

    return s;
}

std::vector<string> Request::to_vector () { return _to_vector([this]{ return http_header(0); }); }
string              Request::to_string () { return _to_string([this](size_t r){ return http_header(r); }); }

bool Request::expects_continue () const {
    for (auto& val : headers.get_multi("Expect")) if (val == "100-continue") return true;
    return false;
}

}}}
