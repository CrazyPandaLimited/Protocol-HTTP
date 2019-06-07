#include "Request.h"

#include "Response.h"
#include "Header.h"

namespace panda { namespace protocol { namespace http {

Request::~Request() {
}

Request::Request() {
}

Request::Request(Method method, URISP uri, Header&& header, BodySP body, const string& http_version) :
    Message(std::move(header), body, http_version),
    method(method),
    uri(uri)
{
}

ResponseSP Request::response() const {
    return create_response();
}

ResponseSP Request::create_response() const {
    return make_iptr<Response>();
}

std::ostream& Request::print(std::ostream& os) const {
    os << to_string(method) << " " << uri->to_string() << " " << "HTTP/" << http_version_ << "\r\n";
    Message::print(os);
    return os;
}

}}} // namespace panda::protocol::http
