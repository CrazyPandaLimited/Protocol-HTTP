#include "../lib/test.h"

TEST_CASE("google response 0", "[parser]") {
    http::ResponseParser response_parser;
    http::RequestSP request = make_iptr<http::Request>();
    request->method(Method::GET);
    response_parser.append_request(request);
    
    string raw =
        "HTTP/1.1 302 Found\r\n"
        "Cache-Control: private\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Referrer-Policy: no-referrer\r\n"
        "Location: http://www.google.ru/?gfe_rd=cr&dcr=0&ei=dlSVWsfRFMiG7gT1wK8Q\r\n"
        "Content-Length: 266\r\n"
        "Date: Tue, 27 Feb 2018 12:52:06 GMT\r\n"
        "\r\n"
        "<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\r\n"
        "<TITLE>302 Moved</TITLE></HEAD><BODY>\r\n"
        "<H1>302 Moved</H1>\r\n"
        "The document has moved\r\n"
        "<A HREF=\"http://www.google.ru/?gfe_rd=cr&amp;dcr=0&amp;ei=dlSVWsfRFMiG7gT1wK8Q\">here</A>.\r\n"
        "</BODY></HTML>\r\n";

    http::ResponseSP response = response_parser.parse_first(raw).response;
    
    _DBG("response " << response);

    REQUIRE(response->is_valid());
    REQUIRE(response->http_version() == "1.1");
}

TEST_CASE("google response 1", "[parser]") {
    const std::string TEST_DIR = TEST_ROOT + "test-regress-1";
    http::ResponseParser response_parser;
    http::RequestSP request = make_iptr<http::Request>();
    request->method(Method::GET);
    response_parser.append_request(request);
    
    http::ResponseSP response;

    for(auto file_name : read_directory(TEST_DIR)) {
        std::ifstream file(TEST_DIR+"/"+file_name, std::ios::binary);
        std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
       
        string buffer(str.c_str()); 
        response = response_parser.parse_first(buffer).response;
    }

    _DBG("response " << response);

    REQUIRE(response->is_valid());
    REQUIRE(response->http_version() == "1.1");
}
