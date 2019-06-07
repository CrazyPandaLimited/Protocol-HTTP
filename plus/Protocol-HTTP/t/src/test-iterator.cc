#include "../lib/test.h"

const std::string TEST_DIR = TEST_ROOT + "test-iterator";
const std::string TEST_REQUEST = "request.txt";
const std::string TEST_RESPONSE = "response.txt";

TEST_CASE("parsing request with iterator", "[iterator]") {
    http::RequestParser request_parser;
    http::RequestSP request = request_parser.message();

    std::ifstream file(TEST_DIR+"/"+TEST_REQUEST, std::ios::binary);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    string buffer(str.c_str());
    http::RequestParser::ResultIterator pos = request_parser.parse(buffer); 
    http::RequestParser::Result result = *pos;
    request = result.request;

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->uri()->to_string() == "/r1");
    REQUIRE(request->headers.get_field("Header1") == "header1");
    REQUIRE(request->headers.get_field("Header2") == "header2");
    REQUIRE(request->headers.get_field("Header3") == "header3");
    
    result = *(pos++);
    request = result.request;
    
    _DBG("position: " << result.position);

    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->uri()->to_string() == "/r2");
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->headers.get_field("Header4") == "header4");
    REQUIRE(request->headers.get_field("Header5") == "header5");
    REQUIRE(request->headers.get_field("Header6") == "header6");
    
    result = *(pos++);
    request = result.request;
    
    _DBG("position: " << result.position);
    
    REQUIRE(request->is_valid());
    REQUIRE(request->method() == Method::GET);
    REQUIRE(request->http_version() == "1.0");
    REQUIRE(request->uri()->to_string() == "/r3");
    REQUIRE(request->headers.get_field("Header7") == "header7");
    REQUIRE(request->headers.get_field("Header8") == "header8");
    REQUIRE(request->headers.get_field("Header9") == "header9");
    
    result = *(pos++);
    
    _DBG("position: " << result.position);

    request = result.request;
    REQUIRE(result.state == http::RequestParser::State::not_yet);
    REQUIRE(!request->is_valid());
}

TEST_CASE("parsing response with iterator", "[iterator]") {
    http::ResponseParser response_parser;
    http::ResponseSP response;

    // dont know the right response type, so will throw
    REQUIRE_THROWS_AS([&]{response_parser.message();}(), http::ParserError);
    
    http::RequestSP request = make_iptr<http::Request>();
    request->method(Method::GET);
    response_parser.append_request(request);
    response_parser.append_request(request);
    response_parser.append_request(request);
    
    // known response type, will create a new empty one
    response = response_parser.message();

    REQUIRE(!response->is_valid());

    std::ifstream file(TEST_DIR+"/"+TEST_RESPONSE, std::ios::binary);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    string buffer(str.c_str());
    http::ResponseParser::ResultIterator pos = response_parser.parse(buffer); 
    http::ResponseParser::Result result = *pos;
    response = result.response;
    
    REQUIRE(response->is_valid());
    REQUIRE(response->code() == 200);
    REQUIRE(response->http_version() == "1.0");
    REQUIRE(response->headers.get_field("Header1") == "header1");
    REQUIRE(response->headers.get_field("Header2") == "header2");
    REQUIRE(response->headers.get_field("Header3") == "header3");
    
    result = *(pos++);
    response = result.response;
    
    _DBG("position 1: " << result.position);

    REQUIRE(response->is_valid());
    REQUIRE(response->code() == 200);
    REQUIRE(response->http_version() == "1.0");
    REQUIRE(response->headers.get_field("Header4") == "header4");
    REQUIRE(response->headers.get_field("Header5") == "header5");
    REQUIRE(response->headers.get_field("Header6") == "header6");
    
    result = *(pos++);
    response = result.response;
    
    _DBG("position 2: " << result.position);
    
    REQUIRE(response->is_valid());
    REQUIRE(response->code() == 200);
    REQUIRE(response->http_version() == "1.0");
    REQUIRE(response->headers.get_field("Header7") == "header7");
    REQUIRE(response->headers.get_field("Header8") == "header8");
    REQUIRE(response->headers.get_field("Header9") == "header9");
    
    result = *(pos++);
    
    _DBG("position 3: " << result.position);

    response = result.response;
    REQUIRE(result.state == http::ResponseParser::State::not_yet);
   
    // will be nullptr, because there are no response yet
    REQUIRE(!response);
}

TEST_CASE("assign and compare iterators", "[iterator]") {
    http::RequestParser request_parser;
    http::RequestSP request = request_parser.message();

    std::ifstream file(TEST_DIR+"/"+TEST_REQUEST, std::ios::binary);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    string buffer(str.c_str());
    http::RequestParser::ResultIterator iter1 = request_parser.parse(buffer); 
    http::RequestParser::ResultIterator iter2 = iter1;
    REQUIRE(iter1 == iter2);
    
    http::RequestParser::Result result = *(++iter1);
    _DBG("iter1: " << (*iter1).position);
    _DBG("iter2: " << (*iter2).position);
    REQUIRE(iter1 != iter2);
}

TEST_CASE("loop with iterator", "[iterator]") {
    http::RequestParser request_parser;

    //for(int i = 0; i < 2; ++i) 
    { 
        string buffer;
        buffer =  
                "POST http://alx3apps.appspot.com/jsonrpc_example/json_service/ HTTP/1.1\r\n"
                "Host: alx3apps.appspot.com\r\n"
                "Content-Length: 55\r\n"
                "\r\n"
                "{\"params\":[\"Howdy\",\"Python!\"],\"method\":\"concat\",\"id\":1}";

        http::RequestParser::ResultIterator iter = request_parser.parse(buffer);
    }
   
    { 
        string buffer;
        buffer =  
                "POST http://alx3apps.appspot.com/jsonrpc_example/json_service/ HTTP/1.1\r\n"
                "Host: alx3apps.appspot.com\r\n"
                "Content-Length: 55\r\n"
                "\r\n"
                "{\"params\":[\"Howdy\",\"Python!\"],\"method\":\"concat\",\"id\":1}";

        http::RequestParser::ResultIterator iter = request_parser.parse(buffer);
    }
}
