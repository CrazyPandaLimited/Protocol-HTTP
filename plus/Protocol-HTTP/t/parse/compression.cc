#include "../lib/test.h"

#define TEST(name) TEST_CASE("parse-compression: " name, "[parse-compression]")

#if 0
/* ACCEPT-ENCODING */
TEST("Accept-Encoding: gzip") {
    RequestParser p;
    string raw = "GET / HTTP/1.1\r\n"
        "Accept-Encoding: gzip\r\n"
    "\r\n";
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK(req->headers.get("Accept-Encoding") == "gzip");
    CHECK((req->compression_mask() & compression::GZIP));
    CHECK((req->compression_mask() & compression::IDENTITY));
}

TEST("Accept-Encoding: gzip;q=1.0") {
    RequestParser p;
    string raw = "GET / HTTP/1.1\r\n"
        "Accept-Encoding: gzip;q=1.0\r\n"
    "\r\n";
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK((req->compression_mask() & compression::GZIP));
    CHECK((req->compression_mask() & compression::IDENTITY));
}

TEST("Accept-Encoding: gzip;q=0.002") {
    RequestParser p;
    string raw = "GET / HTTP/1.1\r\n"
        "Accept-Encoding: gzip;q=0.002\r\n"
    "\r\n";
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK((req->compression_mask() & compression::GZIP));
    CHECK((req->compression_mask() & compression::IDENTITY));
}

TEST("Accept-Encoding: gzip;q=0.0") {
    RequestParser p;
    string raw = "GET / HTTP/1.1\r\n"
        "Accept-Encoding: gzip;q=0.0\r\n"
    "\r\n";
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK(!(req->compression_mask() & compression::GZIP));
    CHECK((req->compression_mask() & compression::IDENTITY));
}

TEST("Accept-Encoding: gzip;q=0.000") {
    RequestParser p;
    string raw = "GET / HTTP/1.1\r\n"
        "Accept-Encoding: gzip;q=0.000\r\n"
    "\r\n";
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK(!(req->compression_mask() & compression::GZIP));
    CHECK((req->compression_mask() & compression::IDENTITY));
}

TEST("Accept-Encoding: (empty)") {
    RequestParser p;
    string raw = "GET / HTTP/1.1\r\n"
        "Accept-Encoding:\r\n"
    "\r\n";
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK((req->compression_mask() == compression::IDENTITY));
}

TEST("Accept-Encoding: gzip, deflate, br, *;q=0") {
    RequestParser p;
    string raw = "GET / HTTP/1.1\r\n"
        "Accept-Encoding: gzip, deflate, br, *;q=0\r\n"
    "\r\n";
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK((req->compression_mask() & compression::GZIP));
    CHECK((req->compression_mask() & compression::DEFLATE));
    CHECK((req->compression_mask() & compression::IDENTITY));
}


TEST("Accept-Encoding: gzip;q=1.0, deflate;q=0") {
    RequestParser p;
    string raw = "GET / HTTP/1.1\r\n"
        "Accept-Encoding: gzip;q=1.0, deflate;q=0\r\n"
    "\r\n";
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK((req->compression_mask() & compression::GZIP));
    CHECK(!(req->compression_mask() & compression::DEFLATE));
    CHECK((req->compression_mask() & compression::IDENTITY));
}


TEST("Accept-Encoding: gzip;q=0.123, deflate;q=0.120") {
    RequestParser p;
    string raw = "GET / HTTP/1.1\r\n"
        "Accept-Encoding: gzip;q=0.123, deflate;q=0.120\r\n"
    "\r\n";
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK((req->compression_mask() & compression::GZIP));
    CHECK((req->compression_mask() & compression::DEFLATE));
    CHECK((req->compression_mask() & compression::IDENTITY));
}

/* CONTENT-ENCODING */

TEST("Content-Encoding: empty") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "\r\n"
        ;
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK(req->compressed == compression::IDENTITY);
}

TEST("Content-Encoding: identity") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Encoding: identity\r\n"
        "\r\n"
        ;
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK(req->compressed == compression::IDENTITY);
}

TEST("Content-Encoding: gzip") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Encoding: gzip\r\n"
        "\r\n"
        ;
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK(req->compressed == compression::GZIP);
}

