#pragma once
#include <vector>
#include <iosfwd>

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

std::ostream& operator<< (std::ostream& os, const Body& b); 
std::ostream& operator<< (std::ostream& os, const BodySP& ptr); 

}}} // namespace panda::protocol::http
