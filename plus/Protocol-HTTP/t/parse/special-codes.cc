#include "../lib/test.h"

#define TEST(name) TEST_CASE("parse-special-codes: " name, "[parse-special-codes]")

TEST("100 continue") {
    ResponseParser p;
    p.set_context_request(new Request(Method::GET, new URI("/"), Header().add("Expect", "100-continue")));

    auto res = p.parse("HTTP/1.1 100 Continue\r\n\r\n").response;
    CHECK(res->state() == State::done);
    CHECK(res->code == 100);
    CHECK(p.context_request());

    auto res2 = p.parse("HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n").response;
    CHECK(res2 != res);
    res = res2;
    CHECK(res->state() == State::done);
    CHECK(res->code == 200);
    CHECK_FALSE(p.context_request());
}

TEST("unexpected 100 continue") {
    ResponseParser p;
    p.set_context_request(new Request());

    auto res = p.parse("HTTP/1.1 100 Continue\r\n\r\n").response;
    CHECK(res->state() == State::error);
    CHECK(res->error() == errc::unexpected_continue);
}

TEST("204 no content") {
    ResponseParser p;
    p.set_context_request(new Request());

    auto res = p.parse("HTTP/1.1 204 No Content\r\nConnection: keep-alive\r\n\r\n").response;
    CHECK(res->state() == State::done);
    CHECK(res->code == 204);
}
