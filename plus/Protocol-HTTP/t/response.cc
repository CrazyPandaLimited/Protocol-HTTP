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
