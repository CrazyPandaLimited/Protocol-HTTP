#include "lib/test.h"
#include <set>
#include <fstream>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

const string ROOT = "t/regression/";

inline std::set<string> read_directory (const string& name = ".") {
    DIR* dirp = opendir(name.c_str());
    struct dirent* dp;
    std::set<string> v;
    while ((dp = readdir(dirp)) != NULL) {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) continue;
        v.insert(string(dp->d_name, strlen(dp->d_name)));
    }
    closedir(dirp);
    return v;
}

TEST_CASE("google response 0", "[regression]") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::GET;
    p.set_request(req);
    
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

    auto result = p.parse(raw);
    CHECK(result.state == State::done);
    REQUIRE(result.response->http_version == HttpVersion::v1_1);
}

TEST_CASE("google response 1", "[regression]") {
    ResponseParser p;
    RequestSP req = new Request();
    req->method = Method::GET;
    p.set_request(req);
    
    ResponseParser::Result result;
    auto DIR = ROOT+"1";
    for (auto fname : read_directory(DIR)) {
        CHECK(result.state != State::done);
        std::ifstream file(DIR+"/"+fname, std::ios::binary);
        std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        result = p.parse(string(str.c_str()));
    }
    CHECK(result.state == State::done);

    REQUIRE(result.response->http_version == HttpVersion::v1_1);
}
