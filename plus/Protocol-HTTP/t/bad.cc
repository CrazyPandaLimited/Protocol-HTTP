#include "lib/test.h"

TEST_CASE("double first line", "[bad]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";

    auto result = p.parse(raw);
    REQUIRE(result.error);

    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == HttpVersion::v1_0);
}

TEST_CASE("bad first line", "[bad]") {
    RequestParser p;
    string raw =
        "\r\n"
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";
    REQUIRE(p.parse(raw).error);
}

TEST_CASE("space before colon in header field", "[bad]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host : host1\r\n"
        "\r\n";
    REQUIRE(p.parse(raw).error);
}

TEST_CASE("space before header field", "[bad]") {
    RequestParser p;
    string raw =
        "\r\n"
        "GET / HTTP/1.0\r\n"
        " Host: host1\r\n"
        "\r\n";
    REQUIRE(p.parse(raw).error);
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
        CHECK(parser.parse(raw).error);
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
        CHECK(parser.parse(raw).error);
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
        p.set_request(new Request(Method::GET, new URI("http://dev/"), Header(), Body()));
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
    REQUIRE(result.error);

    auto req = result.request;
    REQUIRE(req->method == Method::POST);
}

TEST_CASE("bug test: additional final chunk before other chunks", "[bad]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.1\r\n"
        "Transfer-Encoding: chunked\r\n"
        "Connection: keep-alive\r\n"
        "\r\n"
        "0\r\n"
        "\r\n"
        "2\r\n"
        "12\r\n"
        "2\r\n"
        "34\r\n"
        "2\r\n"
        "56\r\n"
        "0\r\n"
        "\r\n"
    ;
    auto result = p.parse(raw);
    auto req = result.request;
    CHECK(result.state == State::done);
    CHECK_FALSE(result.error);
    CHECK(result.position == 75); //stoped at first final chunk
    CHECK(req->body.to_string() == "");
}
