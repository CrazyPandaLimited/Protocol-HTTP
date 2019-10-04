#include "lib/test.h"

TEST_CASE("trivial get request", "[request]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Host") == "host1");
}

TEST_CASE("trivial post request", "[request]") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 23\r\n"
        "\r\n"
        "Wikipedia in\r\n\r\nchunks."
        ;

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::POST);
    REQUIRE(req->http_version == "1.1");
    REQUIRE(req->headers.fields.size() == 1);
    REQUIRE(req->headers.get_field("Content-Length") == "23");
    REQUIRE(req->body.as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}

TEST_CASE("trivial chunked post request", "[request]") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Transfer-Encoding: chunked\r\n"
        "\r\n"
        "4\r\n"
        "Wiki\r\n"
        "5\r\n"
        "pedia\r\n"
        "E\r\n"
        " in\r\n"
        "\r\n"
        "chunks.\r\n"
        "0\r\n"
        "\r\n"
        ;

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::POST);
    REQUIRE(req->http_version == "1.1");
    REQUIRE(req->headers.fields.size() == 1);
    REQUIRE(req->headers.get_field("Transfer-Encoding") == "chunked");
    REQUIRE(req->body.parts.size() == 3);
    REQUIRE(req->body.as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}

TEST_CASE("chunked post request with extension", "[request]") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Transfer-Encoding: chunked\r\n"
        "\r\n"
        "4;chunkextension=somevalue\r\n"
        "Wiki\r\n"
        "5\r\n"
        "pedia\r\n"
        "E\r\n"
        " in\r\n"
        "\r\n"
        "chunks.\r\n"
        "0\r\n"
        "\r\n"
        ;

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::POST);
    REQUIRE(req->http_version == "1.1");
    REQUIRE(req->headers.fields.size() == 1);
    REQUIRE(req->headers.get_field("Transfer-Encoding") == "chunked");
    REQUIRE(req->body.parts.size() == 3);
    REQUIRE(req->body.as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}

TEST_CASE("chunked post request with trailer header", "[request]") {
    RequestParser p;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Transfer-Encoding: chunked\r\n"
        "Trailer: Expires\r\n"
        "\r\n"
        "4;chunkextension=somevalue\r\n"
        "Wiki\r\n"
        "5\r\n"
        "pedia\r\n"
        "E\r\n"
        " in\r\n"
        "\r\n"
        "chunks.\r\n"
        "0\r\n"
        "Expires: Wed, 21 Oct 2015 07:28:00 GMT\r\n"
        "\r\n"
        ;

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::POST);
    REQUIRE(req->http_version == "1.1");
    REQUIRE(req->headers.fields.size() == 2);
    REQUIRE(req->headers.get_field("Transfer-Encoding") == "chunked");
    REQUIRE(req->body.parts.size() == 3);
    REQUIRE(req->body.as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}

TEST_CASE("trimming spaces from header value", "[request]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: host \r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.fields.size() == 1);
    REQUIRE(req->headers.get_field("Host") == "host");
}

TEST_CASE("no space after header field", "[request]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host:host\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Host") == "host");
    REQUIRE(req->headers.fields.size() == 1);
}

TEST_CASE("no header at all", "[request]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.fields.size() == 0);
}

TEST_CASE("space in header value", "[request]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: ho  st\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Host") == "ho  st");
    REQUIRE(req->headers.fields.size() == 1);
}

TEST_CASE("colon 1", "[request]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host:: host\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Host") == ": host");
    REQUIRE(req->headers.fields.size() == 1);
}

TEST_CASE("colon 2", "[request]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: h:ost\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Host") == "h:ost");
    REQUIRE(req->headers.fields.size() == 1);
}

TEST_CASE("multiple spaces", "[request]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: hh oo ss tt\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Host") == "hh oo ss tt");
    REQUIRE(req->headers.fields.size() == 1);
}

TEST_CASE("duplicated header field", "[request]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "Host: host2\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Host") == "host2");
    REQUIRE(req->headers.fields.size() == 2);
}

TEST_CASE("case insensitive content-length", "[request]") {
    RequestParser p;
    string raw =
        "GET / HTTP/1.0\r\n"
        "content-length: 1\r\n"
        "\r\n"
        "1";

    auto result = p.parse(raw);
    CHECK(result.state == RequestParser::State::done);

    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.fields.size() == 1);
    REQUIRE(req->body.as_buffer() == "1");
}

TEST_CASE("max_{message,body}_size", "[request]") {
    RequestParser p;
    auto conf = GENERATE(&RequestParser::max_body_size, &RequestParser::max_message_size);
    p.*conf = 2;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 10\r\n"
        "\r\n"
        "1234567890"
        ;
    CHECK_FALSE(p.parse(raw).state);
}

TEST_CASE("max_body_size prohibited", "[request]") {
    RequestParser p;
    p.max_body_size = RequestParser::SIZE_PROHIBITED;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 1\r\n"
        "\r\n"
        "1"
        ;
    CHECK_FALSE(p.parse(raw).state);
}

TEST_CASE("max_body_size chunked", "[request]") {
    RequestParser p;
    p.max_body_size = 3;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Transfer-Encoding: chunked\r\n"
        "\r\n"
        "4\r\n"
        "Wiki\r\n"
        "5\r\n"
        "pedia\r\n"
        "E\r\n"
        " in\r\n"
        "\r\n"
        "chunks.\r\n"
        "0\r\n"
        "\r\n"
        ;

    REQUIRE_FALSE(p.parse(raw).state);
}

TEST_CASE("parsing pipelined requests", "[request]") {
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
    CHECK(result.state == RequestParser::State::done);
    s.offset(result.position);
    auto req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->uri->to_string() == "/r1");
    REQUIRE(req->headers.get_field("Header1") == "header1");
    REQUIRE(req->headers.get_field("Header2") == "header2");
    REQUIRE(req->headers.get_field("Header3") == "header3");

    result = p.parse(s);
    CHECK(result.state == RequestParser::State::done);
    s.offset(result.position);
    req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->uri->to_string() == "/r2");
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Header4") == "header4");
    REQUIRE(req->headers.get_field("Header5") == "header5");
    REQUIRE(req->headers.get_field("Header6") == "header6");

    result = p.parse_shift(s);
    CHECK(result.state == RequestParser::State::done);
    req = result.request;
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->uri->to_string() == "/r3");
    REQUIRE(req->headers.get_field("Header7") == "header7");
    REQUIRE(req->headers.get_field("Header8") == "header8");
    REQUIRE(req->headers.get_field("Header9") == "header9");

    REQUIRE(s.empty());
}

TEST_CASE("request without length", "[response]") {
    RequestParser p;
    string body = GENERATE(string(""), string("1"));
    string raw =
        "GET / HTTP/1.1\r\n"
        "Host: host1\r\n"
        "\r\n" + body;

    auto fres = p.parse(raw);
    CHECK(fres.state == RequestParser::State::done);
}

