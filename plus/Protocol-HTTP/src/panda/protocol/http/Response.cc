#include "Response.h"
#include "Request.h"

namespace panda { namespace protocol { namespace http {

Response::Response (int code, const string& message, Header&& header, Body&& body, const string& http_version, bool chunked) :
    Message(std::move(header), std::move(body), http_version, chunked), code(code), message(message)
{}

string Response::_http_header (const Request* req, size_t reserve) {
    prepare_tostr();

    if (req) {
        if (!http_version) http_version = req->http_version;
    }

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

std::vector<string> Response::to_vector (const Request* req) {
    std::vector<string> result;
    result.reserve(1 + body.parts.size());
    result.emplace_back(_http_header(req, 0));
    for (auto& part : body.parts) result.emplace_back(part);
    return result;
}

string Response::to_string (const Request* req) {
    auto ret = _http_header(req, body.length());
    for (auto& part : body.parts) ret += part;

    return ret;
}

}}}
