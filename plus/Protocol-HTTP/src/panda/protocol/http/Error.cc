#include "Error.h"

namespace panda { namespace protocol { namespace http {

ErrorCategory error_category;

const char* ErrorCategory::name () const throw() { return "protocol-http"; }

std::string ErrorCategory::message (int condition) const throw() {
    switch ((errc)condition) {
        case errc::semantic_error    : return "http parsing semantic error";
        case errc::lexical_error     : return "http parsing lexical error";
        case errc::message_too_large : return "message is bigger than max_message_size";
        case errc::body_too_large    : return "body is bigger than max_body_size";
        case errc::unexpected_body   : return "body is prohibited";
        case errc::unexpected_eof    : return "http parsing error: unexpected EOF";
    }
    return {};
}

}}}