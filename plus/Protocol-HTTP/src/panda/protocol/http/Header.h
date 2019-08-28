#pragma once

#include <vector>

#include <panda/refcnt.h>
#include <panda/string.h>

#include <range/v3/core.hpp>
#include <range/v3/view/filter.hpp>

#include "Defines.h"
#include "HeaderField.h"

namespace panda { namespace protocol { namespace http {

static int const DEFAULT_FIELDS_RESERVE = 20;

struct Header {
    friend std::ostream& operator<<(std::ostream& os, const HeaderField& hf);
    using Container = std::vector<HeaderField>;

    virtual ~Header();

    Header();

    Header(const std::vector<HeaderField>& fields);

    struct Builder {
        Builder& connection_close() {
            fields.emplace_back("Connection", "close");
            return *this;
        }

        Builder& date(const string& date) {
            fields.emplace_back("Date", date);
            return *this;
        }

        Builder& host(const string& host) {
            fields.emplace_back("Host", host);
            return *this;
        }

        Builder& location(const string& location) {
            fields.emplace_back("Location", location);
            return *this;
        }

        Builder& chunked() {
            fields.emplace_back("Transfer-Encoding", "chunked");
            return *this;
        }

        Builder& add_field(const string& name, const string& value) {
            fields.emplace_back(name, value);
            return *this;
        }

        Header build() {
            return Header(std::move(fields));
        }

    protected:
        std::vector<HeaderField> fields;
    };

    bool has_field(panda::string_view key) const;

    string get_field(panda::string_view key, const string& default_val = "") const;

    void add_field(panda::string_view key, const string& value);

    void set_field(panda::string_view key, const string& value);

    void remove_field(panda::string_view key);

    bool empty() const {
        return fields.empty();
    }

    void clear() {
        fields.clear();
    }

    size_t size() {
        return fields.size();
    }

    Container::reverse_iterator find(panda::string_view key);
    Container::const_reverse_iterator find(panda::string_view key) const;

    Container::reverse_iterator end() { return fields.rend(); }
    Container::const_reverse_iterator end() const { return fields.rend(); }

    struct Comparator {
        string key;
        bool operator()(const HeaderField& f) const {
            return iequals(f.name, key);
        }
    };

    using Range =  decltype(std::declval<const Container&>() | ::ranges::view::filter(std::declval<Comparator>()));

    Range equal_range(const string& key) const {
        return fields | ::ranges::view::filter(Comparator{key});
    }

    Container fields;
};

inline
std::ostream& operator<<(std::ostream& os, const Header& h) {
    for(auto field : h.fields) {
        os << field << "\r\n";
    }
    return os;
}

}}} // namespace panda::protocol::http
