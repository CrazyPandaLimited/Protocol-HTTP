#pragma once
#include "Request.h"
#include "Response.h"
#include "compression/Gzip.h"

namespace panda { namespace protocol { namespace http {

constexpr const size_t SIZE_UNLIMITED = size_t(-1);

struct MessageParser {
    size_t max_headers_size = SIZE_UNLIMITED;
    size_t max_body_size    = SIZE_UNLIMITED;
    bool   uncompress_content = true;   // false have sense only for proxies

protected:
    MessageSP       message;
    RequestSP       request;
    ResponseSP      response;
    State           state; // high-level state
    int             cs;    // ragel state
    bool            has_content_length;
    uint64_t        content_length;
    std::error_code error;

    MessageParser(): gzip{max_body_size} {
        /* zlib supports deflate and gzip streams uncompression. Use the same object */
        compressors[0] = compressors[1] = &gzip;
    }

    MessageParser (const MessageParser&) = delete;
    MessageParser (MessageParser&&)      = delete;

    inline void reset () {
        message            = nullptr;
        request            = nullptr;
        response           = nullptr;
        state              = State::headers;
        mark               = -1;
        marked             = false;
        headers_so_far     = 0;
        headers_finished   = false;
        has_content_length = false;
        content_length     = 0;
        body_so_far        = 0;
        error.clear();

        if (compressor) {
            compressor->reset();
            compressor = nullptr;
        }
    }

    template <class F1, class F2> size_t parse (const string& buffer, F1&& after_headers_cb, F2&& no_body_cb);

    void set_error (const std::error_code& e) {
        error = e;
        state = State::error;
    }

    compression::Compressor *compressor = nullptr;

private:
    ptrdiff_t mark;
    bool      marked;
    string    acc;
    size_t    headers_so_far;
    bool      headers_finished;
    size_t    body_so_far;
    size_t    chunk_length;
    size_t    chunk_so_far;

    compression::Gzip gzip;
    compression::Compressor *compressors[2];
    std::uint8_t compr = 0;

    size_t machine_exec (const string& buffer, size_t off);
};

}}}
