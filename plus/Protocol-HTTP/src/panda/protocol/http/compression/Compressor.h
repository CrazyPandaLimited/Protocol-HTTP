#pragma once
#include <system_error>
#include "panda/string.h"
#include "../Body.h"


namespace panda { namespace protocol { namespace http { namespace compression {

enum class Mode { none = 0, compress, uncompress };

struct Compressor {
    static const constexpr std::size_t RX_BUFF_SCALE = 10;

    Compressor(){}
    Compressor(const Compressor& ) = delete;
    Compressor(Compressor&& ) = delete;

    virtual void prepare_uncompress(size_t& max_body_size) noexcept = 0;
    virtual void prepare_compress() noexcept = 0;
    virtual void reset() noexcept = 0;

    virtual std::error_code uncompress(const string& piece, Body& body) noexcept = 0;
    bool eof() noexcept  { return rx_done ;}

    virtual ~Compressor() {}

protected:
    size_t* max_body_size = nullptr;
    Mode mode = Mode::none;
    bool rx_done = false;
};

}}}};
