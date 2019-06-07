#pragma once

#include "Message.h"

#include <panda/string.h>
#include <panda/refcnt.h>
#include <panda/lib.h>

#include "Defines.h"

namespace panda { namespace protocol { namespace http {

class Response : public Message {
public:
    Response();

    Response(int code, const string& reason, Header&& header, BodySP body, const string& http_version);

    int code;
    string message;

    std::ostream& print(std::ostream& os) const override;

protected:
    // restrict stack allocation
    virtual ~Response();

private:
    // disable copying as we disabled stack usage
    Response(const Response&) = delete;
    Response& operator=(const Response&) = delete;

};

inline
std::ostream& operator<<(std::ostream& os, const ResponseSP& ptr) {
    if(ptr) {
        os << *ptr;
    }
    return os;
}

}}} // namespace panda::protocol::http
