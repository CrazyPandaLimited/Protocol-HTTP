#include "Message.h"
#include <algorithm>

namespace panda { namespace protocol { namespace http {

bool Message::keep_alive () const {
    auto conn = headers.connection();
    if (http_version == 11) return !iequals(conn, "close");
    else                    return iequals(conn, "keep-alive");
}

}}}
