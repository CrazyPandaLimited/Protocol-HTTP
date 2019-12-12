#include "Message.h"
#include <algorithm>

namespace panda { namespace protocol { namespace http {

bool Message::keep_alive () const {
    auto conn = headers.connection();
    if (http_version == 10) return iequals(conn, "keep-alive");
    else                    return !iequals(conn, "close");
}

compression::BodyGuard Message::maybe_compress() {
    if ((compressed == compression::IDENTITY) || body.parts.empty()) {
        return compression::BodyGuard{};
    }
    compression::BodyGuard body_holder(&body);
    Body compressed;
    for(auto& part: body.parts) {
        auto data = compressor->compress(part);
        if (data) {
            compressed.parts.emplace_back(std::move(data));
        }
    }
    compressed.parts.emplace_back(compressor->flush());
    body = std::move(compressed);
    return body_holder;
}

}}}
