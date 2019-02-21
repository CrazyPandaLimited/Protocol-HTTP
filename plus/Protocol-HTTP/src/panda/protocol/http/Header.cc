#include "Header.h"

#include <algorithm>

#include "HeaderField.h"

namespace panda { namespace protocol { namespace http {

Header::~Header() {
}

Header::Header() {
    fields.reserve(DEFAULT_FIELDS_RESERVE);
}

Header::Header(const std::vector<HeaderField>& fields) : fields(fields) {
}

bool Header::has_field(std::string_view key) const {
    return find(key) != fields.rend();
}

Header::Container::const_reverse_iterator Header::find(std::string_view key) const {
    return std::find_if(fields.rbegin(), fields.rend(),[&](const HeaderField& f){
        return iequals(f.name, key);
    });
}

Header::Container::reverse_iterator Header::find(std::string_view key) {
    return std::find_if(fields.rbegin(), fields.rend(),[&](const HeaderField& f){
        return iequals(f.name, key);
    });
}


string Header::get_field(std::string_view key, const string& default_val) const {
    auto pos = find(key);

    if (pos != fields.rend()) {
        return pos->value;
    }

    return default_val;
}

void Header::add_field(std::string_view key, const string& value) {
    fields.emplace_back(string(key.data(), key.size()), value);
}

void Header::set_field(std::string_view key, const string& value) {
    auto pos = std::find_if(fields.begin(), fields.end(),[&](const HeaderField& f){
        return iequals(f.name, key);
    });


    if (pos == fields.end()) {
        add_field(key, value);
        return;
    }

    *pos = {string(key.data(), key.size()), value};
}

void Header::remove_field(std::string_view key) {
    fields.erase(std::remove_if(fields.begin(), fields.end(), Comparator{string(key.data(), key.size())}), fields.end());
}

}}} // namespace panda::protocol::http
