#include "../lib/test.h"

const std::string TEST_DIR = TEST_ROOT + "test-fragmented-chunks";

TEST_CASE("parsing message with fragmented chunks", "[fragmented]") {
    http::RequestParser request_parser;
    http::RequestSP request;
    http::RequestParser::State final_state;

    for (auto file_name : read_directory(TEST_DIR)) {
        if (request) REQUIRE(!request->is_valid());

        std::ifstream file(TEST_DIR+"/"+file_name, std::ios::binary);
        std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
       
        string buffer(str.c_str()); 
        auto res =  request_parser.parse_first(buffer);
        request = res.request;
        final_state = res.state.value_or(http::RequestParser::State::not_yet);
    }

    _DBG(
            "request: version: " << request->http_version() 
            << " method: " << static_cast<int>(request->method)
            << " uri: " << request->uri
    );

    
    for(auto field : request->headers.fields) {
        _DBG("header: "<< field.name << ":" << field.value);
    }

    for(auto part : request->body->parts) {
        _DBG("body part: [" << part << "]");
    }

    _DBG(request->headers.get_field("Header1"));

    REQUIRE(request->is_valid());
    CHECK(final_state == http::RequestParser::State::done);
    CHECK(request->method == Method::POST);
    CHECK(request->http_version() == "1.1");
    CHECK(request->headers.get_field("Transfer-Encoding") == "chunked");
    CHECK(request->headers.get_field("Trailer") == "Expires");
    CHECK(request->body->as_buffer() == "Wikipedia in\r\n\r\nchunks.");
    CHECK(request->has_body());
}
