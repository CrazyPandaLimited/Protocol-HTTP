#include "Request.h"

namespace panda { namespace protocol { namespace http {

Request::Request (Method method, const URISP& uri, Header&& header, Body&& body, const string& http_version, bool chunked) :
    Message(std::move(header), std::move(body), http_version, chunked), method(method), uri(uri)
{}

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
    prepare_tostr();
    auto meth = _method_str(method);
    auto reluri  = uri->relative();

    if (http_version == "1.1" && !headers.has_field("Host")) {
        // Host field builder
        // See https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Host
        auto host = uri->host();
        if ((uri->scheme() == "http" && uri->port() != 80) || (uri->scheme() == "https" && uri->port() != 443)) {
            host.reserve(host.length()+6);
            host += ':';
            host += panda::to_string(uri->port());
        }
        headers.add_field("Host", host);
    }

    if (!headers.has_field("User-Agent")) headers.add_field(
        "User-Agent",
        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.111 Safari/537.36 PandaHTTP/1.0.1"
    );

    string s(meth.length() + 1 + reluri.length() + 6 + http_version.length() + 2 + headers.length() + 2 + reserve);

    s += meth;
    s += ' ';
    s += reluri;
    s += " HTTP/";
    s += http_version;
    s += "\r\n";
    headers.write(s);
    s += "\r\n";

    return s;
}

std::vector<string> Request::to_vector () const {
    std::vector<string> result;
    result.reserve(1 + body.parts.size());

    result.emplace_back(const_cast<Request*>(this)->_http_header(0));
    for (auto& part : body.parts) result.emplace_back(part);

    return result;
}

string Request::to_string () const {
    auto ret = const_cast<Request*>(this)->_http_header(body.length());
    for (auto& part : body.parts) ret += part;

    return ret;
}

}}}
