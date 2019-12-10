#include "Gzip.h"
#include <iostream>

namespace panda { namespace protocol { namespace http { namespace compression {


static bool check_zlib(){
    string compiled_verison{ZLIB_VERSION};
    string loaded_version{zlibVersion()};

     if (compiled_verison != loaded_version) {
         std::cerr << "zlib version mismatch, loaded: "  << loaded_version << ", compiled" << compiled_verison << "\n";
         std::abort();
         return false;
     }
     return true;
}

static bool initialized = check_zlib();

Gzip::Gzip(size_t& max_body_size_):Compressor(max_body_size_) {
    rx_stream.avail_in = 0;
    rx_stream.next_in = Z_NULL;
    rx_stream.zalloc = Z_NULL;
    rx_stream.zfree = Z_NULL;
    rx_stream.opaque = Z_NULL;

    tx_stream.avail_in = 0;
    tx_stream.next_in = 0;
    tx_stream.zalloc = Z_NULL;
    tx_stream.zfree = Z_NULL;
    tx_stream.opaque = Z_NULL;

    // https://stackoverflow.com/questions/1838699/how-can-i-decompress-a-gzip-stream-with-zlib
    int err;
    err = inflateInit2(&rx_stream, 16 + MAX_WBITS);
    if (err != Z_OK) { throw "zlib::inflateInit";}
}

Gzip::~Gzip() {
    int err;
    err = inflateEnd(&rx_stream);
    assert(err == Z_OK);
}

bool Gzip::uncompress(const string& piece, Body& body) noexcept {
    if (rx_done) { return false; }
    string acc;
    acc.reserve(piece.size() * RX_BUFF_SCALE);

    rx_stream.next_out = reinterpret_cast<Bytef*>(acc.buf());
    rx_stream.avail_out = static_cast<uInt>(acc.capacity());
    rx_stream.avail_in = static_cast<uInt>(piece.size());
    rx_stream.next_in = (Bytef*)(piece.data());

    auto consume_buff = [&](bool final){
        acc.length(acc.capacity() - rx_stream.avail_out);
        body.parts.emplace_back(std::move(acc));
        consumed_bytes += (piece.size() - rx_stream.avail_in);
        if (!final) {
            acc.clear();
            acc.reserve(piece.size() * RX_BUFF_SCALE);
            rx_stream.next_out = reinterpret_cast<Bytef*>(acc.buf());
            rx_stream.avail_out = static_cast<uInt>(acc.capacity());
        }
    };

    do {
        int r = ::inflate(&rx_stream, Z_SYNC_FLUSH);
        switch (r) {
        case Z_STREAM_END:
            consume_buff(true);
            rx_done = true;
            return true;
        case Z_OK:
            consume_buff(false);
            continue;
        case Z_BUF_ERROR:
            if (rx_stream.avail_out != acc.capacity()) {
                consume_buff(false);
                continue;
            } else {
                assert(!rx_stream.avail_in);
                return true;
            }
        default:
            return false;
        }
    } while (true);
}

void Gzip::reset() noexcept {
    rx_done = false;
    consumed_bytes = 0;
}


}}}}
