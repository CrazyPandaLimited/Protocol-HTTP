#include "lib/test.h"

#define TEST(name) TEST_CASE("cookie-jar: " name, "[cookie_jar]")

auto now     = panda::date::Date::now();
auto past    = now - 3600;
auto ancient = now - 3600 * 5;
auto future  = now + 3600;

TEST("add cookie") {
    CookieJar jar("");
    auto& dc = jar.domain_cookies;
    URISP origin(new URI("https://www.perl.org/my-path"));


    Response::Cookie coo("v");
    coo.domain("crazypanda.ru");
    coo.path("/p");

    SECTION("no domain -> ignored") {
        coo.domain("");
        coo.path("/p");
        jar.add("k", coo, origin);
        CHECK(dc.size() == 0);
    }

    SECTION("session cookie is added") {
        jar.add("k", coo, origin);
        CHECK(dc.size() == 1);
        CHECK(dc.count(".crazypanda.ru") == 1);
        CHECK(dc[".crazypanda.ru"][0].name() == "k");
        CHECK(dc[".crazypanda.ru"][0].to_string("k") == coo.to_string("k"));
    }

    SECTION("non-expired cookie is added") {
        coo.expires(future);
        jar.add("k", coo, origin, now);
        CHECK(dc.size() == 1);
    }

    SECTION("expired cookie isn't added") {
        coo.expires(past);
        jar.add("k", coo, origin, now);
        CHECK(dc.size() == 0);
    }

    SECTION("2 cookies on same domain with differen paths are added") {
        jar.add("k", coo, origin);
        coo.path("/p2");
        jar.add("k", coo, origin);
        CHECK(dc.size() == 1);
        auto& cookies = dc[".crazypanda.ru"];
        CHECK(cookies.size() == 2);
    }

    SECTION("2 cookies on different domains are addred") {
        jar.add("k", coo, origin);
        coo.domain("example.org");
        jar.add("k", coo, origin);
        CHECK(dc.size() == 2);
    }

    SECTION("updated") {
        jar.add("k", coo, origin);
        coo.value("v2");
        jar.add("k", coo, origin);
        auto& cookies = dc[".crazypanda.ru"];
        CHECK(cookies.size() == 1);
        CHECK(cookies[0].value() == "v2");
    }

    SECTION("remove cookie") {
        jar.add("k", coo, origin);
        coo.expires(past);
        jar.add("k", coo, origin, now);
        CHECK(dc.size() == 0);
    }

    SECTION("remove cookie") {
        coo.path("");
        jar.add("k", coo, origin);
        jar.add("k", coo, origin, past);
        REQUIRE(dc.size() == 1);
        auto& cookies = dc[".crazypanda.ru"];
        CHECK(cookies.at(0).path() == "/my-path");
    }
}

TEST("domain submatch") {
    CHECK(CookieJar::sub_match(".perl.org", ".perl.org"));
    CHECK(CookieJar::sub_match(".perl.org", ".news.perl.org"));
    CHECK(!CookieJar::sub_match(".perl.org", ".php.net"));
    CHECK(!CookieJar::sub_match(".perl.org", ".pppperl.org"));
    CHECK(!CookieJar::sub_match(".perl.org", ".perl.org.fake.com"));
}

