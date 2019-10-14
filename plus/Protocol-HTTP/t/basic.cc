#include "lib/test.h"

TEST_CASE("case insensitive headers", "[basic]") {
    Header h;
    h.add_field("Aa", "value");
    CHECK(h.get_field("AA") == "value");
}

TEST_CASE("keep-alive", "[basic]") {
    RequestSP req = new Request();

    SECTION("1.0") {
        req->http_version = HttpVersion::v1_0;
        SECTION("yes1") {
            req->headers.connection("Keep-Alive");
            CHECK(req->keep_alive());
        }
        SECTION("yes2") {
            req->keep_alive(true);
            CHECK(req->keep_alive());
        }
        SECTION("no 1") {
            CHECK(!req->keep_alive());
        }
        SECTION("no 2") {
            req->headers.connection("Epta");
            CHECK(!req->keep_alive());
        }
        SECTION("no 3") {
            req->headers.connection("close");
            CHECK(!req->keep_alive());
        }
        SECTION("no 4") {
            req->keep_alive(false);
            CHECK(!req->keep_alive());
        }
    }

    SECTION("1.1") {
        req->http_version = HttpVersion::v1_1;
        SECTION("yes 1") {
            CHECK(req->keep_alive());
        }
        SECTION("yes 2") {
            req->keep_alive(true);
            CHECK(req->keep_alive());
        }
        SECTION("yes 3") {
            req->headers.connection("Epta");
            CHECK(req->keep_alive());
        }
        SECTION("no 1") {
            req->headers.connection("close");
            CHECK(!req->keep_alive());
        }
        SECTION("no 2") {
            req->keep_alive(false);
            CHECK(!req->keep_alive());
        }
    }
}
