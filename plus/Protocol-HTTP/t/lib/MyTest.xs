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


uint64_t bench_headers_move (RequestSP req) {
    RETVAL = 0;
    Headers headers;
    for (size_t i = 0; i < 1000; ++i) {
        headers = std::move(req->headers);
        RETVAL += headers.size();
        req->headers = std::move(headers);
        RETVAL += req->headers.size();
    }
}

uint64_t bench_string_move (string s) {
    RETVAL = 0;
    auto ss = std::move(s);
    for (size_t i = 0; i < 1000000; ++i) {
        s = std::move(ss);
        ss = std::move(s);
    }
}

uint64_t bench_sm_move (RequestSP req) {
    RETVAL = 0;
    decltype(req->headers.fields) f;
    for (size_t i = 0; i < 1000; ++i) {
        f = std::move(req->headers.fields);
        RETVAL += f.size();
        req->headers.fields = std::move(f);
        RETVAL += req->headers.fields.size();
    }
}

uint64_t bench_sm_move2 (RequestSP req) {
    RETVAL = 0;
    struct Epta {
        string a;
        string b;
        Epta (const string& a, const string& b) : a(a), b(b) {}
        Epta (Epta&&) = default;
    };
    boost::container::small_vector<Epta, 15> f1;
    boost::container::small_vector<Epta, 15> f2;
    
    auto sz = req->headers.fields.size();
    for (size_t i = 0; i < sz; ++i) f2.push_back({req->headers.fields[i].name, req->headers.fields[i].value});
    
    for (size_t i = 0; i < 1000; ++i) {
        f1.clear();
        for (size_t i = 0; i < sz; ++i) f1.push_back(std::move(f2[i]));
        RETVAL += f1.size();
        sz = f1.size();

        f2.clear();
        for (size_t i = 0; i < sz; ++i) f2.push_back(std::move(f2[i]));
        RETVAL += f2.size();
        sz = f2.size();
    }
}

uint64_t bench_cookie (string s) {
    RETVAL = 0;
    RequestSP req = new Request();
    req->headers.add("Cookie", "session=1234567890abcdef1234567890abcdef; dasfdasfdas=dsfdasfdas; adsfdasfdasf=adsfdasf");
    req->headers.add("Content-Length", "123");
    req->headers.add("Accept-Encoding", "gzip, deflate");
    req->headers.add("Connection", "keep-alive");
    req->headers.add("Host", "crazypanda.ru");
    
    for (size_t i = 0; i < 1000; ++i) {
        //RETVAL += req->headers.get("Cookie").length();
        req->parse_cookie(req->headers.get("Cookie"));
        RETVAL += req->cookies.size();
        if (!RETVAL) throw "error";
        req->cookies.fields.clear();
    }
}

uint64_t bench_set_cookie (string s) {
    RETVAL = 0;
    ResponseSP res = new Response();
    for (size_t i = 0; i < 1000; ++i) {
        res->parse_set_cookie(s);
        RETVAL += res->cookies.size();
        if (!RETVAL) throw "error";
        res->cookies.fields.clear();
    }
}