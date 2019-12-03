#include <xs/protocol/http.h>

using namespace panda;
using namespace panda::protocol::http;

MODULE = MyTest                PACKAGE = MyTest
PROTOTYPES: DISABLE

uint64_t bench_iequals (string_view a, string_view b) {
    RETVAL = 0;
    for (auto i = 0; i < 1000; ++i) {
        RETVAL += iequals(a, b);
    }
}

void bench () {
    RequestParser p;
    string buf =
        "POST http://alx3apps.appspot.com/jsonrpc_example/json_service/ HTTP/1.1\r\n"
        "Host: alx3apps.appspot.com\r\n"
        "Content-Length: 55\r\n"
        "\r\n"
        "{\"params\":[\"Howdy\",\"Python!\"],\"method\":\"concat\",\"id\":1}";
    if (p.parse(buf).error) throw p.parse(buf).error;
    
    for (auto i = 0; i < 1000; ++i) {
        p.parse(buf);
    }
}

void bench_min () {
    RequestParser p;
    string buf =
        "GET / HTTP/1.1\r\n"
        "Host: ya.ru\r\n"
        "\r\n";
    if (p.parse(buf).error) throw p.parse(buf).error;
    
    for (auto i = 0; i < 1000; ++i) {
        p.parse(buf);
    }
}

void bench_res_min () {
    RequestSP req = new Request();
    ResponseParser p;
    p.set_context_request(req);
    string buf =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 0\r\n"
        "\r\n";
    if (p.parse(buf).error) throw p.parse(buf).error;
    
    for (auto i = 0; i < 1000; ++i) {
        p.set_context_request(req);
        p.parse(buf);
    }
}

void bench_mid () {
    RequestParser p;
    string buf =
        "GET /49652gatedesc.xml HTTP/1.0\r\n"
        "Host: 192.168.100.1:49652\r\n"
        "User-Agent: Go-http-client/1.1\r\n"
        "Accept-Encoding: gzip\r\n"
        "\r\n";
    if (p.parse(buf).error) throw p.parse(buf).error;
    
    for (auto i = 0; i < 1000; ++i) {
        p.parse(buf);
    }
}

void bench_res_mid () {
    RequestSP req = new Request();
    ResponseParser p;
    p.set_context_request(req);
    string buf =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 0\r\n"
        "Host: 192.168.100.1:49652\r\n"
        "User-Agent: Go-http-client/1.1\r\n"
        "Accept-Encoding: gzip\r\n"
        "\r\n";
    if (p.parse(buf).error) throw p.parse(buf).error;
    
    for (auto i = 0; i < 1000; ++i) {
        p.set_context_request(req);
        p.parse(buf);
    }
}

void bench_mid2 () {
    RequestParser p;
    string buf =
        "GET /49652gatedesc/dasfdsf/sdf.xml?ddsf=dsfdsf&adsfdsf=dafdsfds HTTP/1.0\r\n"
        "Host: 192.168.100.1:49652\r\n"
        "User-Agent: Go-http-client/1.1\r\n"
        "Accept-Encoding: gzip\r\n"
        "\r\n";
    if (p.parse(buf).error) throw p.parse(buf).error;
    
    for (auto i = 0; i < 1000; ++i) {
        p.parse(buf);
    }
}

void bench_body () {
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
    if (p.parse(buf).error) throw p.parse(buf).error;

    for (auto i = 0; i < 1000; ++i) {
        p.parse(buf);
    }
}

void bench_heavy_headers () {
    RequestParser p;
    string buf =
        "POST http://alx3apps.appspot.com/jsonrpc_example/json_service/ HTTP/1.1\r\n"
        "Host: alx3apps.appspot.com\r\n"
        "User-Agent: Mozilla/5.0(Windows;U;WindowsNT6.1;en-GB;rv:1.9.2.13)Gecko/20101203Firefox/3.6.13\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
        "Accept-Language: en-gb,en;q=0.5\r\n"
        "Accept-Encoding: gzip,deflate\r\n"
        "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
        "Keep-Alive: 115\r\n"
        "Connection: keep-alive\r\n"
        "Content-Type: application/json-rpc;charset=UTF-8\r\n"
        "X-Requested-With: XMLHttpRequest\r\n"
        "Referer: http://alx3apps.appspot.com/jsonrpc_example/\r\n"
        "Content-Length: 0\r\n"
        "Pragma: no-cache\r\n"
        "Cache-Control: no-cache\r\n"
        "\r\n"
        ;
    if (p.parse(buf).error) throw p.parse(buf).error;
    
    for (auto i = 0; i < 1000; ++i) {
        p.parse(buf);
    }
}

void bench_heavy_cookies () {
    RequestParser p;
    string buf =
        "GET / HTTP/1.1\r\n"
        "Content-Length: 0\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "Cookie: asfkldasfkljdskjfjkldsfkljdas=dasfkjdhjsfjdsafkj; asdfdasfdasfdasf=dasfdasfjkdashfds\r\n"
        "\r\n"
        ;
    if (p.parse(buf).error) throw p.parse(buf).error;
    
    for (auto i = 0; i < 1000; ++i) {
        p.parse(buf);
    }
}

void bench_res_heavy_headers () {
    RequestSP req = new Request();
    ResponseParser p;
    p.set_context_request(req);
    string buf =
        "HTTP/1.1 200 OK\r\n"
        "Host: alx3apps.appspot.com\r\n"
        "User-Agent: Mozilla/5.0(Windows;U;WindowsNT6.1;en-GB;rv:1.9.2.13)Gecko/20101203Firefox/3.6.13\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
        "Accept-Language: en-gb,en;q=0.5\r\n"
        "Accept-Encoding: gzip,deflate\r\n"
        "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
        "Keep-Alive: 115\r\n"
        "Connection: keep-alive\r\n"
        "Content-Type: application/json-rpc;charset=UTF-8\r\n"
        "X-Requested-With: XMLHttpRequest\r\n"
        "Referer: http://alx3apps.appspot.com/jsonrpc_example/\r\n"
        "Content-Length: 0\r\n"
        "Pragma: no-cache\r\n"
        "Cache-Control: no-cache\r\n"
        "\r\n"
        ;
    if (p.parse(buf).error) throw p.parse(buf).error;
    p.eof();
    
    for (auto i = 0; i < 1000; ++i) {
        p.set_context_request(req);
        p.parse(buf);
        p.eof();
    }
}
