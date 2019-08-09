#pragma once

#include <deque>

#include <panda/string.h>
#include <panda/refcnt.h>
#include <panda/excepted.h>

#include "Defines.h"
#include "Response.h"
#include "Request.h"
#include "MessageParser.h"
#include "MessageIterator.h"
#include "ParserError.h"

namespace panda { namespace protocol { namespace http {

class ResponseParser : public MessageParser<ResponseParser, Response> {
public:
    virtual ~ResponseParser();
    ResponseParser();

    struct Result {
        RequestSP request;
        ResponseSP response;
        size_t position;
        excepted<State, ParserError> state;
    };

    using ResultSP = iptr<Result>;
    using ResultIterator = MessageIterator<ResponseParser, Result>;

    Result parse_first(const string& buffer);
    ResultIterator parse(const string& buffer);

    ResponseSP create_message();
    Result reset_and_build_result(bool is_valid, size_t position, State state);

    void append_request(RequestSP request);

    ResponseSP message() override;

    bool no_pending_requests() const { return requests_.empty(); }

private:
    std::deque<RequestSP> requests_;
};

}}} // namespace panda::protocol::http
