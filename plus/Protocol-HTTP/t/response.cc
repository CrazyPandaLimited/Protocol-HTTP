#include "lib/test.h"

TEST_CASE("trivial get response", "[response]") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::GET;
    p.append_request(req);
    string raw =
        "HTTP/1.0 200 OK\r\n"
        "Host: host1\r\n"
        "\r\n";

    auto res = p.parse(raw).response;
    REQUIRE(res->is_valid());
    REQUIRE(res->http_version == "1.0");
    REQUIRE(res->headers.get_field("Host") == "host1");
}

TEST_CASE("trivial head response", "[response]") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::HEAD;
    p.append_request(req);
    string raw =
        "HTTP/1.0 200 OK\r\n"
        "Host: host1\r\n"
        "Content-Length: 100500\r\n" // parser won't expect real body here for HEAD response
        "\r\n";

    auto res = p.parse(raw).response;
    REQUIRE(res->is_valid());
    REQUIRE(res->http_version == "1.0");
    REQUIRE(res->headers.get_field("Host") == "host1");
}

TEST_CASE("redirect response", "[response]") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::HEAD;
    p.append_request(req);
    string raw =
        "HTTP/1.1 301 Moved Permanently\r\n"
        "Date: Thu, 22 Mar 2018 16:25:43 GMT\r\n"
        "Location: http://localhost:35615\r\n"
        "Content-Length: 163\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<html><head><title>Moved</title></head><body><h1>Moved</h1><p>This page has moved to <a href=\"http://localhost:35615\">http://localhost:35615</a>.</p></body></html>\r\n";

    auto res = p.parse(raw).response;
    REQUIRE(res->is_valid());
    REQUIRE(res->http_version == "1.1");
    REQUIRE(res->headers.get_field("Location") == "http://localhost:35615");
    REQUIRE(res->headers.get_field("Date") == "Thu, 22 Mar 2018 16:25:43 GMT");
}

TEST_CASE("trivial connection close", "[response]") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::GET;
    p.append_request(req);
    string raw =
        "HTTP/1.1 200 OK\r\n"
        "Host: host1\r\n"
        "Connection: close\r\n"
        "\r\n"
        "body";

    auto fres = p.parse(raw);
    auto res = p.eof();
    CHECK(res.state == ResponseParser::State::done);
    CHECK(res.response->is_valid());
    CHECK(res.response->http_version == "1.1");
    CHECK(res.response->headers.get_field("Host") == "host1");
    CHECK(res.response->body.as_buffer() == "body");
}

TEST_CASE("connection close priority", "[response]") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::GET;
    p.append_request(req);
    string additional = GENERATE(string("Content-Length: 4\r\n"), string("Transfer-Encoding: chunked\r\n"));
    string raw =
        "HTTP/1.1 200 OK\r\n"
        "Host: host1\r\n"
        + additional +
        "Connection: close\r\n"
        "\r\n"
        "1";

    auto fres = p.parse(raw);
    CHECK(fres.state);
    auto res = p.eof();
    CHECK_FALSE(res.state);
}

TEST_CASE("response eof after full message", "[response]") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::GET;
    p.append_request(req);
    string body = GENERATE(string(""), string("1"));
    string raw =
        "HTTP/1.1 200 OK\r\n"
        "Host: host1\r\n"
        "Connection: close\r\n"
        "Content-Length: " + to_string(body.length()) + "\r\n"
        "\r\n" + body;

    auto fres = p.parse(raw);
    CHECK(fres.state == ResponseParser::State::done);
    auto res = p.eof();
    CHECK(!res.state);
}
