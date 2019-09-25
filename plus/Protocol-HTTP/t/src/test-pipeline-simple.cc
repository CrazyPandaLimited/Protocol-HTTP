#include "../lib/test.h"

const std::string TEST_DIR = TEST_ROOT + "test-pipeline-simple";
const std::string TEST_REQUEST = "pipeline.txt";

TEST_CASE("parsing pipelined messages", "[parser]") {
    http::RequestParser request_parser;

    std::ifstream file(TEST_DIR+"/"+TEST_REQUEST, std::ios::binary);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    string buffer1(str.c_str());
    http::RequestParser::Result result = request_parser.parse_first(buffer1); 
    size_t position = result.position;
    auto request = result.request;

    _DBG("position: " << position);

    REQUIRE(request->is_valid());
    REQUIRE(request->method == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->uri->to_string() == "/r1");
    REQUIRE(request->headers.get_field("Header1") == "header1");
    REQUIRE(request->headers.get_field("Header2") == "header2");
    REQUIRE(request->headers.get_field("Header3") == "header3");
    
    string buffer2(buffer1.substr(position));
    result = request_parser.parse_first(buffer2); 
    position = result.position;
    request = result.request;
    
    _DBG("position: " << position);

    REQUIRE(request->is_valid());
    REQUIRE(request->method == Method::GET);
    REQUIRE(request->uri->to_string() == "/r2");
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->headers.get_field("Header4") == "header4");
    REQUIRE(request->headers.get_field("Header5") == "header5");
    REQUIRE(request->headers.get_field("Header6") == "header6");
    
    string buffer3(buffer2.substr(position));
    result = request_parser.parse_first(buffer3); 
    position = result.position;
    request = result.request;
    
    _DBG("position: " << position);
    
    REQUIRE(request->is_valid());
    REQUIRE(request->method == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->uri->to_string() == "/r3");
    REQUIRE(request->headers.get_field("Header7") == "header7");
    REQUIRE(request->headers.get_field("Header8") == "header8");
    REQUIRE(request->headers.get_field("Header9") == "header9");
}
