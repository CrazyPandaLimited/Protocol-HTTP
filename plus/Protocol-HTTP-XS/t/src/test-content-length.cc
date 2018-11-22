#include "../lib/test.h"

TEST_CASE("post with content-length content as single buffer", "[content-length]") {
    http::RequestParser request_parser;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 23\r\n"
        "\r\n"
        "Wikipedia in\r\n\r\nchunks."
        ;
    http::RequestParser::Result result = request_parser.parse_first(raw);

    REQUIRE(result.state == State::got_body);
    
    http::RequestSP request = result.request;

    _DBG("["<< request->body()->as_buffer() << "]");
    
    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::POST);
    REQUIRE(request->http_version() == "1.1");
    REQUIRE(request->header()->fields.size() == 1);
    REQUIRE(request->header()->get_field("Content-Length") == "23");
    REQUIRE(request->body()->as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}

TEST_CASE("post with content-length content in parts", "[content-length]") {
    http::RequestParser request_parser;
    http::RequestParser::Result result;
    result = request_parser.parse_first("POST /upload HTTP/1.1\r\nContent-Length: 23\r\n\r");
    
    REQUIRE(!result.request->is_valid());
    REQUIRE(result.state == State::not_yet);

    result = request_parser.parse_first("\n");
    
    REQUIRE(!result.request->is_valid());
    REQUIRE(result.state == State::in_body);

    result = request_parser.parse_first("W");

    REQUIRE(!result.request->is_valid());
    REQUIRE(result.state == State::in_body);
    
    result = request_parser.parse_first("i");

    REQUIRE(!result.request->is_valid());
    REQUIRE(result.state == State::in_body);
    
    result = request_parser.parse_first("kipedia in\r\n");
    
    REQUIRE(!result.request->is_valid());
    REQUIRE(result.state == State::in_body);
    
    result = request_parser.parse_first("\r\nchunks.");
    
    REQUIRE(result.request->is_valid());
    REQUIRE(result.state == State::got_body);

    http::RequestSP request = result.request;

    _DBG("["<< request->body()->as_buffer() << "]");

    REQUIRE(request->method() == Method::POST);
    REQUIRE(request->http_version() == "1.1");
    REQUIRE(request->header()->fields.size() == 1);
    REQUIRE(request->header()->get_field("Content-Length") == "23");
    REQUIRE(request->body()->as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}

TEST_CASE("post with null content-length", "[content-length]") {
    http::RequestParser request_parser;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 0\r\n"
        "\r\n"
        ;
    http::RequestParser::Result result = request_parser.parse_first(raw);

    REQUIRE(result.state == State::got_header);
    
    http::RequestSP request = result.request;

    _DBG("["<< request->body()->as_buffer() << "]");
    
    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::POST);
    REQUIRE(request->http_version() == "1.1");
    REQUIRE(request->header()->fields.size() == 1);
    REQUIRE(request->header()->get_field("Content-Length") == "0");
    REQUIRE(request->body()->as_buffer() == "");
}

TEST_CASE("post iterator single request", "[content-length]") {
    http::RequestParser request_parser;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 2\r\n"
        "\r\n"
        ;

    http::RequestParser::ResultIterator pos = request_parser.parse(raw);
    http::RequestParser::Result result = *pos; 

    REQUIRE(result.state == State::in_body);

    result = request_parser.parse_first("X");
    
    REQUIRE(result.state == State::in_body);

    _DBG("["<< result.request->body()->as_buffer() << "]");
    
    result = request_parser.parse_first("X");
    
    REQUIRE(result.state == State::got_body);

    _DBG("["<< result.request->body()->as_buffer() << "]");

    http::RequestSP request = result.request;
    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::POST);
    REQUIRE(request->http_version() == "1.1");
    REQUIRE(request->header()->fields.size() == 1);
    REQUIRE(request->header()->get_field("Content-Length") == "2");
    REQUIRE(request->body()->as_buffer() == "XX");
}

TEST_CASE("post iterator multiple messages", "[content-length]") {
    http::RequestParser request_parser;
    string raw =
        "POST /upload HTTP/1.1\r\n"
        "Content-Length: 2\r\n"
        "\r\n"
        ;

    http::RequestParser::ResultIterator pos = request_parser.parse(raw);
    http::RequestParser::Result result1 = *pos; 

    REQUIRE(result1.state == State::in_body);

    result1 = request_parser.parse_first("X");
    
    REQUIRE(result1.state == State::in_body);

    _DBG("["<< result1.request->body()->as_buffer() << "]");
    
    result1 = request_parser.parse_first("X" + raw);
    
    REQUIRE(result1.state == State::got_body);

    _DBG("["<< result1.request->body()->as_buffer() << "]");

    http::RequestSP request1 = result1.request;
    REQUIRE(request1->is_valid());
    REQUIRE(request1->method() == Method::POST);
    REQUIRE(request1->http_version() == "1.1");
    REQUIRE(request1->header()->fields.size() == 1);
    REQUIRE(request1->header()->get_field("Content-Length") == "2");
    REQUIRE(request1->body()->as_buffer() == "XX");

    // parse nto the second result with the same iterator
    pos = request_parser.parse(raw);
    http::RequestParser::Result result2 = *pos; 
    
    _DBG("state: " << (int)result2.state);
    _DBG("["<< result2.request->body()->as_buffer() << "]");
   
    REQUIRE(result2.state == State::in_body);

    result2 = request_parser.parse_first("YY");
    
    _DBG("["<< result2.request->body()->as_buffer() << "]");
    
    http::RequestSP request2 = result2.request;
    REQUIRE(request2->is_valid());
    REQUIRE(request2->method() == Method::POST);
    REQUIRE(request2->http_version() == "1.1");
    REQUIRE(request2->header()->fields.size() == 1);
    REQUIRE(request2->header()->get_field("Content-Length") == "2");
    REQUIRE(request2->body()->as_buffer() == "YY");
   
    // ensure that the first request is not modified 
    REQUIRE(request1->body()->as_buffer() == "XX");
}
