#pragma once
#include "HeaderField.h"
#include <vector>
#include <panda/string.h>
#include <range/v3/core.hpp>
#include <range/v3/view/filter.hpp>

namespace panda { namespace protocol { namespace http {

static int const DEFAULT_FIELDS_RESERVE = 20;

struct Header {
    using Container = std::vector<HeaderField>;

    Container fields;

    Header ();
    Header (const Container& fields);
    Header (Container&& fields);

    bool     has_field    (string_view key) const;
    string   get_field    (string_view key, const string& default_val = "") const;
    Header&  add_field    (const string& key, const string& value) &;
    Header&& add_field    (const string& key, const string& value) && { add_field(key, value); return std::move(*this); }
    void     set_field    (const string& key, const string& value);
    void     remove_field (string_view key);

    bool   empty () const { return fields.empty(); }
    size_t size  () const { return fields.size(); }

    uint32_t length () const {
        uint32_t ret = 0;
        for (auto& field : fields) ret += field.name.length() + 2 + field.value.length() + 2;
        return ret;
    }

    void clear () { fields.clear(); }

    string connection () const { return get_field("Connection", ""); }
    string date       () const { return get_field("Date", ""); }
    string host       () const { return get_field("Host", ""); }
    string location   () const { return get_field("Location", ""); }
    bool   is_chunked () const { return get_field("Transfer-Encoding", "") == "chunked"; }

    Header&  connection (const string& ctype) &     { return add_field("Connection", ctype); }
    Header&& connection (const string& ctype) &&    { return std::move(*this).add_field("Connection", ctype); }
    Header&  date       (const string& date) &      { return add_field("Date", date); }
    Header&& date       (const string& date) &&     { return std::move(*this).add_field("Date", date); }
    Header&  host       (const string& host) &      { return add_field("Host", host); }
    Header&& host       (const string& host) &&     { return std::move(*this).add_field("Host", host); }
    Header&  location   (const string& location) &  { return add_field("Location", location); }
    Header&& location   (const string& location) && { return std::move(*this).add_field("Location", location); }
    Header&  chunked    () &                        { return add_field("Transfer-Encoding", "chunked"); }
    Header&& chunked    () &&                       { return std::move(*this).add_field("Transfer-Encoding", "chunked"); }

    Container::reverse_iterator       find (string_view key);
    Container::const_reverse_iterator find (string_view key) const;

    Container::reverse_iterator       end ()       { return fields.rend(); }
    Container::const_reverse_iterator end () const { return fields.rend(); }

    struct Comparator {
        string key;
        bool operator()(const HeaderField& f) const {
            return iequals(f.name, key);
        }
    };

    using Range = decltype(std::declval<const Container&>() | ::ranges::view::filter(std::declval<Comparator>()));

    Range equal_range (const string& key) const {
        return fields | ::ranges::view::filter(Comparator{key});
    }

    void write (string& s) {
        for (auto& field : fields) {
            s += field.name;
            s += ": ";
            s += field.value;
            s += "\r\n";
        }
    }
};

std::ostream& operator<< (std::ostream&, const Header&);

}}}
