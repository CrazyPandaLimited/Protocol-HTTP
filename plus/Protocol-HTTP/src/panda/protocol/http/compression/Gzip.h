#pragma once

#include "Compressor.h"
#include <zlib.h>

namespace panda { namespace protocol { namespace http { namespace compression {

struct Gzip: Compressor {
    Gzip(size_t& max_body_size_);
    ~Gzip() override;

    bool uncompress(const string& piece, Body& body) noexcept override;
    void reset() noexcept override;

private:
    z_stream rx_stream;
};

}}}}
