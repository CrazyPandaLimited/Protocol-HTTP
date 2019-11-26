#include "../lib/test.h"

#define TEST(name) TEST_CASE("compile-request: " name, "[compile-request]")

TEST("method") {
    auto req = Request::Builder().uri("/").build();
    string mstr;
    SECTION("OPTIONS") { mstr = "OPTIONS"; req->method = Method::OPTIONS; }
    SECTION("GET")     { mstr = "GET";     req->method = Method::GET; }
    SECTION("HEAD")    { mstr = "HEAD";    req->method = Method::HEAD; }
    SECTION("POST")    { mstr = "POST";    req->method = Method::POST; }
    SECTION("PUT")     { mstr = "PUT";     req->method = Method::PUT; }
    SECTION("DELETE")  { mstr = "DELETE";  req->method = Method::DELETE; }
    SECTION("TRACE")   { mstr = "TRACE";   req->method = Method::TRACE; }
    SECTION("CONNECT") { mstr = "CONNECT"; req->method = Method::CONNECT; }

    CHECK(req->to_string() == mstr + " / HTTP/1.1\r\n\r\n" );
}

TEST("default method is GET") {
    auto req = Request::Builder().uri("/").build();
    CHECK(req->to_string() == "GET / HTTP/1.1\r\n\r\n");
}

TEST("relative uri") {
    auto req = Request::Builder().uri("/hello").build();
    CHECK(req->to_string() == "GET /hello HTTP/1.1\r\n\r\n");
}

TEST("absolute uri") {
    auto req = Request::Builder().uri("https://epta.ru/hello").build();
    CHECK(req->to_string() ==
        "GET /hello HTTP/1.1\r\n"
        "Host: epta.ru\r\n"
        "\r\n"
    );
}

TEST("default uri is '/'") {
    auto req = Request::Builder().build();
    CHECK(req->to_string() == "GET / HTTP/1.1\r\n\r\n");
}

TEST("uri as URI object") {
    URISP uri = new URI();
    uri->path("/here");
    uri->param("is", "hello world");
    auto req = Request::Builder().uri(uri).build();
    CHECK(req->to_string() == "GET /here?is=hello%20world HTTP/1.1\r\n\r\n");
}

TEST("http version") {
    auto req = Request::Builder().build();
    string chk = "1.1";
    SECTION("default is 1.1") {}
    SECTION("1.1")            { req->http_version = 11; }
    SECTION("1.0")            { req->http_version = 10; chk = "1.0"; }
    CHECK(req->to_string() == string("GET / HTTP/") + chk + "\r\n\r\n");
}

TEST("example") {
    auto req = Request::Builder()
        .method(Method::POST)
        .uri("http://crazypanda.ru/hello/world")
        .http_version(10)
        .headers(Header().add("MyHeader", "my value"))
        .body("my body")
        .build();

    CHECK(req->to_string() ==
        "POST /hello/world HTTP/1.0\r\n"
        "MyHeader: my value\r\n"
        "Content-Length: 7\r\n"
        "Host: crazypanda.ru\r\n"
        "\r\n"
        "my body"
    );
}
