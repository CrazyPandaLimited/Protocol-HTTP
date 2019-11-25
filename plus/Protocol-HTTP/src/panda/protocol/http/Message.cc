#include "Message.h"
#include <algorithm>

namespace panda { namespace protocol { namespace http {

bool Message::keep_alive () const {
    auto conn = headers.connection();
    if (http_version == 10) return iequals(conn, "keep-alive");
    else                    return !iequals(conn, "close");
}

}}}
