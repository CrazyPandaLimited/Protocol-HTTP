#include "../lib/test.h"

#define TEST(name) TEST_CASE("parse-response: " name, "[parse-response]")

TEST("trivial get response") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::GET;
    p.set_request(req);
    string raw =
        "HTTP/1.0 200 OK\r\n"
        "Host: host1\r\n"
        "\r\n";

    auto result = p.parse(raw);
    CHECK(result.state != State::done);
    CHECK(result.position == raw.length());

    auto res = result.response;
    CHECK(res->http_version == 10);
    CHECK(res->code == 200);
    CHECK(res->message == "OK");
    CHECK(res->headers.get("Host") == "host1");

    result = p.eof();
    CHECK(result.state == State::done);
}

TEST("trivial head response") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::HEAD;
    p.set_request(req);
    string raw =
        "HTTP/1.0 200 OK\r\n"
        "Host: host1\r\n"
        "Content-Length: 100500\r\n" // parser won't expect real body here for HEAD response
        "\r\n";

    auto result = p.parse_shift(raw);
    CHECK(result.state == State::done);

    auto res = result.response;
    CHECK(res->http_version == 10);
    CHECK(res->code == 200);
    CHECK(res->message == "OK");
    CHECK(res->headers.get("Host") == "host1");
    CHECK(raw.empty());
}

TEST("redirect response") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::HEAD;
    p.set_request(req);
    string raw =
        "HTTP/1.1 301 Moved Permanently\r\n"
        "Date: Thu, 22 Mar 2018 16:25:43 GMT\r\n"
        "Location: http://localhost:35615\r\n"
        "Content-Length: 163\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<html><head><title>Moved</title></head><body><h1>Moved</h1><p>This page has moved to <a href=\"http://localhost:35615\">http://localhost:35615</a>.</p></body></html>\r\n";

    auto result = p.parse(raw);
    CHECK(result.state == State::done);

    auto res = result.response;
    REQUIRE(res->http_version == 11);
    CHECK(res->code == 301);
    CHECK(res->message == "Moved Permanently");
    CHECK(res->headers.get("Location") == "http://localhost:35615");
    CHECK(res->headers.get("Date") == "Thu, 22 Mar 2018 16:25:43 GMT");
}

TEST("trivial connection close") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::GET;
    p.set_request(req);
    string raw =
        "HTTP/1.1 200 OK\r\n"
        "Host: host1\r\n"
        "Connection: close\r\n"
        "\r\n"
        "body";

    auto result = p.parse(raw);
    CHECK(result.state != State::done);

    auto res = result.response;
    CHECK(res->http_version == 11);
    CHECK(res->headers.get("Host") == "host1");
    CHECK(res->body.to_string() == "body");

    result = p.eof();
    CHECK(result.state == State::done);
    CHECK(res->body.to_string() == "body");
}

TEST("connection close priority") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::GET;
    p.set_request(req);
    string additional = GENERATE(string("Content-Length: 4\r\n"), string("Transfer-Encoding: chunked\r\n"));
    string raw =
        "HTTP/1.1 200 OK\r\n"
        "Host: host1\r\n"
        + additional +
        "Connection: close\r\n"
        "\r\n"
        "1";

    auto result = p.parse(raw);
    CHECK_FALSE(result.error);
    result = p.eof();
    CHECK(result.error);
}

TEST("eof after full message") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::GET;
    p.set_request(req);
    string body = GENERATE(string(""), string("1"));
    string raw =
        "HTTP/1.1 200 OK\r\n"
        "Host: host1\r\n"
        "Connection: close\r\n"
        "Content-Length: " + to_string(body.length()) + "\r\n"
        "\r\n" + body;

    auto fres = p.parse(raw);
    CHECK(fres.state == State::done);

    fres = p.eof();
    CHECK(!fres.request);
    CHECK(!fres.response);
    CHECK(!fres.position);
    CHECK(fres.state == State::not_yet);
}

TEST("response with chunks") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::GET;
    p.set_request(req);
    string s =
        "HTTP/1.1 200 OK\r\n"
        "Transfer-Encoding: chunked\r\n"
        "Connection: keep-alive\r\n"
        "\r\n"
        "8\r\n"
        "epta raz\r\n"
        "8\r\n"
        "epta dva\r\n"
        "0\r\n\r\n";
    auto fres = p.parse(s);
    auto res  = fres.response;
    CHECK(fres.state == State::done);
    CHECK(res->body.length() == 16);
    CHECK(res->body.to_string() == "epta razepta dva");
    CHECK(res->chunked);
}

TEST("parsing response byte by byte") {
    ResponseParser p;
    p.set_request(new Request(Method::GET, new URI("http://dev/"), Header(), Body()));

    string s =
        "HTTP/1.1 101 Switching Protocols\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-WebSocket-Protocol: killme\r\n"
        "Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=\r\n"
        "Server: Panda-WebSocket\r\n"
        "Sec-WebSocket-Extensions: permessage-deflate; client_max_window_bits=15\r\n"
        "\r\n";

    const size_t CHUNK = GENERATE(1, 10);
    ResponseParser::Result result;
    while (s) {
        CHECK(result.state != State::done);
        result = p.parse(s.substr(0, CHUNK));
        s.offset(CHUNK < s.length() ? CHUNK : s.length());
    }
    CHECK(result.state == State::done);

    auto res = result.response;
    REQUIRE(res);
    REQUIRE(res->http_version == 11);
    CHECK(res->code == 101);
    CHECK(res->full_message() == "101 Switching Protocols");
    CHECK(res->headers.get("Upgrade") == "websocket");
    CHECK(res->headers.get("Connection") == "Upgrade");
    CHECK(res->headers.get("Sec-WebSocket-Extensions") == "permessage-deflate; client_max_window_bits=15");
}
