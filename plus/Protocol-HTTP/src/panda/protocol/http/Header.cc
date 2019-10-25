#include "Header.h"
#include <ostream>

namespace panda { namespace protocol { namespace http {

bool Header::has_field (string_view key) const {
    for (const auto& f : fields) if (iequals(f.name, key)) return true;
    return false;
}

Header::Container::const_iterator Header::find (string_view key) const {
    auto end = fields.crend();
    for (auto it = fields.crbegin(); it != end; ++it) {
        if (iequals(it->name, key)) return it.base()-1;
    }
    return fields.cend();
}

Header::Container::iterator Header::find (string_view key) {
    auto end = fields.rend();
    for (auto it = fields.rbegin(); it != end; ++it) {
        if (iequals(it->name, key)) return it.base()-1;
    }
    return fields.end();
}

string Header::get_field (string_view key, const string& default_val) const {
    auto it = find(key);
    return it == fields.cend() ? default_val : it->value;
}

void Header::set_field (const string& key, const string& value) {
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
        add_field(key, value);
    }
}

void Header::remove_field (string_view key) {
    for (auto it = fields.cbegin(); it != fields.end();) {
        if (iequals(it->name, key)) it = fields.erase(it);
        else ++it;
    }
}

std::ostream& operator<< (std::ostream& os, const Header::Field& hf) {
    os << hf.name << ": " << hf.value;
    return os;
}

std::ostream& operator<< (std::ostream& os, const Header& h) {
    for (auto field : h.fields) os << field << "\r\n";
    return os;
}

}}}
