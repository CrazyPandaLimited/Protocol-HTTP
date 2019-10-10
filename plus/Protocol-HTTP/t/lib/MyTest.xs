#include <xs.h>
#include <panda/protocol/http.h>

using namespace panda;
using namespace panda::protocol::http;

MODULE = MyTest                PACKAGE = MyTest
PROTOTYPES: DISABLE

void _benchmark () {
    RequestParser p;
    string buf =
        "POST http://alx3apps.appspot.com/jsonrpc_example/json_service/ HTTP/1.1\r\n"
        "Host: alx3apps.appspot.com\r\n"
        "Content-Length: 55\r\n"
        "\r\n"
        "{\"params\":[\"Howdy\",\"Python!\"],\"method\":\"concat\",\"id\":1}";
    
    for (auto i = 0; i < 1000; ++i) {
        p.parse(buf);
    }
}

void _benchmark_min () {
    RequestParser p;
    string buf =
        "GET / HTTP/1.1\r\n"
        "Host: ya.ru\r\n"
        "\r\n";
    
    for (auto i = 0; i < 1000; ++i) {
        p.parse(buf);
    }
}


void _benchmark_body () {
    RequestParser p;
    string buf =
        "POST http://alx3apps.appspot.com/jsonrpc_example/json_service/ HTTP/1.1\r\n"
        "Host: alx3apps.appspot.com\r\n"
        "Content-Length: 500\r\n"
        "\r\n"
        "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
        "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
        "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
        "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
        "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";

    for (auto i = 0; i < 1000; ++i) {
        p.parse(buf);
    }
}

void _benchmark_heavy_headers () {
    RequestParser p;
    string buf =
        "POST http://alx3apps.appspot.com/jsonrpc_example/json_service/ HTTP/1.1\r\n"
        "Host: alx3apps.appspot.com\r\n"
        "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; en-GB; rv:1.9.2.13) Gecko/20101203 Firefox/3.6.13\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
        "Accept-Language: en-gb,en;q=0.5\r\n"
        "Accept-Encoding: gzip,deflate\r\n"
        "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
        "Keep-Alive: 115\r\n"
        "Connection: keep-alive\r\n"
        "Content-Type: application/json-rpc; charset=UTF-8\r\n"
        "X-Requested-With: XMLHttpRequest\r\n"
        "Referer: http://alx3apps.appspot.com/jsonrpc_example/\r\n"
        "Content-Length: 55\r\n"
        "Pragma: no-cache\r\n"
        "Cache-Control: no-cache\r\n"
        "\r\n"
        "{\"params\":[\"Howdy\",\"Python!\"],\"method\":\"concat\",\"id\":1}";
    
    for (auto i = 0; i < 1000; ++i) {
        p.parse(buf);
    }
}

void bench2 () {
    RequestParser p;
    string buf =
        "GET /49652gatedesc.xml HTTP/1.0\r\n"
        "Host: 192.168.100.1:49652\r\n"
        "User-Agent: Go-http-client/1.1\r\n"
        "Accept-Encoding: gzip\r\n"
        "\r\n";
    for (auto i = 0; i < 1000000; ++i) {
        p.parse(buf);
    }
}
