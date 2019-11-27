#pragma once
#include <vector>
#include <iosfwd>
#include <panda/string.h>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <boost/container/small_vector.hpp>

namespace panda { namespace protocol { namespace http {

inline bool iequals (string_view a, string_view b) {
    auto sz = a.length();
    if (sz != b.length()) return false;

    const char* ap = a.data();
    const char* bp = b.data();
    size_t l = sz / 8;
    const char* e = ap + l*8;
    for (; ap != e; ap += 8, bp += 8) {
        uint64_t av, bv;
        memcpy(&av, ap, 8);
        memcpy(&bv, bp, 8);
        if ((av|0x2020202020202020ULL) != (bv|0x2020202020202020ULL)) return false;
    }

    auto left = sz - l*8;
    if (left & 4) {
        unsigned int av, bv;
        memcpy(&av, ap, 4);
        memcpy(&bv, bp, 4);
        if ((av|0x20202020) != (bv|0x20202020)) return false;
        ap += 4;
        bp += 4;
    }

    if (left & 2) {
        unsigned short av, bv;
        memcpy(&av, ap, 2);
        memcpy(&bv, bp, 2);
        if ((av|0x2020) != (bv|0x2020)) return false;
        ap += 2;
        bp += 2;
    }

    if (left & 1) return (*ap|0x20) == (*bp|0x20);

    return true;
}

struct Headers {
    struct Field {
        string name;
        string value;
        Field (const string& k, const string& v) : name(k), value(v) {}
    };
    using Container = boost::container::small_vector<Field, 15>;

    Container fields;

    Headers () {}
    Headers (const Container& fields) : fields(fields) {}
    Headers (Container&& fields)      : fields(std::move(fields)) {}

    bool      has    (string_view key) const;
    string    get    (string_view key, const string& default_val = "") const;
    Headers&  add    (const string& key, const string& value) &  { fields.emplace_back(key, value); return *this; }
    Headers&& add    (const string& key, const string& value) && { add(key, value); return std::move(*this); }
    void      set    (const string& key, const string& value);
    void      remove (string_view key);

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

    Headers&  connection      (const string& ctype) &     { return add("Connection", ctype); }
    Headers&& connection      (const string& ctype) &&    { return std::move(*this).add("Connection", ctype); }
    Headers&  date            (const string& date) &      { return add("Date", date); }
    Headers&& date            (const string& date) &&     { return std::move(*this).add("Date", date); }
    Headers&  host            (const string& host) &      { return add("Host", host); }
    Headers&& host            (const string& host) &&     { return std::move(*this).add("Host", host); }
    Headers&  location        (const string& location) &  { return add("Location", location); }
    Headers&& location        (const string& location) && { return std::move(*this).add("Location", location); }
    Headers&  chunked         () &                        { return add("Transfer-Encoding", "chunked"); }
    Headers&& chunked         () &&                       { return std::move(*this).add("Transfer-Encoding", "chunked"); }
    Headers&  expect_continue () &                        { return add("Expect", "100-continue"); }
    Headers&& expect_continue () &&                       { return std::move(*this).add("Expect", "100-continue"); }

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

    auto get_multi (const string_view& key) const {
        return fields | ::ranges::view::filter([key](const Field& f) {return iequals(f.name, key);})
                      | ::ranges::view::transform([](const Field& f) -> const string& {return f.value; });
    }
};

std::ostream& operator<< (std::ostream&, const Headers::Field&);
std::ostream& operator<< (std::ostream&, const Headers&);

}}}
