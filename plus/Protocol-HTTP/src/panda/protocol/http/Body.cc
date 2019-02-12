#include "Body.h"

#include <numeric>

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

}}} // namespace panda::protocol::http
