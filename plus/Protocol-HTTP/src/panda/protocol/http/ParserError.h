#pragma once
#include <stdexcept>

namespace panda { namespace protocol { namespace http {

struct ParserError : std::runtime_error {
    ParserError (const std::string& msg) : std::runtime_error(msg) {}
};

}}}
