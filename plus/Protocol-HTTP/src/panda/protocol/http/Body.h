#pragma once

#include <vector>

#include <panda/refcnt.h>
#include <panda/string.h>

#include "Defines.h"

namespace panda { namespace protocol { namespace http {

struct Body : virtual Refcnt {
    virtual ~Body();

    Body();

    Body(const string& body);

    string as_buffer() const;

    size_t content_length() const;

    size_t length() const { return content_length(); }

    bool empty() { return length() == 0; }

    std::vector<string> parts;
};

inline
std::ostream& operator<<(std::ostream& os, const Body& b) {
    for(auto part : b.parts) {
        os << part;
    }
    return os;
}

inline
std::ostream& operator<<(std::ostream& os, const BodySP& ptr) {
    if(ptr) {
        os << *ptr;
    }
    return os;
}

}}} // namespace panda::protocol::http
