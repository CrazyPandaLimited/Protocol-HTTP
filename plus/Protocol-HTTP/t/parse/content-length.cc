#include "../lib/test.h"

#define TEST(name) TEST_CASE("parse-content-length: " name, "[parse-content-length]")

TEST("content as single buffer") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 23\r\n"
        "\r\n"
        "Wikipedia in\r\n\r\nchunks."
        ;

    auto req = p.parse(raw).request;
    CHECK(req->state() == State::done);
    CHECK(req->headers.fields.size() == 1);
    CHECK(req->headers.get("Content-Length") == "23");
    CHECK(req->body.to_string() == "Wikipedia in\r\n\r\nchunks.");
}

TEST("content in parts") {
    RequestParser p;

    auto req = p.parse("POST /upload HTTP/1.1\r\nContent-Length: 23\r\n\r").request;
    CHECK(req->state() == State::headers);

    p.parse("\n");
    CHECK(req->state() == State::body);

    p.parse("W");
    CHECK(req->state() == State::body);
    
    p.parse("i");
    CHECK(req->state() == State::body);
    
    p.parse("kipedia in\r\n");
    CHECK(req->state() == State::body);
    
    p.parse("\r\nchunks.");
    CHECK(req->state() == State::done);
    CHECK(req->headers.fields.size() == 1);
    CHECK(req->headers.get("Content-Length") == "23");
    CHECK(req->body.to_string() == "Wikipedia in\r\n\r\nchunks.");
}

TEST("zero content-length") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 0\r\n"
        "\r\n"
        ;

    auto req = p.parse(raw).request;
    CHECK(req->state() == State::done);
    CHECK(req->headers.fields.size() == 1);
    CHECK(req->headers.get("Content-Length") == "0");
    CHECK(req->body.to_string() == "");
}

TEST("case insensitive") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "content-length: 1\r\n"
        "\r\n"
        "1";

    auto req = p.parse(raw).request;
    CHECK(req->state() == State::done);
    CHECK(req->headers.fields.size() == 1);
    CHECK(req->headers.get("Content-LENGTH") == "1");
    CHECK(req->body.to_string() == "1");
}

TEST("multiple content length header") {
    string raw = GENERATE(
        string("POST /upload HTTP/1.1\r\n"
        "Content-Length: 10\r\n"
        "Content-Length: 10\r\n"
        "\r\n"
        "1234567890")
    );

    RequestParser p;
    CHECK(p.parse(raw).request->error() == errc::multiple_content_length);
}
