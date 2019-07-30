#include "Body.h"
#include <numeric>
#include <ostream>

namespace panda { namespace protocol { namespace http {

Body::~Body() {
}

Body::Body() {
}

Body::Body(const string& body) {
    parts.emplace_back(body);
}

string Body::as_buffer() const {
    return std::accumulate(parts.begin(), parts.end(), string());
}

size_t Body::content_length() const {
    return std::accumulate(parts.begin(), parts.end(), 0, [](size_t a, const string& b) { return a + b.length(); });
}

std::ostream& operator<< (std::ostream& os, const Body& b) {
    for (auto part : b.parts) os << part;
    return os;
}

std::ostream& operator<<(std::ostream& os, const BodySP& ptr) {
    if (ptr) os << *ptr;
    return os;
}

}}}
