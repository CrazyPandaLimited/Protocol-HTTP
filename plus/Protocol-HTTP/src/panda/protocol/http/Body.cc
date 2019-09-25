#include "Body.h"
#include <ostream>

namespace panda { namespace protocol { namespace http {

Body::Body (const string& body) {
    parts.emplace_back(body);
}

string Body::as_buffer () const {
    if (!parts.size()) return "";
    if (parts.size() == 1) return parts[0];
    string ret(length() + 1); // speedup possible c_str()
    for (auto& s : parts) ret += s;
    return ret;
}

size_t Body::length () const {
    uint64_t size = 0;
    for (auto& s : parts) size += s.length();
    return size;
}

std::ostream& operator<< (std::ostream& os, const Body& b) {
    for (auto part : b.parts) os << part;
    return os;
}

std::ostream& operator<< (std::ostream& os, const BodySP& ptr) {
    if (ptr) os << *ptr;
    return os;
}

}}}
