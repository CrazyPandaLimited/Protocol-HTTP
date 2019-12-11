#pragma once
#include "panda/string.h"
#include "../Body.h"

namespace panda { namespace protocol { namespace http { namespace compression {

struct Compressor {
    static const constexpr std::size_t RX_BUFF_SCALE = 10;

    Compressor(size_t& max_body_size_):max_body_size{max_body_size_} {}
    Compressor(const Compressor& ) = delete;
    Compressor(Compressor&& ) = delete;

    virtual bool uncompress(const string& piece, Body& body) noexcept = 0;
    virtual void reset() noexcept = 0;

    virtual ~Compressor() {}
    size_t unpacked_bytes = 0;
    size_t acked_bytes = 0;
    size_t& max_body_size;
    bool rx_done = false;
};

}}}};
