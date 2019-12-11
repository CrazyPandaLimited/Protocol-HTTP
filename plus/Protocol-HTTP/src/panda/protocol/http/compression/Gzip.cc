#include "Gzip.h"
#include <iostream>
#include "../Error.h"

namespace panda { namespace protocol { namespace http { namespace compression {


static bool check_zlib(){
    string compiled_verison{ZLIB_VERSION};
    string loaded_version{zlibVersion()};

     if (compiled_verison != loaded_version) {
         std::cerr << "zlib version mismatch, loaded: "  << loaded_version << ", compiled" << compiled_verison << "\n";
         std::abort();
     }
     return true;
}

static bool initialized = check_zlib();

Gzip::~Gzip() {
    int err = Z_OK;
    if (mode == Mode::uncompress) {
        err = inflateEnd(&rx_stream);
    }
    assert(err == Z_OK);
}

void Gzip::prepare_uncompress(size_t& max_body_size_) noexcept{
    assert(mode == Mode::none);
    max_body_size = &max_body_size_;
    rx_stream.total_out = 0;
    rx_stream.total_in = 0;
    rx_stream.avail_in = 0;
    rx_stream.next_in = Z_NULL;
    rx_stream.zalloc = Z_NULL;
    rx_stream.zfree = Z_NULL;
    rx_stream.opaque = Z_NULL;
    mode = Mode::uncompress;
    // https://stackoverflow.com/questions/1838699/how-can-i-decompress-a-gzip-stream-with-zlib
    int err = inflateInit2(&rx_stream, 16 + MAX_WBITS);
    assert(err == Z_OK);
}

void Gzip::prepare_compress() noexcept {
    std::abort();
}


std::error_code Gzip::uncompress(const string& piece, Body& body) noexcept {
    assert(mode == Mode::uncompress);
    if (rx_done) { return errc::uncompression_failure; }
    string acc;
    acc.reserve(piece.size() * RX_BUFF_SCALE);

    rx_stream.next_out = reinterpret_cast<Bytef*>(acc.buf());
    rx_stream.avail_out = static_cast<uInt>(acc.capacity());
    rx_stream.avail_in = static_cast<uInt>(piece.size());
    rx_stream.next_in = (Bytef*)(piece.data());
    size_t consumed_bytes = 0;

    std::error_code errc;
    auto consume_buff = [&](bool final){
        if (rx_stream.total_out >= *max_body_size) {
            errc = errc::body_too_large;
            return false;
        }

        acc.length(acc.capacity() - rx_stream.avail_out);
        body.parts.emplace_back(std::move(acc));
        consumed_bytes += (piece.size() - rx_stream.avail_in);
        if (!final) {
            acc.clear();
            acc.reserve(piece.size() * RX_BUFF_SCALE);
            rx_stream.next_out = reinterpret_cast<Bytef*>(acc.buf());
            rx_stream.avail_out = static_cast<uInt>(acc.capacity());
        }
        return true;
    };

    bool enough = false;
    do {
        int r = ::inflate(&rx_stream, Z_SYNC_FLUSH);
        switch (r) {
        case Z_STREAM_END:
            if (!consume_buff(true)) { break; }
            if (consumed_bytes != piece.size()) { errc = errc::uncompression_failure; }
            else                                { rx_done = true; }
            enough = true;
            break;
        case Z_OK:
            if (!consume_buff(false)) { break; }
            continue;
        case Z_BUF_ERROR:
            if (rx_stream.avail_out != acc.capacity()) {
                if (!consume_buff(false)) { break; }
                continue;
            } else {
                assert(!rx_stream.avail_in);
                enough = true;
                break;
            }
        default:
            errc = errc::uncompression_failure;
            break;
        }
    } while (!errc && !enough);
    return  errc;
}

void Gzip::reset() noexcept {
    if (mode == Mode::uncompress) {
        rx_done = false;
        rx_stream.total_out = 0;
        rx_stream.total_in = 0;
        rx_stream.avail_in = 0;

        int err = inflateReset2(&rx_stream, 16 + MAX_WBITS);
        assert(err == Z_OK);
    }
}


}}}}
