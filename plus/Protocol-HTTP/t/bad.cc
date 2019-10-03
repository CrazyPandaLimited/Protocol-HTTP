#include "lib/test.h"

TEST_CASE("double first line", "[bad]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";

    auto result = p.parse(raw);
    REQUIRE_FALSE(result.state);

    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
}

TEST_CASE("bad first line", "[bad]") {
    RequestParser p;
    string raw =
        "\r\n"
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";
    REQUIRE_FALSE(p.parse(raw).state);
}

TEST_CASE("space before colon in header field", "[bad]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host : host1\r\n"
        "\r\n";
    REQUIRE_FALSE(p.parse(raw).state);
}

TEST_CASE("space before header field", "[bad]") {
    RequestParser p;
    string raw =
        "\r\n"
        "GET / HTTP/1.0\r\n"
        " Host: host1\r\n"
        "\r\n";
    REQUIRE_FALSE(p.parse(raw).state);
}

template <typename ParserFactory>
static void test_unreal_digits_request (ParserFactory&& f) {
    string raws[] = {
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 100500999999999999099999999\r\n"
        "\r\n"
        "1234567890"
        ,

    };
    for (auto raw : raws) {
        auto parser = f();
        CHECK_FALSE(parser.parse(raw).state);
    }
}

template <typename ParserFactory>
static void test_unreal_digits_response (ParserFactory&& f) {
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
        CHECK_FALSE(parser.parse(raw).state);
    }
}

TEST_CASE ("unreal content length request", "[bad]") {
    test_unreal_digits_request([]() {
        return RequestParser();
    });
}

TEST_CASE("unreal content lentgh response", "[bad]") {
    test_unreal_digits_response([]() {
        ResponseParser p;
        RequestSP req = new Request(Method::GET, new URI("http://dev/"), Header(), Body(), "1.1");
        p.append_request(req);
        return p;
    });
}

TEST_CASE("bad chunk size", "[bad]") {
    RequestParser p;
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
    auto result = p.parse(raw);
    REQUIRE(!result.state);

    auto req = result.request;
    REQUIRE(req->method == Method::POST);
}
