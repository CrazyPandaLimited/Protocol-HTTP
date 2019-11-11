#pragma once
#include <vector>
#include <iosfwd>
#include <panda/string.h>

#include <boost/container/small_vector.hpp>
#include <range/v3/view/filter.hpp>

namespace panda { namespace protocol { namespace http {

static constexpr int const DEFAULT_FIELDS_RESERVE = 10;

inline bool iequals (string_view a, string_view b) {
    return a.length() == b.length() && std::equal(a.begin(), a.end(), b.begin(), [](char a, char b) { return a == b || tolower(a) == tolower(b); });
}

struct Header {
    struct Field {
        string name;
        string value;
        Field (const string& k, const string& v) : name(k), value(v) {}
        bool operator== (const Field &rhs) const { return iequals(name, rhs.name) && value == rhs.value; }
        bool operator!= (const Field& rhs) const { return !(*this == rhs); }
    };
    using Container = boost::container::small_vector<Field, DEFAULT_FIELDS_RESERVE>;

    Container fields;

    Header () {}
    Header (const Container& fields) : fields(fields) {}
    Header (Container&& fields)      : fields(std::move(fields)) {}

    bool     has    (string_view key) const;
    string   get    (string_view key, const string& default_val = "") const;
    Header&  add    (const string& key, const string& value) &  { fields.emplace_back(key, value); return *this; }
    Header&& add    (const string& key, const string& value) && { add(key, value); return std::move(*this); }
    void     set    (const string& key, const string& value);
    void     remove (string_view key);

    bool   empty () const { return fields.empty(); }
    size_t size  () const { return fields.size(); }

    uint32_t length () const {
        uint32_t ret = 0;
        for (auto& field : fields) ret += field.name.length() + 2 + field.value.length() + 2;
        return ret;
    }

    void clear () { fields.clear(); }

    string connection () const { return get("Connection", ""); }
    string date       () const { return get("Date", ""); }
    string host       () const { return get("Host", ""); }
    string location   () const { return get("Location", ""); }
    bool   is_chunked () const { return get("Transfer-Encoding", "") == "chunked"; }

    Header&  connection      (const string& ctype) &     { return add("Connection", ctype); }
    Header&& connection      (const string& ctype) &&    { return std::move(*this).add("Connection", ctype); }
    Header&  date            (const string& date) &      { return add("Date", date); }
    Header&& date            (const string& date) &&     { return std::move(*this).add("Date", date); }
    Header&  host            (const string& host) &      { return add("Host", host); }
    Header&& host            (const string& host) &&     { return std::move(*this).add("Host", host); }
    Header&  location        (const string& location) &  { return add("Location", location); }
    Header&& location        (const string& location) && { return std::move(*this).add("Location", location); }
    Header&  chunked         () &                        { return add("Transfer-Encoding", "chunked"); }
    Header&& chunked         () &&                       { return std::move(*this).add("Transfer-Encoding", "chunked"); }
    Header&  expect_continue () &                        { return add("Expect", "100-continue"); }
    Header&& expect_continue () &&                       { return std::move(*this).add("Expect", "100-continue"); }

    Container::iterator       find (string_view key);
    Container::const_iterator find (string_view key) const;

    Container::iterator       end ()       { return fields.end(); }
    Container::const_iterator end () const { return fields.end(); }


    void write (string& s) {
        for (auto& field : fields) {
            s += field.name;
            s += ": ";
            s += field.value;
            s += "\r\n";
        }
    }

    auto equal_range (const string& key) const {
        return fields | ::ranges::view::filter([key](const Field& f){return iequals(f.name, key);});
    }

};

std::ostream& operator<< (std::ostream&, const Header::Field&);
std::ostream& operator<< (std::ostream&, const Header&);

}}}
