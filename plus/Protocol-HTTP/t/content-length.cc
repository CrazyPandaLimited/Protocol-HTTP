#include "lib/test.h"

TEST_CASE("post with content-length content as single buffer", "[content-length]") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 23\r\n"
        "\r\n"
        "Wikipedia in\r\n\r\nchunks."
        ;

    auto result = p.parse(raw);
    REQUIRE(result.state == RequestParser::State::done);
    
    auto req = result.request;
    
    REQUIRE(req->method == Method::POST);
    REQUIRE(req->http_version == "1.1");
    REQUIRE(req->headers.fields.size() == 1);
    REQUIRE(req->headers.get_field("Content-Length") == "23");
    REQUIRE(req->body.as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}

TEST_CASE("post with content-length content in parts", "[content-length]") {
    RequestParser p;

    auto result = p.parse("POST /upload HTTP/1.1\r\nContent-Length: 23\r\n\r");
    REQUIRE(result.state == RequestParser::State::not_yet);

    result = p.parse("\n");
    REQUIRE(result.state == RequestParser::State::in_body);

    result = p.parse("W");
    REQUIRE(result.state == RequestParser::State::in_body);
    
    result = p.parse("i");
    REQUIRE(result.state == RequestParser::State::in_body);
    
    result = p.parse("kipedia in\r\n");
    REQUIRE(result.state == RequestParser::State::in_body);
    
    result = p.parse("\r\nchunks.");
    REQUIRE(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::POST);
    REQUIRE(req->http_version == "1.1");
    REQUIRE(req->headers.fields.size() == 1);
    REQUIRE(req->headers.get_field("Content-Length") == "23");
    REQUIRE(req->body.as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}

TEST_CASE("post with zero content-length", "[content-length]") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 0\r\n"
        "\r\n"
        ;

    auto result = p.parse(raw);
    REQUIRE(result.state == RequestParser::State::done);
    
    auto req = result.request;
    REQUIRE(req->method == Method::POST);
    REQUIRE(req->http_version == "1.1");
    REQUIRE(req->headers.fields.size() == 1);
    REQUIRE(req->headers.get_field("Content-Length") == "0");
    REQUIRE(req->body.as_buffer() == "");
}

TEST_CASE("post single request", "[content-length]") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 2\r\n"
        "\r\n"
        ;

    auto result = p.parse(raw);
    REQUIRE(result.state == RequestParser::State::in_body);

    result = p.parse("X");
    REQUIRE(result.state == RequestParser::State::in_body);

    result = p.parse("X");
    REQUIRE(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::POST);
    REQUIRE(req->http_version == "1.1");
    REQUIRE(req->headers.fields.size() == 1);
    REQUIRE(req->headers.get_field("Content-Length") == "2");
    REQUIRE(req->body.as_buffer() == "XX");
}

TEST_CASE("post iterator multiple messages", "[content-length]") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 2\r\n"
        "\r\n"
        ;

    auto result1 = p.parse(raw);
    REQUIRE(result1.state == RequestParser::State::in_body);

    result1 = p.parse("X");
    REQUIRE(result1.state == RequestParser::State::in_body);

    result1 = p.parse("X" + raw);
    REQUIRE(result1.state == RequestParser::State::done);

    auto req1 = result1.request;
    REQUIRE(req1->method == Method::POST);
    REQUIRE(req1->http_version == "1.1");
    REQUIRE(req1->headers.fields.size() == 1);
    REQUIRE(req1->headers.get_field("Content-Length") == "2");
    REQUIRE(req1->body.as_buffer() == "XX");

    // parse nto the second result with the same iterator
    auto result2 = p.parse(raw);
    REQUIRE(result2.state == RequestParser::State::in_body);

    result2 = p.parse("YY");
    REQUIRE(result2.state == RequestParser::State::done);

    auto req2 = result2.request;
    REQUIRE(req2->method == Method::POST);
    REQUIRE(req2->http_version == "1.1");
    REQUIRE(req2->headers.fields.size() == 1);
    REQUIRE(req2->headers.get_field("Content-Length") == "2");
    REQUIRE(req2->body.as_buffer() == "YY");
   
    // ensure that the first request is not modified 
    REQUIRE(req1->body.as_buffer() == "XX");
}
