#include "Response.h"

namespace panda { namespace protocol { namespace http {

Response::~Response() {
}

Response::Response() :
    code_(0) {
}

Response::Response(int code, const string& reason, Header&& header, BodySP body, const string& http_version) :
    Message(std::move(header), body, http_version),
    code_(code),
    reason_(reason)
{
}

std::ostream& Response::print(std::ostream& os) const {
    os << "HTTP/" << http_version_ << " " << to_string(code_) << " " << reason_ << "\r\n";
    Message::print(os);
    return os;
}

}}} // namespace panda::protocol::http
