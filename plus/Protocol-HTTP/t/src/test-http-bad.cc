#include "../lib/test.h"

TEST_CASE("double first line", "[bad]") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";
    http::RequestSP request = request_parser.parse_first(raw).request;
    
    REQUIRE(!request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
}

TEST_CASE("bad first line", "[bad]") {
    http::RequestParser request_parser;
    string raw =
        "\r\n"
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";
    http::RequestSP request = request_parser.parse_first(raw).request;
    
    REQUIRE(!request->is_valid());
}

TEST_CASE("space before colon in header field", "[bad]") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host : host1\r\n"
        "\r\n";
    http::RequestSP request = request_parser.parse_first(raw).request;
    
    REQUIRE(!request->is_valid());
}

TEST_CASE("space before header field", "[bad]") {
    http::RequestParser request_parser;
    string raw =
        "\r\n"
        "GET / HTTP/1.0\r\n"
        " Host: host1\r\n"
        "\r\n";
    http::RequestSP request = request_parser.parse_first(raw).request;

    REQUIRE(!request->is_valid());
}
