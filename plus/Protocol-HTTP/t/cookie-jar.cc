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

    SECTION("no domain -> get it from origin") {
        coo.domain("");
        coo.path("/p");
        jar.add("k", coo, origin);
        CHECK(dc.size() == 1);
        CHECK(dc[".www.perl.org"][0].host_only() == true);
    }

    SECTION("session cookie is added") {
        jar.add("k", coo, origin);
        CHECK(dc.size() == 1);
        CHECK(dc.count(".crazypanda.ru") == 1);
        CHECK(dc[".crazypanda.ru"][0].name() == "k");
        Response::Cookie &coo = dc[".crazypanda.ru"][0]; /* downcast */
        CHECK(coo.to_string("k") == coo.to_string("k"));
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

    SECTION("session cookies") {
        CookieJar jar("");
        Response::Cookie coo1("v1");
        coo1.domain("crazypanda.ru");
        coo1.path("/p1");
        jar.add("k1", coo1, origin);
        auto cookies = jar.find(URISP{new URI("https://games.crazypanda.ru/")});
        REQUIRE(cookies.size() == 1);
    }

    SECTION("host-only cookies (missing domain)") {
        CookieJar jar("");
        auto origin = URISP{new URI("https://ya.ru/")};
        Response::Cookie coo1("v1");
        jar.add("k1", coo1, origin);
        auto cookies = jar.find(origin);
        REQUIRE(cookies.size() == 1);

        cookies = jar.find(URISP{new URI("https://www.ya.ru/")});
        REQUIRE(cookies.size() == 0);
    }
}

TEST("cookies collection from the request") {
    CookieJar jar("");

    auto req = Request::Builder().uri("http://games.crazypanda.ru/hello/world").build();
    auto res = Response::Builder()
            .cookie("c1", Response::Cookie("v1"))
            .cookie("c2", Response::Cookie("v2").domain("crazypanda.ru").path("/hi"))
            .cookie("c3", Response::Cookie("v3").domain("google.com"))
            .build();


    SECTION("same origin -> 2 cookies") {
        jar.collect(*res, *req);
        auto cookies = jar.find(URISP{new URI("http://games.crazypanda.ru")});
        REQUIRE(cookies.size() == 2);
        CHECK(cookies[0].name() == "c1");
        CHECK(cookies[1].name() == "c2");
    }

    SECTION("differnt subdomain -> 1 cookie") {
        jar.collect(*res, *req);
        auto cookies = jar.find(URISP{new URI("http://ww.games.crazypanda.ru")});
        REQUIRE(cookies.size() == 1);
        CHECK(cookies[0].name() == "c2");
    }

    SECTION("ignore predicate") {
        jar.set_ignore([](auto&){ return true; });
        jar.collect(*res, *req);
        auto cookies = jar.find(URISP{new URI("http://games.crazypanda.ru")});
        REQUIRE(cookies.size() == 0);
    }

}

TEST("cookies population to thr response") {
    CookieJar jar("");
    URISP uri(new URI("https://crazypanda.ru/"));
    Response::Cookie coo1("v1");
    jar.add("k1", coo1, uri);

    auto req = Request::Builder().uri(uri).build();
    REQUIRE(req->cookies.size() == 0);
    jar.populate(*req);
    REQUIRE(req->cookies.size() == 1);
    CHECK(req->cookies.get("k1") == "v1");
}


TEST("(de)serialization") {
    CookieJar jar("");
    URISP origin(new URI("https://www.tut.by"));

    SECTION("single cookie serialization") {
        auto& dc = jar.domain_cookies;
        Response::Cookie coo("v");
        coo.domain("tut.by");
        coo.path("/news");
        jar.add("k", coo, origin);

        REQUIRE(dc.size() == 1);
        REQUIRE(dc.count(".tut.by") == 1);
        CHECK(dc[".tut.by"][0].name() == "k");

        auto &jcoo = dc[".tut.by"][0];
        REQUIRE(jcoo.to_string() == "Set-Cookie-Jar: k=v; Domain=tut.by; Path=/news");

        CHECK(jar.to_string(true) == "Set-Cookie-Jar: k=v; Domain=tut.by; Path=/news\r\n");
        CHECK(jar.to_string(false) == "");
    }

    SECTION("by date filtration") {
        panda::date::Date expires(2020, 05, 18, 5);
        auto past = expires - 3600;
        auto future = expires + 3600;

        Response::Cookie coo("v");
        coo.domain("tut.by");
        coo.path("/news");
        coo.expires(expires);
        jar.add("k", coo, origin, past);

        CHECK(jar.to_string(false, past) == "Set-Cookie-Jar: k=v; Domain=tut.by; Path=/news; Expires=Mon, 18 May 2020 02:00:00 GMT\r\n");
        CHECK(jar.to_string(false, future) == "");

    }

    SECTION("samesite & origin") {
        Response::Cookie coo("v");
        coo.domain("tut.by");
        coo.same_site(Response::Cookie::SameSite::Strict);
        jar.add("k", coo, origin);
        CHECK(jar.to_string(true) == "Set-Cookie-Jar: origin=https://www.tut.by ; k=v; Domain=tut.by; SameSite\r\n");
    }

    SECTION("samesite & origin") {
        Response::Cookie coo("v");
        jar.add("k", coo, origin);
        CHECK(jar.to_string(true) == "Set-Cookie-Jar: HostOnly; k=v; Domain=www.tut.by\r\n");
    }

}
