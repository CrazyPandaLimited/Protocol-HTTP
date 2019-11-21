#pragma once
#include "Request.h"
#include "Response.h"

namespace panda { namespace protocol { namespace http {

constexpr const size_t SIZE_UNLIMITED = size_t(-1);

struct MessageParser {
    size_t max_headers_size;
    size_t max_body_size;

protected:
    MessageParser () {
        max_headers_size = SIZE_UNLIMITED;
        max_body_size    = SIZE_UNLIMITED;
    }

    MessageParser (const MessageParser&) = delete;
    MessageParser (MessageParser&&)      = default;

    inline void reset () {
        message            = nullptr;
        request            = nullptr;
        response           = nullptr;
        mark               = nullptr;
        headers_so_far     = 0;
        headers_finished   = false;
        has_content_length = false;
        content_length     = 0;
        body_so_far        = 0;
    }

    template <class F1, class F2> size_t parse (const string& buffer, F1&& after_headers_cb, F2&& no_body_cb);

protected:
    MessageSP message;
    Request*  request;
    Response* response;
    int       cs; // ragel state
    ptrdiff_t mark;
    string    acc; // contains unfinished field and used to parse messages that come in fragments
    string    field_name;
    size_t    headers_so_far;
    bool      headers_finished;
    bool      has_content_length;
    uint64_t  content_length;
    size_t    body_so_far;
    size_t    chunk_length;
    size_t    chunk_so_far;
};

}}}
