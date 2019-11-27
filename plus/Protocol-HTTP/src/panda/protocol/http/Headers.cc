#include "Headers.h"
#include <ostream>

namespace panda { namespace protocol { namespace http {

bool Headers::has (string_view key) const {
    for (const auto& f : fields) if (iequals(f.name, key)) return true;
    return false;
}

Headers::Container::const_iterator Headers::find (string_view key) const {
    auto end = fields.crend();
    for (auto it = fields.crbegin(); it != end; ++it) {
        if (iequals(it->name, key)) return it.base()-1;
    }
    return fields.cend();
}

Headers::Container::iterator Headers::find (string_view key) {
    auto end = fields.rend();
    for (auto it = fields.rbegin(); it != end; ++it) {
        if (iequals(it->name, key)) return it.base()-1;
    }
    return fields.end();
}

string Headers::get (string_view key, const string& default_val) const {
    auto it = find(key);
    return it == fields.cend() ? default_val : it->value;
}

void Headers::set (const string& key, const string& value) {
    bool replaced = false;
    for (auto it = fields.begin(); it != fields.end();) {
        if (iequals(it->name, key)) {
            if (replaced) it = fields.erase(it);
            else {
                replaced = true;
                it->name  = key;
                it->value = value;
                ++it;
            }
        }
        else ++it;
    }
    if (!replaced) {
        add(key, value);
    }
}

void Headers::remove (string_view key) {
    for (auto it = fields.cbegin(); it != fields.end();) {
        if (iequals(it->name, key)) it = fields.erase(it);
        else ++it;
    }
}

std::ostream& operator<< (std::ostream& os, const Headers::Field& hf) {
    os << hf.name << ": " << hf.value;
    return os;
}

std::ostream& operator<< (std::ostream& os, const Headers& h) {
    for (auto field : h.fields) os << field << "\r\n";
    return os;
}

}}}
