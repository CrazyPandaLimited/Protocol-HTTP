#pragma once
#include <iosfwd>
#include <algorithm>
#include <panda/string.h>

namespace panda { namespace protocol { namespace http {

inline bool iequals (string_view a, string_view b) {
    return std::equal(a.begin(), a.end(), b.begin(), [](char a, char b) { return a == b || tolower(a) == tolower(b); });
}

struct HeaderField {
    string name;
    string value;

    HeaderField (const string& name, const string& value);

    bool operator== (const HeaderField& rhs) const;
    bool operator!= (const HeaderField& rhs) const { return !(*this == rhs); }
};

std::ostream& operator<< (std::ostream& os, const HeaderField& hf);

}}}
