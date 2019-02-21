#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

#include <panda/refcnt.h>
#include <panda/string.h>

namespace panda { namespace protocol { namespace http {

inline
bool iequals(std::string_view a, std::string_view b) {
    return std::equal(a.begin(), a.end(), b.begin(), [](char a, char b) { return a == b || tolower(a) == tolower(b); });
}

struct HeaderField {
    friend std::ostream& operator<<(std::ostream& os, const HeaderField& hf);

    HeaderField(const string& name, const string& value);
    bool operator==(const HeaderField& rhs) const;
    bool operator!=(const HeaderField& rhs) const;

    string name;
    string value;
};

inline
std::ostream& operator<<(std::ostream& os, const HeaderField& hf) {
    os << hf.name << ": " << hf.value;
    return os;
}

}}} // namespace panda::protocol::http
