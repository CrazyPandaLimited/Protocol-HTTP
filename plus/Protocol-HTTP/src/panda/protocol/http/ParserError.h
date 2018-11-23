#pragma once

#include <exception>

namespace panda { namespace protocol { namespace http {

class ParserError : public std::runtime_error {
public:
    ParserError(const std::string& msg) : std::runtime_error(msg) {
    }
};

}}} // namespace panda::protocol::http
