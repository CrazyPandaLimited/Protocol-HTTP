#include "Message.h"
#include <algorithm>

namespace panda { namespace protocol { namespace http {

bool Message::keep_alive () const {
    auto conn = headers.connection();
    if (http_version == HttpVersion::v1_1) return !iequals(conn, "close");
    else                                   return iequals(conn, "keep-alive");
}

}}}
