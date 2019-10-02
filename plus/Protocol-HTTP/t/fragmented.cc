#include "lib/test.h"

TEST_CASE("parsing request with fragmented header", "[fragmented]") {
    RequestParser p;
    RequestSP req;

    std::vector<string> v = {
        "GET / HTTP/1.0\r\n"
        "Heade", "r1: header1\r\n"
        "Header2: h", "eader2\r\n"
        "Header3: header3\r\n"
        "\r\n"
    };

    for (auto s : v) {
        if (req) REQUIRE(!req->is_valid());
        req = p.parse(s).request;
    }

    REQUIRE(req->is_valid());
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Header1") == "header1");
    REQUIRE(req->headers.get_field("Header2") == "header2");
    REQUIRE(req->headers.get_field("Header3") == "header3");
}

TEST_CASE("parsing request with fragmented method", "[fragmented]") {
    RequestParser p;
    RequestSP req;

    std::vector<string> v = {
        "G", "ET / HTTP/1", ".0\r\n"
        "Header1: header1\r\n"
        "Header2: header2\r\n"
        "Header3: header3\r\n"
        "\r\n"
    };

    for (auto s : v) {
        if (req) REQUIRE(!req->is_valid());
        req = p.parse(s).request;
    }

    REQUIRE(req->is_valid());
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Header1") == "header1");
    REQUIRE(req->headers.get_field("Header2") == "header2");
    REQUIRE(req->headers.get_field("Header3") == "header3");
}

TEST_CASE("parsing request fragmented by lines", "[fragmented]") {
    RequestParser p;
    RequestSP req;

    std::vector<string> v = {
        "GET / HTTP/1.0\r\n"
        "Header1: header1\r\n",
        "Header2: header2\r\n",
        "Header3: header3\r\n"
        "\r\n"
    };

    for (auto s : v) {
        if (req) REQUIRE(!req->is_valid());
        req = p.parse(s).request;
    }

    REQUIRE(req->is_valid());
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Header1") == "header1");
    REQUIRE(req->headers.get_field("Header2") == "header2");
    REQUIRE(req->headers.get_field("Header3") == "header3");
}

TEST_CASE("parsing request byte by byte", "[fragmented]") {
    RequestParser p;
    RequestSP req;
    string s =
        "GET /uri HTTP/1.0\r\n"
        "Header1: header1\r\n"
        "Header2: header2\r\n"
        "Header3: header3\r\n"
        "\r\n";

    const size_t CHUNK = GENERATE(1, 10);
    while (s) {
        if (req) REQUIRE(!req->is_valid());
        req = p.parse(s.substr(0, CHUNK)).request;
        s.offset(CHUNK < s.length() ? CHUNK : s.length());
    }

    REQUIRE(req->is_valid());
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Header1") == "header1");
    REQUIRE(req->headers.get_field("Header2") == "header2");
    REQUIRE(req->headers.get_field("Header3") == "header3");
}

TEST_CASE("parsing response byte by byte", "[fragmented]") {
    ResponseParser p;
    RequestSP req = new Request(Method::GET, new URI("http://dev/"), Header(), Body(), "1.1");
    p.append_request(req);
    ResponseSP res;

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
    while (s) {
        if (res) REQUIRE(!res->is_valid());
        res = p.parse(s.substr(0, CHUNK)).response;
        s.offset(CHUNK < s.length() ? CHUNK : s.length());
    }

    REQUIRE(res);
    REQUIRE(res->is_valid());
    REQUIRE(res->http_version == "1.1");
    CHECK(res->code == 101);
    CHECK(res->full_message() == "101 Switching Protocols");
    CHECK(res->headers.get_field("Upgrade") == "websocket");
    CHECK(res->headers.get_field("Connection") == "Upgrade");
    CHECK(res->headers.get_field("Sec-WebSocket-Extensions") == "permessage-deflate; client_max_window_bits=15");
}

TEST_CASE("parsing request with fragmented chunks", "[fragmented]") {
    RequestParser p;
    RequestSP req;
    RequestParser::State final_state;

    std::vector<string> v = {
        "POST /upload HTTP/1.1\r\n"
        "Transfer-Encoding", ": chunked\r\n"
        "Trailer: Expires\r\n"
        "\r\n"
        "4;chunkex", "tension=somevalue\r\n"
        "Wiki\r\n"
        "5\r\n"
        "pedia\r\n"
        "E\r\n"
        " i", "n\r\n"
        "\r\n"
        "chunks.\r\n"
        "0\r\n"
        "Expires: Wed, 21 Oct 20", "15 07:28:00 GMT\r\n"
        "\r\n"
    };

    for (auto s : v) {
        if (req) REQUIRE(!req->is_valid());
        auto res =  p.parse(s);
        req = res.request;
        final_state = res.state.value_or(RequestParser::State::not_yet);
    }

    REQUIRE(req->is_valid());
    CHECK(final_state == RequestParser::State::done);
    CHECK(req->method == Method::POST);
    CHECK(req->http_version == "1.1");
    CHECK(req->headers.get_field("Transfer-Encoding") == "chunked");
    CHECK(req->headers.get_field("Trailer") == "Expires");
    CHECK(req->body.as_buffer() == "Wikipedia in\r\n\r\nchunks.");
    CHECK(req->has_body());
}

TEST_CASE("parsing 3 requests in a row", "[fragmented]") {
    const int CHUNK_SIZE = 74;
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
    auto req = result.request;

    REQUIRE(result.position == CHUNK_SIZE);
    REQUIRE(req->is_valid());
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->uri->to_string() == "/r1");
    REQUIRE(req->headers.get_field("Header1") == "header1");
    REQUIRE(req->headers.get_field("Header2") == "header2");
    REQUIRE(req->headers.get_field("Header3") == "header3");

    s.offset(result.position);
    result = p.parse(s);
    req = result.request;

    REQUIRE(result.position == CHUNK_SIZE);
    REQUIRE(req->is_valid());
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->uri->to_string() == "/r2");
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->headers.get_field("Header4") == "header4");
    REQUIRE(req->headers.get_field("Header5") == "header5");
    REQUIRE(req->headers.get_field("Header6") == "header6");

    s.offset(result.position);
    result = p.parse(s);
    req = result.request;

    REQUIRE(result.position == CHUNK_SIZE);
    REQUIRE(req->is_valid());
    REQUIRE(req->method == Method::GET);
    REQUIRE(req->http_version == "1.0");
    REQUIRE(req->uri->to_string() == "/r3");
    REQUIRE(req->headers.get_field("Header7") == "header7");
    REQUIRE(req->headers.get_field("Header8") == "header8");
    REQUIRE(req->headers.get_field("Header9") == "header9");

    s.offset(result.position);
    REQUIRE(s.empty());
}
