#include "Response.h"

namespace panda { namespace protocol { namespace http {

Response::Response (int code, const string& reason, Header&& header, Body&& body, const string& http_version, bool chunked) :
    Message(std::move(header), std::move(body), http_version, chunked), code(code), message(reason)
{}

string Response::_http_header (size_t reserve) {
    prepare_tostr();

    string s(5 + http_version.length() + 5 + message.length() + 2 + headers.length() + 2 + reserve);

    s += "HTTP/";
    s += http_version;
    s += ' ';
    s += panda::to_string(code);
    s += ' ';
    s += message;
    s += "\r\n";
    headers.write(s);
    s += "\r\n";

    return s;
}

std::vector<string> Response::to_vector () const {
    std::vector<string> result;
    result.reserve(1 + body.parts.size());
    result.emplace_back(const_cast<Response*>(this)->_http_header(0));
    for (auto& part : body.parts) result.emplace_back(part);
    return result;
}

string Response::to_string () const {
    auto ret = const_cast<Response*>(this)->_http_header(body.length());
    for (auto& part : body.parts) ret += part;

    return ret;
}

}}}
