#include "../lib/test.h"

TEST_CASE("double first line", "[bad]") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";
    auto res = request_parser.parse_first(raw);
    REQUIRE_FALSE(res.state);
    http::RequestSP request = res.request;
    
    REQUIRE(!request->is_valid());
    REQUIRE(request->method == Method::GET);
    REQUIRE(request->http_version() == "1.0");
}

TEST_CASE("bad first line", "[bad]") {
    http::RequestParser request_parser;
    string raw =
        "\r\n"
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";
    auto res = request_parser.parse_first(raw);
    REQUIRE_FALSE(res.state);
    http::RequestSP request = res.request;
    
    REQUIRE(!request->is_valid());
}

TEST_CASE("space before colon in header field", "[bad]") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host : host1\r\n"
        "\r\n";
    auto res = request_parser.parse_first(raw);
    REQUIRE_FALSE(res.state);
    http::RequestSP request = res.request;
    
    REQUIRE(!request->is_valid());
}

TEST_CASE("space before header field", "[bad]") {
    http::RequestParser request_parser;
    string raw =
        "\r\n"
        "GET / HTTP/1.0\r\n"
        " Host: host1\r\n"
        "\r\n";
    auto res = request_parser.parse_first(raw);
    REQUIRE_FALSE(res.state);
    http::RequestSP request = res.request;

    REQUIRE(!request->is_valid());
}

template <typename ParserFactory>
static void test_unreal_digits_request(ParserFactory&& f) {
    string raws[] = {
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 100500999999999999099999999\r\n"
        "\r\n"
        "1234567890"
        ,

    };
    for (auto raw : raws) {
        auto parser = f();
        CHECK_FALSE(parser.parse_first(raw).state);
    }
}

template <typename ParserFactory>
static void test_unreal_digits_response(ParserFactory&& f) {
    string raws[] = {
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 100500999999999999099999999\r\n"
        "\r\n"
        "1234567890"
        ,
        "HTTP/1.1 11111 OK\r\n"
        "Content-Length: 10\r\n"
        "\r\n"
        "1234567890"
    };
    for (auto raw : raws) {
        auto parser = f();
        CHECK_FALSE(parser.parse_first(raw).state);
    }
}

TEST_CASE("unreal content lentgh request", "[parser]") {
    test_unreal_digits_request([]() {
        return http::RequestParser();
    });
}

TEST_CASE("unreal content lentgh response", "[parser]") {
    test_unreal_digits_response([]() {
        http::ResponseParser response_parser;
        http::RequestSP request = new http::Request(http::Request::Method::GET, new uri::URI("http://dev/"), http::Header(), new http::Body, "1.1");
        response_parser.append_request(request);
        return response_parser;
    });
}

TEST_CASE("bad chunk size", "[bad]") {
    http::RequestParser request_parser;
    string raw = GENERATE(
        string(
            "POST /upload HTTP/1.1\r\n"
            "Transfer-Encoding: chunked\r\n"
            "\r\n"
            "12345678901234567890\r\n"
            "1234\r\n"
            "0\r\n"
            "\r\n")
        ,
        string(
            "POST /upload HTTP/1.1\r\n"
            "Transfer-Encoding: chunked\r\n"
            "\r\n"
            "82222222222222222\r\n"
            "12345678901234567890\r\n"
            "1234\r\n"
            "0\r\n"
            "\r\n"
        )
    );
    auto res = request_parser.parse_first(raw);
    REQUIRE(!res.state);
    http::RequestSP request = res.request;

    REQUIRE(!request->is_valid());
    REQUIRE(request->method == Method::POST);
}
