#include "../lib/test.h"

const std::string TEST_DIR = TEST_ROOT + "test-fragmented-simple";

TEST_CASE("parsing message fragmented by lines", "[fragmented]") {
    http::RequestParser request_parser;
    http::RequestSP request;

    for(auto file_name : read_directory(TEST_DIR)) {
        if (request) REQUIRE(!request->is_valid());

        std::ifstream file(TEST_DIR+"/"+file_name, std::ios::binary);
        std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
       
        string buffer(str.c_str()); 
        request = request_parser.parse_first(buffer).request;
    }

    REQUIRE(request->is_valid());
    REQUIRE(request->method == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->headers.get_field("Header1") == "header1");
    REQUIRE(request->headers.get_field("Header2") == "header2");
    REQUIRE(request->headers.get_field("Header3") == "header3");
}
