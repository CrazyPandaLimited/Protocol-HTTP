#include "Compressor.h"
#include "Gzip.h"

namespace panda { namespace protocol { namespace http { namespace compression {

static Compressor* create_gzip_compressor() noexcept { return new Gzip(); }

static const CompressorFactory gzip_factory = create_gzip_compressor;
static CompressorFactory brotli_factory = nullptr;

bool register_factory(Compression compression, CompressorFactory& factory) noexcept {
    bool result = false;
    if (compression == Compression::BROTLI && !brotli_factory) {
        brotli_factory = factory;
        result = true;
    }
    return result;
}

CompressorPtr instantiate(Compression compression) noexcept {
    CompressorFactory factory = nullptr;
    switch (compression) {
    /* zlib supports deflate and gzip streams uncompression. Use the same object */
    case Compression::GZIP:
    case Compression::DEFLATE:
        factory = gzip_factory;
        break;
    case Compression::BROTLI:
        factory = brotli_factory;
        break;
    default: /* NOOP */ break;

    }
    if (factory) return CompressorPtr((*factory)());
    return CompressorPtr();
}

}}}}