TEST("Content-Encoding: deflate") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Encoding: deflate\r\n"
        "\r\n"
        ;
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK(req->compressed == compression::DEFLATE);
}

TEST("Content-Encoding: rar") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Encoding: rar\r\n"
        "\r\n"
        ;
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::error);
    CHECK(result.error == errc::unsupported_compression);
}

TEST("Content-Encoding: rar (disabled uncompression)") {
    RequestParser p;
    p.uncompress_content = false;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Encoding: rar\r\n"
        "\r\n"
        ;
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK(req->compressed == compression::IDENTITY);
}

TEST("Content-Encoding: gzip, identity") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Encoding: gzip, identity\r\n"
        "\r\n"
        ;
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK(req->compressed == compression::GZIP);
}

TEST("Content-Encoding: gzip, gzip") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Encoding: gzip, gzip\r\n"
        "\r\n"
        ;
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::error);
    CHECK(result.error == errc::unsupported_compression);
}
#endif

/* compression gzip */
TEST("request with gzip payload (small piece)") {

/*
wireshark captured piece. Generated via

echo 'Lorem ipsum dolor' | gzip | curl -v -i --data-binary @- -H "Content-Encoding: gzip" http://127.0.0.1/

POST / HTTP/1.1
Host: 127.0.0.1
User-Agent: curl/7.67.0
Content-Encoding: gzip
Content-Length: 38
Content-Type: application/x-www-form-urlencoded

............/J.U.,(..UH.../.....N.....
*/
    unsigned char data[] = {
        0x50, 0x4f, 0x53, 0x54, 0x20, 0x2f, 0x20, 0x48,
        0x54, 0x54, 0x50, 0x2f, 0x31, 0x2e, 0x31, 0x0d,
        0x0a, 0x48, 0x6f, 0x73, 0x74, 0x3a, 0x20, 0x31,
        0x32, 0x37, 0x2e, 0x30, 0x2e, 0x30, 0x2e, 0x31,
        0x0d, 0x0a, 0x55, 0x73, 0x65, 0x72, 0x2d, 0x41,
        0x67, 0x65, 0x6e, 0x74, 0x3a, 0x20, 0x63, 0x75,
        0x72, 0x6c, 0x2f, 0x37, 0x2e, 0x36, 0x37, 0x2e,
        0x30, 0x0d, 0x0a, 0x41, 0x63, 0x63, 0x65, 0x70,
        0x74, 0x3a, 0x20, 0x2a, 0x2f, 0x2a, 0x0d, 0x0a,
        0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d,
        0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67,
        0x3a, 0x20, 0x67, 0x7a, 0x69, 0x70, 0x0d, 0x0a,
        0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d,
        0x4c, 0x65, 0x6e, 0x67, 0x74, 0x68, 0x3a, 0x20,
        0x33, 0x38, 0x0d, 0x0a, 0x43, 0x6f, 0x6e, 0x74,
        0x65, 0x6e, 0x74, 0x2d, 0x54, 0x79, 0x70, 0x65,
        0x3a, 0x20, 0x61, 0x70, 0x70, 0x6c, 0x69, 0x63,
        0x61, 0x74, 0x69, 0x6f, 0x6e, 0x2f, 0x78, 0x2d,
        0x77, 0x77, 0x77, 0x2d, 0x66, 0x6f, 0x72, 0x6d,
        0x2d, 0x75, 0x72, 0x6c, 0x65, 0x6e, 0x63, 0x6f,
        0x64, 0x65, 0x64, 0x0d, 0x0a, 0x0d, 0x0a, 0x1f,
        0x8b, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x03, 0xf3, 0xc9, 0x2f, 0x4a, 0xcd, 0x55, 0xc8,
        0x2c, 0x28, 0x2e, 0xcd, 0x55, 0x48, 0xc9, 0xcf,
        0xc9, 0x2f, 0xe2, 0x02, 0x00, 0xe8, 0xd0, 0x4e,
        0xfa, 0x12, 0x00, 0x00, 0x00 };

    string raw(reinterpret_cast<char*>(data), sizeof (data));
    RequestParser p;
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK(req->compressed == compression::GZIP);
    CHECK(req->body.parts.size() == 1);
    CHECK(req->body.parts[0] == "Lorem ipsum dolor\n");
}
