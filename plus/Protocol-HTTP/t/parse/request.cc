#include "../lib/test.h"

#define TEST(name) TEST_CASE("parse-request: " name, "[parse-request]")

TEST("get") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";

    auto req = p.parse(raw).request;
    CHECK(req->state() == State::done);
    CHECK(req->method == Method::GET);
    CHECK(req->http_version == 10);
    CHECK(req->uri->to_string() == "/");
}

TEST("post") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 23\r\n"
        "\r\n"
        "Wikipedia in\r\n\r\nchunks."
        ;

    auto req = p.parse(raw).request;
    CHECK(req->state() == State::done);
    CHECK(req->method == Method::POST);
    CHECK(req->http_version == 11);
    CHECK(req->uri->to_string() == "/upload");
}

TEST("request without length") {
    RequestParser p;
    string body = GENERATE(string(""), string("1"));
    string raw =
        "GET / HTTP/1.1\r\n"
        "Host: host1\r\n"
        "\r\n" + body;

    auto req = p.parse(raw).request;
    CHECK(req->state() == State::done);
    CHECK(req->http_version == 11);
    CHECK_FALSE(req->body.length());
}

TEST("fragmented method") {
    RequestParser p;

    string v[] = {
        "G", "ET / HTTP/1", ".0\r\n"
        "Header1: header1\r\n"
        "\r\n"
    };

    RequestSP req;
    for (auto s : v) {
        if (req) CHECK(req->state() != State::done);
        req = p.parse(s).request;
    }
    CHECK(req->state() == State::done);
    CHECK(req->method == Method::GET);
    CHECK(req->http_version == 10);
    CHECK(req->headers.get("Header1") == "header1");
}

TEST("parsing request byte by byte") {
    RequestParser p;
    string s =
        "GET /uri HTTP/1.0\r\n"
        "Header1: header1\r\n"
        "Header2: header2\r\n"
        "\r\n";

    const size_t CHUNK = GENERATE(1, 10);
    RequestSP req;
    while (s) {
        if (req) CHECK(req->state() != State::done);
        req = p.parse(s.substr(0, CHUNK)).request;
        s.offset(CHUNK < s.length() ? CHUNK : s.length());
    }
    CHECK(req->state() == State::done);
    CHECK(req->method == Method::GET);
    CHECK(req->http_version == 10);
    CHECK(req->headers.get("Header1") == "header1");
    CHECK(req->headers.get("Header2") == "header2");
}

TEST("double first line") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";

    auto req = p.parse(raw).request;
    CHECK(req->error());
    CHECK(req->method == Method::GET);
    CHECK(req->http_version == 10);
}

TEST("bad first line") {
    RequestParser p;
    string raw =
        "\r\n"
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";
    CHECK(p.parse(raw).request->error());
}
