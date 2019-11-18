#include "../lib/test.h"

#define TEST(name) TEST_CASE("parse-special-codes: " name, "[parse-special-codes]")

TEST("100 continue") {
    ResponseParser p;
    p.set_request(new Request(Method::GET, new URI("/"), Header().add("Expect", "100-continue")));

    auto result = p.parse("HTTP/1.1 100 Continue\r\n\r\n");
    CHECK(result.state == State::done);
    CHECK(result.response->code == 100);
    CHECK(p.request());

    result = p.parse("HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n");
    CHECK(result.state == State::done);
    CHECK(result.response->code == 200);
    CHECK_FALSE(p.request());
}

TEST("unexpected 100 continue") {
    ResponseParser p;
    p.set_request(new Request());

    auto result = p.parse("HTTP/1.1 100 Continue\r\n\r\n");
    CHECK(result.state == State::error);
    CHECK(result.error == errc::unexpected_continue);
}

TEST("204 no content") {
    ResponseParser p;
    p.set_request(new Request());

    auto result = p.parse("HTTP/1.1 204 No Content\r\nConnection: keep-alive\r\n\r\n");
    CHECK(result.state == State::done);
    CHECK(result.response->code == 204);
}
