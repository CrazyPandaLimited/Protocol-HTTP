#include "../lib/test.h"

#define TEST(name) TEST_CASE("compile-response: " name, "[compile-response]")

TEST("code with default message for code") {
    auto res = Response::Builder().code(500).build();
    CHECK(res->to_string() ==
        "HTTP/1.1 500 Internal Server Error\r\n"
        "Content-Length: 0\r\n"
        "\r\n"
    );
}

TEST("custom message") {
    auto res = Response::Builder().code(500).message("a-nuka-nah").build();
    CHECK(res->to_string() ==
        "HTTP/1.1 500 a-nuka-nah\r\n"
        "Content-Length: 0\r\n"
        "\r\n"
    );
}

TEST("default code") {
    auto res = Response::Builder().build();
    CHECK(res->to_string() ==
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 0\r\n"
        "\r\n"
    );
}

TEST("http version") {
    auto res = Response::Builder().code(200).build();
    string chk = "1.1";
    SECTION("default is 1.1") {}
    SECTION("1.1")            { res->http_version = 11; }
    SECTION("1.0")            { res->http_version = 10; chk = "1.0"; }
    CHECK(res->to_string() ==
        string("HTTP/") + chk + " 200 OK\r\n"
        "Content-Length: 0\r\n"
        "\r\n"
    );
}

TEST("request context: follow connection type unless explicitly specified") {
    auto req = Request::Builder().build();
    auto res = Response::Builder().build();
    SECTION("request is c=close") {
        req->headers.connection("close");
        SECTION("keep") {
            CHECK(res->to_string(req) ==
                "HTTP/1.1 200 OK\r\n"
                "Content-Length: 0\r\n"
                "Connection: close\r\n"
                "\r\n"
            );
        }
        SECTION("change - ignored") {
            res->headers.connection("keep-alive");
            // can't join with first variant because of how set headers works inside - the order of headers has changed in this case
            // in our example, user has set "Connection" header earlier than auto-added "Content-Length" so it appears earlier in this case despite of
            // it's value being auto-changed to another
            CHECK(res->to_string(req) ==
                "HTTP/1.1 200 OK\r\n"
                "Connection: close\r\n"
                "Content-Length: 0\r\n"
                "\r\n"
            );
        }
    }
    SECTION("request is keep-alive") {
        SECTION("keep") {
            CHECK(res->to_string(req) ==
                "HTTP/1.1 200 OK\r\n"
                "Content-Length: 0\r\n"
                "Connection: keep-alive\r\n"
                "\r\n"
            );
        }
        SECTION("change - ignored") {
            res->headers.connection("close");
            CHECK(res->to_string(req) ==
                "HTTP/1.1 200 OK\r\n"
                "Connection: close\r\n"
                "Content-Length: 0\r\n"
                "\r\n"
            );
        }
    }
}

TEST("request context: follow http_version unless explicitly specified") {
    auto req = Request::Builder().http_version(10).build();
    auto res = Response::Builder().build();

    string chk;
    SECTION("keep")   { chk = "1.0"; }
    SECTION("change") { chk = "1.1"; res->http_version = 11; }

    CHECK(res->to_string(req) ==
        string("HTTP/") + chk + " 200 OK\r\n"
        "Content-Length: 0\r\n"
        "Connection: close\r\n"
        "\r\n"
    );
}

TEST("example") {
    auto res = Response::Builder()
        .code(500)
        .message("epta")
        .headers(Header().add("a", "1").add("b", "2"))
        .body("hello")
        .build();

    CHECK(res->to_string() ==
        "HTTP/1.1 500 epta\r\n"
        "a: 1\r\n"
        "b: 2\r\n"
        "Content-Length: 5\r\n"
        "\r\n"
        "hello"
    );
}
