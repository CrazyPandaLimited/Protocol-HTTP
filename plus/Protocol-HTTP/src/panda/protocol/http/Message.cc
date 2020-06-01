#include "Message.h"
#include <algorithm>

namespace panda { namespace protocol { namespace http {

bool Message::keep_alive () const {
    auto conn = headers.connection();
    if (http_version == 10) return iequals(conn, "keep-alive");
    else                    return !iequals(conn, "close");
}

string Message::to_string (const std::vector<string>& pieces) {
    string r;
    for (auto piece: pieces) { r += piece; }
    return r;
}

void Message::compress_body(Body& dest) {
    for(auto& part: body.parts) {
        auto data = compressor->compress(part);
        if (data) dest.parts.emplace_back(std::move(data));
    }
    dest.parts.emplace_back(compressor->flush());
}



}}}
