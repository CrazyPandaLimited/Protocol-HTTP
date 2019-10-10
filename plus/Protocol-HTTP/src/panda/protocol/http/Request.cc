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
    prepare_tostr();
    auto meth = _method_str(method);
    auto reluri  = uri->relative();
    if (!http_version) http_version = "1.1";

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

std::vector<string> Request::to_vector () {
    auto hdr = _http_header(0);
    auto sz = body.size();
    if (!sz) return {hdr};

    std::vector<string> result;
    if (chunked) {
        result.reserve(1 + sz * 3 + 1);
        result.emplace_back(hdr);
        for (auto& part : body.parts) {
            auto ss = make_chunk(part);
            for (auto& s : ss) result.emplace_back(s);
        }
        result.emplace_back(end_chunk());
    } else {
        result.reserve(1 + sz);
        result.emplace_back(hdr);
        for (auto& part : body.parts) result.emplace_back(part);
    }

    return result;
}

string Request::to_string () {
    auto blen = body_length();
    auto ret = _http_header(blen);
    if (!blen) return ret;

    if (chunked) {
        for (auto& part : body.parts) {
            auto ss = make_chunk(part);
            for (auto& s : ss) ret += s;
        }
        ret += end_chunk();
    }
    else for (auto& part : body.parts) ret += part;

    return ret;
}

}}}
