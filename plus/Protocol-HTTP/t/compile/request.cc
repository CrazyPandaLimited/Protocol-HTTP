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
        .headers(Headers().add("MyHeader", "my value"))
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


TEST("Accept-Encoding") {
    SECTION("*") {
        auto req = Request::Builder().allow_compression(compression::ANY).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: *\r\n"
        "\r\n");
        CHECK(req->compression_mask() == compression::ANY);
    }
    SECTION("gzip") {
        auto req = Request::Builder().allow_compression(compression::GZIP).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: gzip\r\n"
        "\r\n");
        CHECK(req->compression_mask() == compression::GZIP);
    }
    SECTION("compress") {
        auto req = Request::Builder().allow_compression(compression::COMPRESS).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: compress\r\n"
        "\r\n");
    }
    SECTION("deflate") {
        auto req = Request::Builder().allow_compression(compression::DEFLATE).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: deflate\r\n"
        "\r\n");
    }
    SECTION("br") {
        auto req = Request::Builder().allow_compression(compression::BROTLI).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: br\r\n"
        "\r\n");
    }
    SECTION("identity") {
        auto req = Request::Builder().allow_compression(compression::IDENTITY).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n\r\n");
    }
    SECTION("!br") {
        auto req = Request::Builder().allow_compression(~compression::BROTLI).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: br;q=0\r\n"
        "\r\n");
    }

    SECTION("deflate, gzip, identity") {
        auto req = Request::Builder()
                .allow_compression(compression::DEFLATE)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::IDENTITY)
            .build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: deflate, gzip, identity\r\n"
        "\r\n");
        CHECK((req->compression_mask() & compression::GZIP));
        CHECK((req->compression_mask() & compression::DEFLATE));
        CHECK((req->compression_mask() & compression::IDENTITY));
        CHECK(!(req->compression_mask() & compression::BROTLI));
    }

    SECTION("deflate, !gzip, identity") {
        auto req = Request::Builder()
                .allow_compression(compression::DEFLATE)
                .allow_compression(~compression::GZIP)
                .allow_compression(compression::IDENTITY)
            .build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: deflate, identity, gzip;q=0\r\n"
        "\r\n");
        CHECK((req->compression_mask() & compression::DEFLATE));
        CHECK((req->compression_mask() & compression::IDENTITY));
        CHECK((req->compression_mask(true) & compression::GZIP));
        CHECK(!(req->compression_mask(true) & compression::DEFLATE));
    }

    SECTION("deflate, !* (1)") {
        auto req = Request::Builder()
                .allow_compression(~compression::ANY)
                .allow_compression(compression::DEFLATE)
            .build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: deflate, *;q=0\r\n"
        "\r\n");
    }

    SECTION("deflate, !* (2)") {
        auto req = Request::Builder()
                .allow_compression(compression::DEFLATE)
                .allow_compression(~compression::ANY)
            .build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: deflate, *;q=0\r\n"
        "\r\n");
    }


    SECTION("deflate, gzip, gzip, gzip, gzip, gzip, gzip, gzip, gzip, identity") {
        auto req = Request::Builder()
                .allow_compression(compression::DEFLATE)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::IDENTITY)
            .build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: deflate, gzip, gzip, gzip, gzip, gzip, gzip, gzip\r\n"
        "\r\n");
    }

}
