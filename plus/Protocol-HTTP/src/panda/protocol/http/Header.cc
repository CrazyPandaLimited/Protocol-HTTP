#include "Header.h"
#include <algorithm>

namespace panda { namespace protocol { namespace http {

Header::Header () {
    fields.reserve(DEFAULT_FIELDS_RESERVE);
}

Header::Header (const Container& fields) : fields(fields)            {}
Header::Header (Container&& fields)      : fields(std::move(fields)) {}

bool Header::has_field (string_view key) const {
    return find(key) != fields.rend();
}

Header::Container::const_reverse_iterator Header::find (string_view key) const {
    return std::find_if(fields.rbegin(), fields.rend(), [&](const HeaderField& f) {
        return iequals(f.name, key);
    });
}

Header::Container::reverse_iterator Header::find (string_view key) {
    return std::find_if(fields.rbegin(), fields.rend(), [&](const HeaderField& f) {
        return iequals(f.name, key);
    });
}

string Header::get_field (string_view key, const string& default_val) const {
    auto pos = find(key);
    return pos != fields.rend() ? pos->value : default_val;
}

Header& Header::add_field (const string& key, const string& value) & {
    fields.emplace_back(string(key.data(), key.size()), value);
    return *this;
}

void Header::set_field (const string& key, const string& value) {
    remove_field(key);
    add_field(key, value);
}

void Header::remove_field (string_view key) {
    fields.erase(std::remove_if(fields.begin(), fields.end(), Comparator{string(key.data(), key.size())}), fields.end());
}

std::ostream& operator<< (std::ostream& os, const Header& h) {
    for (auto field : h.fields) os << field << "\r\n";
    return os;
}

}}}
