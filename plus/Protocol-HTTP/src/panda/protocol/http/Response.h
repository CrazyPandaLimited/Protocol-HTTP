#pragma once
#include "Message.h"

namespace panda { namespace protocol { namespace http {

struct Response : Message {
    int    code;
    string message;

    Response () : code() {}
    Response (int code, const string& reason, Header&& header, const BodySP& body, const string& http_version);

    string full_message () { return panda::to_string(code) + " " + message; }

    std::ostream& print (std::ostream& os) const override;

protected:
    virtual ~Response () {} // restrict stack allocation

private:
    Response (const Response&) = delete;
    Response& operator= (const Response&) = delete;
};
using ResponseSP = iptr<Response>;

std::ostream& operator<< (std::ostream&, const ResponseSP&);

std::vector<string> to_vector (Response* response_ptr);

}}}
