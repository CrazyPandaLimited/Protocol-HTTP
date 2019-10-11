#include "Response.h"
#include "Request.h"

namespace panda { namespace protocol { namespace http {

Response::Response (int code, const string& message, Header&& header, Body&& body, const string& http_version, bool chunked) :
    Message(std::move(header), std::move(body), http_version, chunked), code(code), message(message)
{}

string Response::_http_header (const Request* req, size_t reserve) {
    if (req) {
        if (!http_version) http_version = req->http_version;
        if (!headers.has_field("Connection")) headers.add_field("Connection", req->keep_alive() ? string("keep-alive") : string("close"));
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

std::vector<string> Response::to_vector (const Request* req) { return _to_vector([this,req]{ return _http_header(req, 0); }); }
string              Response::to_string (const Request* req) { return _to_string([this,req](size_t r){ return _http_header(req, r); }); }

}}}
