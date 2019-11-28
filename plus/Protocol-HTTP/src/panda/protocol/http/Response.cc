#include "Response.h"
#include "Request.h"
#include <ctime>

namespace panda { namespace protocol { namespace http {

const char Response::Cookie::AUTO[1] = {0};

int64_t Response::Cookie::max_age_any () const {
    if (_max_age || !_expires) return _max_age;
    return Date(_expires).epoch() - std::time(nullptr);
}

optional<date::Date> Response::Cookie::expires_any () const {
    if (!_max_age) return expires();
    auto ret = Date::now();
    ret.epoch(ret.epoch() + _max_age);
    return ret;
}

string Response::Cookie::to_string (const string& name, const Request* req) const {
    string str(200); // should be enough for average set-cookie header
    str += name;
    str += '=';
    str += _value;

    const string& domain = _domain.data() == AUTO && req ? req->headers.get("Host") : _domain;
    if (domain) {
        str += "; Domain=";
        str += domain;
    }

    if (_path) {
        str += "; Path=";
        str += _path;
    }

    if (_max_age) {
        str += "; Max-Age=";
        str += panda::to_string(_max_age);
    }
    else if (_expires) {
        str += "; Expires=";
        str += _expires;
    }

    if (_secure)    str += "; Secure";
    if (_http_only) str += "; HttpOnly";

    if      (_same_site == SameSite::Strict) str += "; SameSite";
    else if (_same_site == SameSite::Lax   ) str += "; SameSite=Lax";

    return str;
}

string Response::_http_header (const Request* req, size_t reserve) {
    if (!code) code = 200;
    if (req) {
        if (!http_version) http_version = req->http_version;
        if (!req->keep_alive()) headers.set("Connection", "close");
        else if (!headers.has("Connection")) headers.add("Connection", "keep-alive");
    }
    if (!message) message = message_for_code(code);

    if (!chunked && !headers.has("Content-Length")) headers.add("Content-Length", panda::to_string(body.length()));

    for (const auto& item : cookies.fields) headers.add("Set-Cookie", item.value.to_string(item.name, req));

    string s(5 + 4 + 4 + message.length() + 2 + headers.length() + 2 + reserve);

    s += "HTTP/";
    switch (http_version) {
        case 0:
        case 11: s += "1.1 "; break;
        case 10: s += "1.0 "; break;
        default: assert(false && "invalid http version");
    }
    s += panda::to_string(code);
    s += ' ';
    s += message;
    s += "\r\n";
    headers.write(s);
    s += "\r\n";

    return s;
}

std::vector<string> Response::to_vector (const Request* req) { return _to_vector([this,req]{ return _http_header(req, 0); }); }
string              Response::to_string (const Request* req) { return _to_string([this,req](size_t r){ return _http_header(req, r); }); }

string Response::message_for_code (int code) {
    switch (code) {
        case 100: return "Continue";
        case 101: return "Switching Protocol";
        case 102: return "Processing";
        case 103: return "Early Hints";
        case 200: return "OK";
        case 201: return "Created";
        case 202: return "Accepted";
        case 203: return "Non-Authoritative Information";
        case 204: return "No Content";
        case 205: return "Reset Content";
        case 206: return "Partial Content";
        case 300: return "Multiple Choice";
        case 301: return "Moved Permanently";
        case 302: return "Found";
        case 303: return "See Other";
        case 304: return "Not Modified";
        case 305: return "Use Proxy";
        case 306: return "Switch Proxy";
        case 307: return "Temporary Redirect";
        case 308: return "Permanent Redirect";
        case 400: return "Bad Request";
        case 401: return "Unauthorized";
        case 402: return "Payment Required";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 406: return "Not Acceptable";
        case 407: return "Proxy Authentication Required";
        case 408: return "Request Timeout";
        case 409: return "Conflict";
        case 410: return "Gone";
        case 411: return "Length Required";
        case 412: return "Precondition Failed";
        case 413: return "Request Entity Too Large";
        case 414: return "Request-URI Too Long";
        case 415: return "Unsupported Media Type";
        case 416: return "Requested Range Not Satisfiable";
        case 417: return "Expectation Failed";
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 502: return "Bad Gateway";
        case 503: return "Service Unavailable";
        case 504: return "Gateway Timeout";
        case 505: return "HTTP Version Not Supported";
        default : return {};
    }
}

}}}
