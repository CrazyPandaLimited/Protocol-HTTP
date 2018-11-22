#include "../lib/test.h"

const std::string TEST_DIR = TEST_ROOT + "test-fragmented-chunks";

TEST_CASE("parsing message with fragmented chunks", "[fragmented]") {
    http::RequestParser request_parser;
    http::RequestSP request = request_parser.message();

    for(auto file_name : read_directory(TEST_DIR)) {
        REQUIRE(!request->is_valid());

        std::ifstream file(TEST_DIR+"/"+file_name, std::ios::binary);
        std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
       
        string buffer(str.c_str()); 
        request = request_parser.parse_first(buffer).request;
    }

    _DBG(
            "request: version: " << request->http_version() 
            << " method: " << static_cast<int>(request->method()) 
            << " uri: " << request->uri()
    );
    
    for(auto field : request->header()->fields) {
        _DBG("header: "<< field.name << ":" << field.value);
    }

    for(auto part : request->body()->parts) {
        _DBG("body part: [" << part << "]");
    }

    _DBG(request->header()->get_field("Header1"));

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::POST);
    REQUIRE(request->http_version() == "1.1");
    REQUIRE(request->header()->get_field("Transfer-Encoding") == "chunked");
    REQUIRE(request->header()->get_field("Trailer") == "Expires");
    REQUIRE(request->body()->as_buffer() == "Wikipedia in\r\n\r\nchunks.");
}
