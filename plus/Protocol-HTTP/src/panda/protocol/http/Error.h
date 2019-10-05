#pragma once
#include <system_error>
#include <panda/exception.h>

namespace panda { namespace protocol { namespace http {

enum class errc {
    semantic_error = 1,
    lexical_error,
    message_too_large,
    body_too_large,
    unexpected_body,
    unexpected_eof,
};

struct ErrorCategory : std::error_category {
    const char* name () const throw() override;
    std::string message (int condition) const throw() override;
};
extern ErrorCategory error_category;

struct ParserError : panda::exception {
    using exception::exception;
};

inline std::error_code make_error_code (errc code) { return std::error_code((int)code, error_category); }

}}}

namespace std {
    template <>
    struct is_error_code_enum<panda::protocol::http::errc> : true_type {};
}