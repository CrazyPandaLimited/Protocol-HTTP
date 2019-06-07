#include "../lib/test.h"

const std::string TEST_DIR = TEST_ROOT + "test-fragmented-bytes";

TEST_CASE("parsing message byte by byte", "[fragmented]") {
    http::RequestParser request_parser;
    http::RequestSP request = request_parser.message();

    char file_buffer;
    for(auto file_name : read_directory(TEST_DIR)) {
        REQUIRE(!request->is_valid());

        std::ifstream file(TEST_DIR+"/"+file_name, std::ios::binary);

        while(file.read(&file_buffer, 1)) {
            request = request_parser.parse_first(string(&file_buffer, 1)).request;
	}
    }

    _DBG(request);

    REQUIRE(request->is_valid());
    REQUIRE(request->method == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->headers.get_field("Header1") == "header1");
    REQUIRE(request->headers.get_field("Header2") == "header2");
    REQUIRE(request->headers.get_field("Header3") == "header3");
}
