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

string Request::_http_header (size_t reserve) {
    auto meth = _method_str(method);
    auto reluri  = uri ? uri->relative() : string("/");
    if (!http_version) http_version = 11;

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

std::vector<string> Request::to_vector () { return _to_vector([this]{ return _http_header(0); }); }
string              Request::to_string () { return _to_string([this](size_t r){ return _http_header(r); }); }

bool Request::expects_continue () const {
    for (auto& r : headers.equal_range("Expect")) if (r.value == "100-continue") return true;
    return false;
}

}}}
