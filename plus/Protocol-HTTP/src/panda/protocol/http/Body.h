#pragma once
#include <vector>
#include <iosfwd>
#include <panda/refcnt.h>
#include <panda/string.h>

namespace panda { namespace protocol { namespace http {

struct Body : virtual Refcnt {
    Body () {}
    Body (const string& body);

    virtual ~Body() {}

    string as_buffer      () const;
    size_t length         () const;
    size_t content_length () const { return length(); }
    bool   empty          () const { return length() == 0; }

    std::vector<string> parts;
};
using BodySP = iptr<Body>;

std::ostream& operator<< (std::ostream&, const Body&);
std::ostream& operator<< (std::ostream&, const BodySP&);

}}}
