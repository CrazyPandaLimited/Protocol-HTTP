#include "../lib/test.h"

#define TEST(name) TEST_CASE("parse-message: " name, "[parse-message]")

TEST("trivial") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->headers.get("Host") == "host1");
}

TEST("trimming spaces from header value") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: host \r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->headers.fields.size() == 1);
    REQUIRE(req->headers.get("Host") == "host");
}

TEST("no space after header field") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host:host\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->headers.get("Host") == "host");
    REQUIRE(req->headers.fields.size() == 1);
}

TEST("no header at all") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->headers.fields.size() == 0);
}

TEST("space in header value") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: ho  st\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->headers.get("Host") == "ho  st");
    REQUIRE(req->headers.fields.size() == 1);
}

TEST("colon in header 1") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host:: host\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->headers.get("Host") == ": host");
    REQUIRE(req->headers.fields.size() == 1);
}

TEST("colon in header 2") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: h:ost\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->headers.get("Host") == "h:ost");
    REQUIRE(req->headers.fields.size() == 1);
}

TEST("space before colon in header field") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host : host1\r\n"
        "\r\n";
    REQUIRE(p.parse(raw).error);
}

TEST("space before header field") {
    RequestParser p;
    string raw =
        "\r\n"
        "GET / HTTP/1.0\r\n"
        " Host: host1\r\n"
        "\r\n";
    REQUIRE(p.parse(raw).error);
}

TEST("multiple spaces in header") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: hh oo ss tt\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->headers.get("Host") == "hh oo ss tt");
    REQUIRE(req->headers.fields.size() == 1);
}

TEST("duplicated header field") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "Host: host2\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->headers.get("Host") == "host2");
    REQUIRE(req->headers.fields.size() == 2);
}

TEST("fragmented header") {
    RequestParser p;

    string v[] = {
        "GET / HTTP/1.0\r\n"
        "Heade", "r1: header1\r\n"
        "Header2: h", "eader2\r\n"
        "Header3: header3\r\n"
        "\r\n"
    };

    RequestParser::Result result;
    for (auto s : v) {
        CHECK(result.state != State::done);
        result = p.parse(s);
    }
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->headers.get("Header1") == "header1");
    REQUIRE(req->headers.get("Header2") == "header2");
    REQUIRE(req->headers.get("Header3") == "header3");
}

TEST("message fragmented by lines") {
    RequestParser p;

    string v[] = {
        "GET / HTTP/1.0\r\n"
        "Header1: header1\r\n",
        "Header2: header2\r\n",
        "Header3: header3\r\n"
        "\r\n"
    };

    RequestParser::Result result;
    for (auto s : v) {
        CHECK(result.state != State::done);
        result = p.parse(s);
    }
    CHECK(result.state == State::done);

    auto req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->headers.get("Header1") == "header1");
    REQUIRE(req->headers.get("Header2") == "header2");
    REQUIRE(req->headers.get("Header3") == "header3");
}

TEST("max_headers_size") {
    RequestParser p;
    p.max_headers_size = 19;
    string raw =
        "GET / HTTP/1.1\r\n"
        "Content-Length: 0\r\n" // len = 19
        "\r\n";
    CHECK_FALSE(p.parse(raw).error);

    p.max_headers_size = 18;
    CHECK(p.parse(raw).error == errc::headers_too_large);
}

TEST("max_body_size with content-length") {
    RequestParser p;
    int sz;
    SECTION("ok")         { sz = 10; }
    SECTION("too large")  { sz = 9; }
    SECTION("disallowed") { sz = 0; }
    p.max_body_size = sz;

    string raw =
        "POST / HTTP/1.1\r\n"
        "Content-Length: 10\r\n"
        "\r\n";

    auto result = p.parse(raw);
    if (sz == 10) {
        CHECK(result.state == State::in_body);
        CHECK_FALSE(result.error);
    } else if (sz) {
        CHECK(result.error == errc::body_too_large);
    } else {
        CHECK(result.error == errc::unexpected_body);
    }
}