TEST("find/match cookie") {
    CookieJar jar("");

    URISP origin(new URI("https://perl.perl.org/"));

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

    jar.add("k1", coo1, origin, ancient);
    jar.add("k2", coo2, origin, ancient);
    jar.add("k3", coo3, origin, ancient);

    SECTION("prepreq"){
        auto& dc = jar.domain_cookies;
        auto cookies = &dc.at(".crazypanda.ru");
        REQUIRE(cookies->size() == 2);
        REQUIRE(cookies->at(0).name() == "k1");
        REQUIRE(cookies->at(1).name() == "k2");

        cookies = &dc.at(".perl.crazypanda.ru");
        REQUIRE(cookies->size() == 1);
        REQUIRE(cookies->at(0).name() == "k3");
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
        auto& c = cookies[0];
        CHECK(c.name() == "k2");
        CHECK(c.value() == "v2");
    }

    SECTION("2 of 3 match (by path)") {
        auto cookies = jar.find(URISP{new URI("http://crazypanda.ru/p1")}, past);
        REQUIRE(cookies.size() == 2);
        CHECK(cookies[0].name() == "k2");
        CHECK(cookies[1].name() == "k1");
    }

    SECTION("2 of 3 match (by domain)") {
        auto cookies = jar.find(URISP{new URI("https://crazypanda.ru/p")}, past);
        REQUIRE(cookies.size() == 2);
        CHECK(cookies[0].name() == "k2");
        CHECK(cookies[1].name() == "k1");
    }

    SECTION("3 of 3 match (by domain)") {
        auto cookies = jar.find(URISP{new URI("https://perl.crazypanda.ru/")}, past);
        REQUIRE(cookies.size() == 3);
        CHECK(cookies[0].name() == "k2");
        CHECK(cookies[1].name() == "k3");
        CHECK(cookies[2].name() == "k1");
    }

    SECTION("2 of 3 match (by domain, and security)") {
        auto cookies = jar.find(URISP{new URI("http://perl.crazypanda.ru/")}, past);
        REQUIRE(cookies.size() == 2);
        CHECK(cookies[0].name() == "k2");
        CHECK(cookies[1].name() == "k1");
    }

    SECTION("3 of 3 match (by subdomain)") {
        auto cookies = jar.find(URISP{new URI("https://cpp.and.perl.crazypanda.ru/")}, past);
        REQUIRE(cookies.size() == 3);
        CHECK(cookies[0].name() == "k2");
        CHECK(cookies[1].name() == "k3");
        CHECK(cookies[2].name() == "k1");
    }

    SECTION("3 of 3 match by subdomain, but mismatch my date") {
        auto cookies = jar.find(URISP{new URI("https://cpp.and.perl.crazypanda.ru/")}, future);
        REQUIRE(cookies.size() == 0);
    }

    SECTION("3 of 3 match by subdomain, 2 match my date") {
        auto cookies = jar.find(URISP{new URI("https://perl.crazypanda.ru/")}, now);
        REQUIRE(cookies.size() == 2);
        CHECK(cookies[0].name() == "k2");
        CHECK(cookies[1].name() == "k1");
    }

    SECTION("same-site policy") {
        CookieJar jar("");
        REQUIRE(jar.domain_cookies.size() == 0);

        URISP origin(new URI("https://auth.crazypanda.ru/"));

        Response::Cookie coo1("v1");
        coo1.domain("crazypanda.ru");
        coo1.path("/p1");
        coo1.expires(future);

        Response::Cookie coo4("v4");
        coo4.domain("crazypanda.ru");
        coo4.path("/cpp");
        coo4.expires(future);
        coo4.same_site(Response::Cookie::SameSite::Strict);

        Response::Cookie coo5("v5");
        coo5.domain("crazypanda.ru");
        coo5.path("/cpp");
        coo5.expires(future);
        coo5.same_site(Response::Cookie::SameSite::Lax);

        jar.add("k1", coo1, origin, ancient);
        jar.add("k4", coo4, origin, ancient);
        jar.add("k5", coo5, origin, ancient);

        auto& dc = jar.domain_cookies;
        REQUIRE(dc.at(".crazypanda.ru").size() == 3);

        SECTION("request matches origin") {
            auto cookies = jar.find(origin, now);
            REQUIRE(cookies.size() == 3);
        }

        SECTION("different site") {
            auto cookies = jar.find(URISP{new URI("https://public.crazypanda.ru/")}, past);
            REQUIRE(cookies.size() == 1);
            CHECK(cookies[0].name() == "k1");
        }

        SECTION("different site, lax context") {
            auto cookies = jar.find(URISP{new URI("https://public.crazypanda.ru/")}, past, true);
            REQUIRE(cookies.size() == 2);
            CHECK(cookies[0].name() == "k5");
            CHECK(cookies[1].name() == "k1");
        }
    }

    // check session cookies
}
