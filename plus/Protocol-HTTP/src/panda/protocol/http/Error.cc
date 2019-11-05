#include "Error.h"

namespace panda { namespace protocol { namespace http {

const ErrorCategory error_category;

const char* ErrorCategory::name () const throw() { return "protocol-http"; }

std::string ErrorCategory::message (int condition) const throw() {
    switch ((errc)condition) {
        case errc::semantic_error    : return "http parsing semantic error";
        case errc::lexical_error     : return "http parsing lexical error";
        case errc::headers_too_large : return "headers is bigger than max_headers_size";
        case errc::body_too_large    : return "body is bigger than max_body_size";
        case errc::unexpected_body   : return "body is prohibited";
        case errc::unexpected_eof    : return "http parsing error: unexpected EOF";
    }
    return {};
}

}}}
