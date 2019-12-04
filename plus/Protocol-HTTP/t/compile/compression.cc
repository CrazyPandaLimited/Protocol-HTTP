#include "../lib/test.h"

#define TEST(name) TEST_CASE("compile-compression: " name, "[compile-compression]")

TEST("Accept-Encoding") {
    SECTION("identity") {
        auto req = Request::Builder().allow_compression(compression::IDENTITY).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n\r\n");
        CHECK(req->compression_mask() == compression::IDENTITY);
    }

    SECTION("identity, identity") {
        auto req = Request::Builder()
                .allow_compression(compression::IDENTITY)
                .allow_compression(compression::IDENTITY)
            .build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n\r\n");
        CHECK(req->compression_mask() == compression::IDENTITY);
    }

    SECTION("(empty aka default)") {
        auto req = Request::Builder().build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n\r\n");
        CHECK((req->compression_mask() & compression::IDENTITY));
    }

    SECTION("gzip") {
        auto req = Request::Builder().allow_compression(compression::GZIP).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: gzip\r\n"
        "\r\n");
        CHECK((req->compression_mask() & compression::GZIP));
        CHECK((req->compression_mask() & compression::IDENTITY));
    }

    SECTION("deflate") {
        auto req = Request::Builder().allow_compression(compression::DEFLATE).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: deflate\r\n"
        "\r\n");
        CHECK((req->compression_mask() & compression::DEFLATE));
        CHECK((req->compression_mask() & compression::IDENTITY));
    }

    SECTION("deflate, gzip") {
        auto req = Request::Builder()
                .allow_compression(compression::DEFLATE)
                .allow_compression(compression::GZIP)
            .build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: deflate, gzip\r\n"
        "\r\n");
        CHECK((req->compression_mask() & compression::GZIP));
        CHECK((req->compression_mask() & compression::DEFLATE));
        CHECK((req->compression_mask() & compression::IDENTITY));
    }

    SECTION("deflate, gzip, gzip, gzip, gzip, gzip, gzip, gzip, gzip, identity") {
        auto req = Request::Builder()
                .allow_compression(compression::DEFLATE)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::IDENTITY)
            .build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: deflate, gzip, gzip, gzip, gzip, gzip, gzip\r\n"
        "\r\n");
    }
}