TEST("max_body_size without content-length") {
    ResponseParser p;
    p.set_request(new Request(Method::GET, new URI()));

    int sz;
    SECTION("ok")         { sz = 10; }
    SECTION("too large")  { sz = 9; }
    SECTION("disallowed") { sz = 0; }
    p.max_body_size = sz;

    string raw =
        "HTTP/1.0 200 OK\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == State::in_body);
    CHECK_FALSE(result.error);

    result = p.parse("1234567890");
    if (sz == 10) {
        CHECK(result.state == State::in_body);
        CHECK_FALSE(result.error);
        result = p.eof();
        CHECK(result.state == State::done);
        CHECK_FALSE(result.error);
    } else if (sz) {
        CHECK(result.error == errc::body_too_large);
    } else {
        CHECK(result.error == errc::unexpected_body);
    }
}

TEST("max_body_size chunked") {
    RequestParser p;

    int sz;
    SECTION("ok")         { sz = 10; }
    SECTION("too large")  { sz = 9; }
    SECTION("disallowed") { sz = 0; }
    p.max_body_size = sz;

    string raw =
        "POST / HTTP/1.1\r\n"
        "Transfer-Encoding: chunked\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == State::got_header);
    CHECK_FALSE(result.error);

    result = p.parse("a\r\n");
    if (sz == 10) {
        CHECK(result.state != State::done);
        CHECK_FALSE(result.error);
        result = p.parse("1234567890\r\n");
        CHECK(result.state != State::done);
        CHECK_FALSE(result.error);
        result = p.parse("0\r\n\r\n");
        CHECK(result.state == State::done);
        CHECK_FALSE(result.error);
    } else if (sz) {
        CHECK(result.error == errc::body_too_large);
    } else {
        CHECK(result.error == errc::unexpected_body);
    }
}

TEST("parsing pipelined messages") {
    RequestParser p;

    string s =
        "GET /r1 HTTP/1.0\r\n"
        "Header1: header1\r\n"
        "Header2: header2\r\n"
        "Header3: header3\r\n"
        "\r\n"
        "GET /r2 HTTP/1.0\r\n"
        "Header4: header4\r\n"
        "Header5: header5\r\n"
        "Header6: header6\r\n"
        "\r\n"
        "GET /r3 HTTP/1.0\r\n"
        "Header7: header7\r\n"
        "Header8: header8\r\n"
        "Header9: header9\r\n"
        "\r\n";

    auto result = p.parse(s);
    CHECK(result.state == State::done);
    s.offset(result.position);
    auto req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->uri->to_string() == "/r1");
    REQUIRE(req->headers.get("Header1") == "header1");
    REQUIRE(req->headers.get("Header2") == "header2");
    REQUIRE(req->headers.get("Header3") == "header3");

    result = p.parse(s);
    CHECK(result.state == State::done);
    s.offset(result.position);
    req = result.request;
    REQUIRE(req->uri->to_string() == "/r2");
    REQUIRE(req->http_version == 10);
    REQUIRE(req->headers.get("Header4") == "header4");
    REQUIRE(req->headers.get("Header5") == "header5");
    REQUIRE(req->headers.get("Header6") == "header6");

    result = p.parse_shift(s);
    CHECK(result.state == State::done);
    req = result.request;
    REQUIRE(req->http_version == 10);
    REQUIRE(req->uri->to_string() == "/r3");
    REQUIRE(req->headers.get("Header7") == "header7");
    REQUIRE(req->headers.get("Header8") == "header8");
    REQUIRE(req->headers.get("Header9") == "header9");

    REQUIRE(s.empty());
}

TEST("correct result position in messages with body") {
    RequestParser p;
    string s =
        "POST / HTTP/1.1\r\n"
        "Content-length: 8\r\n"
        "\r\n"
        "epta nah111";
    auto fres = p.parse(s);
    auto req  = fres.request;
    CHECK(fres.state == State::done);
    CHECK(fres.position == 46);
    CHECK(req->headers.get("Content-Length") == "8");
    CHECK(req->body.length() == 8);
}

TEST("keep_alive()") {
    RequestSP req = new Request();

    SECTION("1.0") {
        req->http_version = 10;
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
        req->http_version = 11;
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
