#include "lib/test.h"

#define TEST(name) TEST_CASE("cookie-jar: " name, "[cookie_jar]")

auto now     = panda::date::Date::now();
auto past    = now - 3600;
auto ancient = now - 3600 * 5;
auto future  = now + 3600;

TEST("add cookie") {
    CookieJar jar("");
    auto& dc = jar.domain_cookies;

    Response::Cookie coo("v");
    coo.domain("crazypanda.ru");
    coo.path("/p");

    SECTION("no domain, no path -> ignored") {
        coo.domain("");
        coo.path("/p");
        jar.add("k", coo);
        CHECK(dc.size() == 0);

        coo.domain("example.org");
        coo.path("");
        jar.add("k", coo);
        CHECK(dc.size() == 0);
    }

    SECTION("session cookie is added") {
        jar.add("k", coo);
        CHECK(dc.size() == 1);
        CHECK(dc.count(".crazypanda.ru") == 1);
        CHECK(dc[".crazypanda.ru"].fields[0].name == "k");
        CHECK(dc[".crazypanda.ru"].fields[0].value.to_string("k") == coo.to_string("k"));
    }

    SECTION("non-expired cookie is added") {
        coo.expires(future);
        jar.add("k", coo, now);
        CHECK(dc.size() == 1);
    }

    SECTION("expired cookie isn't added") {
        coo.expires(past);
        jar.add("k", coo, now);
        CHECK(dc.size() == 0);
    }

    SECTION("2 cookies on same domain with differen paths are added") {
        jar.add("k", coo);
        coo.path("/p2");
        jar.add("k", coo);
        CHECK(dc.size() == 1);
        auto& cookies = dc[".crazypanda.ru"];
        CHECK(cookies.size() == 2);
    }

    SECTION("2 cookies on different domains are addred") {
        jar.add("k", coo);
        coo.domain("example.org");
        jar.add("k", coo);
        CHECK(dc.size() == 2);
    }

    SECTION("updated") {
        jar.add("k", coo);
        coo.value("v2");
        jar.add("k", coo);
        auto& cookies = dc[".crazypanda.ru"];
        CHECK(cookies.size() == 1);
        CHECK(cookies.fields[0].value.value() == "v2");
    }

    SECTION("remove cookie") {
        jar.add("k", coo);
        coo.expires(past);
        jar.add("k", coo, now);
        CHECK(dc.size() == 0);
    }
}

TEST("find/match cookie") {
    CookieJar jar("");

    Response::Cookie coo1("v1");
    coo1.domain("crazypanda.ru");
    coo1.path("/p1");
    coo1.expires(now);

    Response::Cookie coo2("v2");
    coo2.domain("crazypanda.ru");
    coo2.path("/p1/p2");
    coo2.expires(now);

    Response::Cookie coo3("v3");
    coo3.domain("perl.crazypanda.ru");
    coo3.path("/pp3");
    coo3.expires(past);
    coo3.secure(true);

    jar.add("k1", coo1, ancient);
    jar.add("k2", coo2, ancient);
    jar.add("k3", coo3, ancient);

    SECTION("prepreq"){
        auto& dc = jar.domain_cookies;
        auto cookies = &dc.at(".crazypanda.ru");
        REQUIRE(cookies->size() == 2);
        REQUIRE(cookies->fields[0].name == "k1");
        REQUIRE(cookies->fields[1].name == "k2");

        cookies = &dc.at(".perl.crazypanda.ru");
        REQUIRE(cookies->size() == 1);
        REQUIRE(cookies->fields[0].name == "k3");
    }

    SECTION("find nothing (path mismatch)") {
        auto cookies = jar.find(URISP{new URI("http://crazypanda.ru/404")}, past);
        REQUIRE(cookies.size() == 0);
    }

    SECTION("find nothing (domain mismatch)") {
        auto cookies = jar.find(URISP{new URI("http://example.org/")});
        REQUIRE(cookies.size() == 0);
    }

    SECTION("find most precise") {
        auto cookies = jar.find(URISP{new URI("http://crazypanda.ru/p1/p2")}, past);
        REQUIRE(cookies.size() == 1);
        auto& c = cookies.fields[0];
        CHECK(c.name == "k2");
        CHECK(c.value.value() == "v2");
    }

    SECTION("2 of 3 match (by path)") {
        auto cookies = jar.find(URISP{new URI("http://crazypanda.ru/p1")}, past);
        REQUIRE(cookies.size() == 2);
        CHECK(cookies.fields[0].name == "k2");
        CHECK(cookies.fields[1].name == "k1");
    }

    SECTION("2 of 3 match (by domain)") {
        auto cookies = jar.find(URISP{new URI("https://crazypanda.ru/p")}, past);
        REQUIRE(cookies.size() == 2);
        CHECK(cookies.fields[0].name == "k2");
        CHECK(cookies.fields[1].name == "k1");
    }

    SECTION("3 of 3 match (by domain)") {
        auto cookies = jar.find(URISP{new URI("https://perl.crazypanda.ru/")}, past);
        REQUIRE(cookies.size() == 3);
        CHECK(cookies.fields[0].name == "k2");
        CHECK(cookies.fields[1].name == "k3");
        CHECK(cookies.fields[2].name == "k1");
    }

    SECTION("2 of 3 match (by domain, and security)") {
        auto cookies = jar.find(URISP{new URI("http://perl.crazypanda.ru/")}, past);
        REQUIRE(cookies.size() == 2);
        CHECK(cookies.fields[0].name == "k2");
        CHECK(cookies.fields[1].name == "k1");
    }

    SECTION("3 of 3 match (by subdomain)") {
        auto cookies = jar.find(URISP{new URI("https://cpp.and.perl.crazypanda.ru/")}, past);
        REQUIRE(cookies.size() == 3);
        CHECK(cookies.fields[0].name == "k2");
        CHECK(cookies.fields[1].name == "k3");
        CHECK(cookies.fields[2].name == "k1");
    }

    SECTION("3 of 3 match by subdomain, but mismatch my date") {
        auto cookies = jar.find(URISP{new URI("https://cpp.and.perl.crazypanda.ru/")}, future);
        REQUIRE(cookies.size() == 0);
    }

    SECTION("3 of 3 match by subdomain, 2 match my date") {
        auto cookies = jar.find(URISP{new URI("https://perl.crazypanda.ru/")}, now);
        REQUIRE(cookies.size() == 2);
        CHECK(cookies.fields[0].name == "k2");
        CHECK(cookies.fields[1].name == "k1");
    }

    SECTION("3 of 3 match, 1 filtered by http-only") {
        jar.domain_cookies[".crazypanda.ru"].fields.front().value.http_only(true);
        auto cookies = jar.find(URISP{new URI("https://perl.crazypanda.ru/")}, past);
        REQUIRE(cookies.size() == 2);
        CHECK(cookies.fields[0].name == "k2");
        CHECK(cookies.fields[1].name == "k3");
    }


}