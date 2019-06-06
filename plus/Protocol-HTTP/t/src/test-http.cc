#include "../lib/test.h"

TEST_CASE("trivial get request", "[parser]") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "\r\n";
    http::RequestSP request = request_parser.parse_first(raw).request;
    
    _DBG("request [" << request << "]");

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->header().get_field("Host") == "host1");
}

TEST_CASE("trivial get response", "[parser]") {
    http::ResponseParser response_parser;
    http::RequestSP request = make_iptr<http::Request>();
    request->method(Method::GET);
    response_parser.append_request(request);
    string raw =
        "HTTP/1.0 200 OK\r\n"
        "Host: host1\r\n"
        "\r\n";
    http::ResponseSP response = response_parser.parse_first(raw).response;
    
    _DBG("response [" << response << "]");

    REQUIRE(response->is_valid());
    REQUIRE(response->http_version() == "1.0");
    REQUIRE(response->header().get_field("Host") == "host1");
}

TEST_CASE("trivial head response", "[parser]") {
    http::ResponseParser response_parser;
    http::RequestSP request = make_iptr<http::Request>();
    request->method(Method::HEAD);
    response_parser.append_request(request);
    string raw =
        "HTTP/1.0 200 OK\r\n"
        "Host: host1\r\n"
        "Content-Length: 100500\r\n" // parser won't expect real body here for HEAD response
        "\r\n";
    http::ResponseSP response = response_parser.parse_first(raw).response;
    
    _DBG("response [" << response << "]");

    REQUIRE(response->is_valid());
    REQUIRE(response->http_version() == "1.0");
    REQUIRE(response->header().get_field("Host") == "host1");
}

TEST_CASE("redirect response", "[parser]") {
    http::ResponseParser response_parser;
    http::RequestSP request = make_iptr<http::Request>();
    request->method(Method::GET);
    response_parser.append_request(request);
    string raw =
	"HTTP/1.1 301 Moved Permanently\r\n"
	"Date: Thu, 22 Mar 2018 16:25:43 GMT\r\n"
	"Location: http://localhost:35615\r\n"
	"Content-Length: 163\r\n"
	"Content-Type: text/html\r\n"
	"\r\n"
	"<html><head><title>Moved</title></head><body><h1>Moved</h1><p>This page has moved to <a href=\"http://localhost:35615\">http://localhost:35615</a>.</p></body></html>\r\n";

    http::ResponseSP response = response_parser.parse_first(raw).response;
    
    _DBG("response " << response);

    REQUIRE(response->is_valid());
    REQUIRE(response->http_version() == "1.1");
    REQUIRE(response->header().get_field("Location") == "http://localhost:35615");
    REQUIRE(response->header().get_field("Date") == "Thu, 22 Mar 2018 16:25:43 GMT");
}

TEST_CASE("trivial post request", "[parser]") {
    http::RequestParser request_parser;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 23\r\n"
        "\r\n"
        "Wikipedia in\r\n\r\nchunks."
        ;
    http::RequestSP request = request_parser.parse_first(raw).request;

    _DBG("["<< request->body()->as_buffer() << "]");

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::POST);
    REQUIRE(request->http_version() == "1.1");
    REQUIRE(request->header().fields.size() == 1);
    REQUIRE(request->header().get_field("Content-Length") == "23");
    REQUIRE(request->body()->as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}

TEST_CASE("trivial chunked post request", "[parser]") {
    http::RequestParser request_parser;
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
    http::RequestSP request = request_parser.parse_first(raw).request;

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::POST);
    REQUIRE(request->http_version() == "1.1");
    REQUIRE(request->header().fields.size() == 1);
    REQUIRE(request->header().get_field("Transfer-Encoding") == "chunked");
    REQUIRE(request->body()->parts.size() == 3);
    REQUIRE(request->body()->as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}

TEST_CASE("chunked post request with extension", "[parser]") {
    http::RequestParser request_parser;
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
    http::RequestSP request = request_parser.parse_first(raw).request;

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::POST);
    REQUIRE(request->http_version() == "1.1");
    REQUIRE(request->header().fields.size() == 1);
    REQUIRE(request->header().get_field("Transfer-Encoding") == "chunked");
    REQUIRE(request->body()->parts.size() == 3);
    REQUIRE(request->body()->as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}

TEST_CASE("chunked post request with trailer header", "[parser]") {
    http::RequestParser request_parser;
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
    http::RequestSP request = request_parser.parse_first(raw).request;

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::POST);
    REQUIRE(request->http_version() == "1.1");
    REQUIRE(request->header().fields.size() == 2);
    REQUIRE(request->header().get_field("Transfer-Encoding") == "chunked");
    REQUIRE(request->body()->parts.size() == 3);
    REQUIRE(request->body()->as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}

TEST_CASE("trimming spaces from header value", "http-unusual") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: host \r\n"
        "\r\n";
    http::RequestSP request = request_parser.parse_first(raw).request;
    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->header().fields.size() == 1);
    REQUIRE(request->header().get_field("Host") == "host");
}

TEST_CASE("no space after header field", "http-unusual") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host:host\r\n"
        "\r\n";

    http::RequestSP request = request_parser.parse_first(raw).request;

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->header().get_field("Host") == "host");
    REQUIRE(request->header().fields.size() == 1);
}

TEST_CASE("no header at all", "http-unusual") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "\r\n";
    http::RequestSP request = request_parser.parse_first(raw).request;

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->header().fields.size() == 0);
}

TEST_CASE("space in header value", "http-unusual") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: ho  st\r\n"
        "\r\n";
    http::RequestSP request = request_parser.parse_first(raw).request;

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->header().get_field("Host") == "ho  st");
    REQUIRE(request->header().fields.size() == 1);
}

TEST_CASE("colon 1", "http-unusual") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host:: host\r\n"
        "\r\n";
    http::RequestSP request = request_parser.parse_first(raw).request;

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->header().get_field("Host") == ": host");
    REQUIRE(request->header().fields.size() == 1);
}

TEST_CASE("colon 2", "http-unusual") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: h:ost\r\n"
        "\r\n";
    http::RequestSP request = request_parser.parse_first(raw).request;

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->header().get_field("Host") == "h:ost");
    REQUIRE(request->header().fields.size() == 1);
}

TEST_CASE("multiple spaces", "http-unusual") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: hh oo ss tt\r\n"
        "\r\n";
    http::RequestSP request = request_parser.parse_first(raw).request;

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->header().get_field("Host") == "hh oo ss tt");
    REQUIRE(request->header().fields.size() == 1);
}

TEST_CASE("duplicated header field", "http-unusual") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "Host: host1\r\n"
        "Host: host2\r\n"
        "\r\n";
    http::RequestSP request = request_parser.parse_first(raw).request;

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->header().get_field("Host") == "host2");
    REQUIRE(request->header().fields.size() == 2);
}

TEST_CASE("case insensitive content-length", "http-unusual") {
    http::RequestParser request_parser;
    string raw =
        "GET / HTTP/1.0\r\n"
        "content-length: 1\r\n"
        "\r\n"
        "1";
    http::RequestSP request = request_parser.parse_first(raw).request;

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->header().fields.size() == 1);
    REQUIRE(request->body()->as_buffer() == "1");
}

TEST_CASE("case insensitive headers", "[parser]") {
    http::Header h;
    h.add_field("Aa", "value");
    CHECK(h.get_field("AA") == "value");
}
