#include "lib/test.h"

#define TEST(name) TEST_CASE("chunks: " name, "[chunks]")

TEST("trivial chunks") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Transfer-Encoding: chunked\r\n"
        "\r\n"
        "4\r\n"
        "Wiki\r\n"
        "5\r\n"
        "pedia\r\n"
        "E\r\n"
        " in\r\n"
        "\r\n"
        "chunks.\r\n"
        "0\r\n"
        "\r\n"
        ;

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->headers.fields.size() == 1);
    REQUIRE(req->headers.get("Transfer-Encoding") == "chunked");
    REQUIRE(req->body.parts.size() == 3);
    REQUIRE(req->body.to_string() == "Wikipedia in\r\n\r\nchunks.");
    REQUIRE(req->chunked);
}

TEST("chunks with extension") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Transfer-Encoding: chunked\r\n"
        "\r\n"
        "4;chunkextension=somevalue\r\n"
        "Wiki\r\n"
        "5\r\n"
        "pedia\r\n"
        "E\r\n"
        " in\r\n"
        "\r\n"
        "chunks.\r\n"
        "0\r\n"
        "\r\n"
        ;

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->headers.fields.size() == 1);
    REQUIRE(req->headers.get("Transfer-Encoding") == "chunked");
    REQUIRE(req->body.parts.size() == 3);
    REQUIRE(req->body.to_string() == "Wikipedia in\r\n\r\nchunks.");
}

TEST("chunks with trailer header") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Transfer-Encoding: chunked\r\n"
        "Trailer: Expires\r\n"
        "\r\n"
        "4;chunkextension=somevalue\r\n"
        "Wiki\r\n"
        "5\r\n"
        "pedia\r\n"
        "E\r\n"
        " in\r\n"
        "\r\n"
        "chunks.\r\n"
        "0\r\n"
        "Expires: Wed, 21 Oct 2015 07:28:00 GMT\r\n"
        "\r\n"
        ;

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->headers.fields.size() == 2);
    REQUIRE(req->headers.get("Transfer-Encoding") == "chunked");
    REQUIRE(req->body.parts.size() == 3);
    REQUIRE(req->body.to_string() == "Wikipedia in\r\n\r\nchunks.");
}

TEST("fragmented chunks") {
    RequestParser p;

    std::vector<string> v = {
        "POST /upload HTTP/1.1\r\n"
        "Transfer-Enco", "ding", ": chu", "nked\r\n"
        "Trailer: Expires\r\n"
        "\r\n"
        "4;chunkex", "tension=somevalue\r\n"
        "Wiki\r\n"
        "5\r\n"
        "pedia\r\n"
        "E\r\n"
        " i", "n\r\n"
        "\r\n"
        "chunks.\r\n"
        "0\r\n"
        "Expires: Wed, 21 Oct 20", "15 07:28:00 GMT\r\n"
        "\r\n"
    };

    RequestParser::Result result;
    for (auto s : v) {
        CHECK(result.state != State::done);
        result =  p.parse(s);
    }
    CHECK(result.state == State::done);

    auto req = result.request;
    CHECK(req->method == Method::POST);
    CHECK(req->http_version == HttpVersion::v1_1);
    CHECK(req->headers.get("Transfer-Encoding") == "chunked");
    CHECK(req->headers.get("Trailer") == "Expires");
    CHECK(req->body.to_string() == "Wikipedia in\r\n\r\nchunks.");
}

TEST("bad chunk size") {
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
    CHECK(req->method == Method::POST);
}
