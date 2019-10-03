#pragma once
#include <vector>
#include <iosfwd>
#include <panda/string.h>

namespace panda { namespace protocol { namespace http {

struct Body {
    Body () {}
    Body (const string& body) { parts.emplace_back(body); }

    Body (const Body&) = default;
    Body (Body&& oth)  = default;

    Body& operator= (const string& str) {
        parts.clear();
        parts.emplace_back(str);
        return *this;
    }

    Body& operator= (string&& str) {
        parts.clear();
        parts.emplace_back(std::move(str));
        return *this;
    }

    size_t length () const {
        if (!parts.size()) return 0;
        uint64_t size = 0;
        for (auto& s : parts) size += s.length();
        return size;
    }

    string as_buffer () const;
    bool   empty     () const { return !length(); }

    std::vector<string> parts;
};

std::ostream& operator<< (std::ostream&, const Body&);

}}}
