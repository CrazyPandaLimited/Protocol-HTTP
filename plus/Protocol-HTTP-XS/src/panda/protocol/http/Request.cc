#include "Request.h"

#include "Response.h"
#include "Header.h"

namespace panda { namespace protocol { namespace http {

Request::~Request() {
}

Request::Request() {
}

Request::Request(Method method, URISP uri, HeaderSP header, BodySP body, const string& http_version) : 
    Message(header, body, http_version),
    method_(method), 
    uri_(uri) 
{
}

ResponseSP Request::response() const {
    return create_response();
}

ResponseSP Request::create_response() const {
    return make_iptr<Response>();
}

std::ostream& Request::print(std::ostream& os) const {
    os << to_string(method_) << " " << uri_->to_string() << " " << "HTTP/" << http_version_ << "\r\n";
    Message::print(os);
    return os;  
}

}}} // namespace panda::protocol::http
