#pragma once

#include <memory>

#include <panda/string.h>
#include <panda/excepted.h>

#include "Defines.h"
#include "Request.h"
#include "MessageParser.h"
#include "MessageIterator.h"
#include "ParserError.h"

namespace panda { namespace protocol { namespace http {

struct RequestFactory : virtual Refcnt {
    virtual RequestSP create() const { return make_iptr<Request>(); }
};

class RequestParser : public MessageParser<RequestParser, Request> {
public:
    virtual ~RequestParser();
    RequestParser(RequestFactorySP request_factory = make_iptr<RequestFactory>());

    using MessageParser::max_body_size;

    struct Result {
        RequestSP request;
        size_t position;
        excepted<State, ParserError> state;
    };

    using ResultSP = iptr<Result>;
    using ResultIterator = MessageIterator<RequestParser, Result>;

    Result parse_first(const string& buffer);
    ResultIterator parse(const string& buffer);

private:
    enum class FinalFlag {
        CONTINUE, RESET
    };
    Result reset_and_build_result(bool is_valid, size_t position, const excepted<State, ParserError>& state);
    Result build_result(FinalFlag reset, size_t position);

    RequestFactorySP request_factory_;
};

}}} // namespace panda::protocol::http
