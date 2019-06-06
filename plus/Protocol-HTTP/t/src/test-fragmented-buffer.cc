#include "../lib/test.h"

const std::string TEST_DIR = TEST_ROOT + "test-fragmented-buffer";

const int CHUNK_SIZE = 74;

TEST_CASE("parsing fragmented messages allocating buffer", "[fragmented]") {

    http::RequestParser request_parser;
    http::RequestSP request = request_parser.message();

    for(auto file_name : read_directory(TEST_DIR)) {
        std::ifstream file(TEST_DIR+"/"+file_name, std::ios::binary);

        std::vector<char> file_buffer(CHUNK_SIZE, 0);
        string buffer;

        assert(file.read(file_buffer.data(), CHUNK_SIZE));
        
        buffer = string(file_buffer.data());

        http::RequestParser::Result result = request_parser.parse_first(buffer); 
        request = result.request;

        REQUIRE(request->is_valid());
        REQUIRE(request->method() == Method::GET);
        REQUIRE(request->http_version() == "1.0");
        REQUIRE(request->uri()->to_string() == "/r1");
        REQUIRE(request->header().get_field("Header1") == "header1");
        REQUIRE(request->header().get_field("Header2") == "header2");
        REQUIRE(request->header().get_field("Header3") == "header3");
        
        assert(file.read(file_buffer.data(), CHUNK_SIZE));
        buffer = string(file_buffer.data());

        result = request_parser.parse_first(buffer); 
        request = result.request;
        
        _DBG("position: " << result.position);

        REQUIRE(request->is_valid());
        REQUIRE(request->method() == Method::GET);
        REQUIRE(request->uri()->to_string() == "/r2");
        REQUIRE(request->http_version() == "1.0");
        REQUIRE(request->header().get_field("Header4") == "header4");
        REQUIRE(request->header().get_field("Header5") == "header5");
        REQUIRE(request->header().get_field("Header6") == "header6");
        
        assert(file.read(file_buffer.data(), CHUNK_SIZE));
        buffer = string(file_buffer.data());

        result = request_parser.parse_first(buffer); 
        request = result.request;
        
        _DBG("position: " << result.position);
        
        REQUIRE(request->is_valid());
        REQUIRE(request->method() == Method::GET);
        REQUIRE(request->http_version() == "1.0");
        REQUIRE(request->uri()->to_string() == "/r3");
        REQUIRE(request->header().get_field("Header7") == "header7");
        REQUIRE(request->header().get_field("Header8") == "header8");
        REQUIRE(request->header().get_field("Header9") == "header9");
    }

}
