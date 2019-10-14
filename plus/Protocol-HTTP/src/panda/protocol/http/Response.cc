#include "Response.h"
#include "Request.h"

namespace panda { namespace protocol { namespace http {

string Response::_http_header (const Request* req, size_t reserve) {
    if (req) {
        if (http_version == HttpVersion::any) http_version = req->http_version;
        if (!headers.has_field("Connection")) headers.add_field("Connection", req->keep_alive() ? string("keep-alive") : string("close"));
    }

    string s(5 + 4 + 4 + message.length() + 2 + headers.length() + 2 + reserve);

    s += "HTTP/";
    if (http_version == HttpVersion::v1_1) s += "1.1 ";
    else                                   s += "1.0 ";
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
