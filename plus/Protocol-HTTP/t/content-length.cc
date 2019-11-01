#include "lib/test.h"

#define TEST(name) TEST_CASE("content-length: " name, "[content-length]")

TEST("content as single buffer") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 23\r\n"
        "\r\n"
        "Wikipedia in\r\n\r\nchunks."
        ;

    auto result = p.parse(raw);
    CHECK(result.state == State::done);
    
    auto req = result.request;
    
    CHECK(req->headers.fields.size() == 1);
    CHECK(req->headers.get("Content-Length") == "23");
    CHECK(req->body.to_string() == "Wikipedia in\r\n\r\nchunks.");
}

TEST("content in parts") {
    RequestParser p;

    auto result = p.parse("POST /upload HTTP/1.1\r\nContent-Length: 23\r\n\r");
    CHECK(result.state == State::not_yet);

    result = p.parse("\n");
    CHECK(result.state == State::in_body);

    result = p.parse("W");
    CHECK(result.state == State::in_body);
    
    result = p.parse("i");
    CHECK(result.state == State::in_body);
    
    result = p.parse("kipedia in\r\n");
    CHECK(result.state == State::in_body);
    
    result = p.parse("\r\nchunks.");
    CHECK(result.state == State::done);

    auto req = result.request;
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

    auto result = p.parse(raw);
    CHECK(result.state == State::done);
    
    auto req = result.request;
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

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    CHECK(req->headers.fields.size() == 1);
    CHECK(req->headers.get("Content-LENGTH") == "1");
    CHECK(req->body.to_string() == "1");
}

TEST("unreal content length request") {
    string raw = GENERATE(
        string("POST /upload HTTP/1.1\r\n"
        "Content-Length: 100500999999999999099999999\r\n"
        "\r\n"
        "1234567890")
    );

    RequestParser p;
    CHECK(p.parse(raw).error);
}

TEST("unreal content lentgh response") {
    string raw = GENERATE(
        string("HTTP/1.1 200 OK\r\n"
        "Content-Length: 100500999999999999099999999\r\n"
        "\r\n"
        "1234567890")
        ,
        string("HTTP/1.1 11111 OK\r\n"
        "Content-Length: 10\r\n"
        "\r\n"
        "1234567890")
    );

    ResponseParser p;
    p.set_request(new Request(Method::GET, new URI("http://dev/"), Header(), Body()));
    CHECK(p.parse(raw).error);
}
