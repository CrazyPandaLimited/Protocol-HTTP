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

bool Header::has_field(const string &key) const {
    auto pos = std::find_if(fields.rbegin(), fields.rend(),[&](const HeaderField& f){
        return f.name == key;
    });
    
    return pos != fields.rend();
}

string Header::get_field(const string &key) const {
    auto pos = std::find_if(fields.rbegin(), fields.rend(),[&](const HeaderField& f){
        return f.name == key;
    });
    

    if (pos != fields.rend()) {
        return pos->value;
    }

    return string("");
}

void Header::add_field(const string &key, const string& value) {
    fields.emplace_back(key, value);
}

void Header::set_field(const string &key, const string& value) {
    auto pos = std::find_if(fields.begin(), fields.end(),[&](const HeaderField& f){
        return f.name == key;
    });
    

    if (pos == fields.end()) {
        return;
    }

    *pos = {key, value};
}

}}} // namespace panda::protocol::http
