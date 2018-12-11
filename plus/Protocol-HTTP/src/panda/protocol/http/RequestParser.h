#pragma once

#include <memory>

#include <panda/string.h>

#include "Defines.h"
#include "Request.h"
#include "MessageParser.h"
#include "MessageIterator.h"

namespace panda { namespace protocol { namespace http {

class RequestFactory : virtual Refcnt {
    virtual RequestSP create() const { return make_iptr<Request>(); }
};

class RequestParser : public MessageParser<RequestParser, Request> {
public:
    virtual ~RequestParser();
    RequestParser(RequestFactorySP request_factory = make_iptr<RequestFactory>());
    
    struct Result {
        RequestSP request;
        size_t position;
        State state;
    };
    
    using ResultSP = iptr<Result>;
    using ResultIterator = MessageIterator<RequestParser, Result>;

    Result parse_first(const string& buffer);
    ResultIterator parse(const string& buffer);

    Result reset_and_build_result(bool is_valid, size_t position, State state);

private:
    RequestFactorySP request_factory_;
};

}}} // namespace panda::protocol::http
