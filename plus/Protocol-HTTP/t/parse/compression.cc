#include "../lib/test.h"

#define TEST(name) TEST_CASE("parse-compression: " name, "[parse-compression]")

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
