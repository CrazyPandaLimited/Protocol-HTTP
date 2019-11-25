#include "../lib/test.h"

#define TEST(name) TEST_CASE("compile-chunks: " name, "[compile-chunks]")

TEST("chunked message force version 1.1") {
    auto req = Request::Builder().chunked().http_version(10).build();
    CHECK(req->to_string() ==
        "GET / HTTP/1.1\r\n"
        "Transfer-Encoding: chunked\r\n"
        "\r\n"
    );
}

TEST("generating chunks later") {
    auto req = Request::Builder().chunked().build();

    string s = "hello world";

    auto v = req->make_chunk(s);
    CHECK(v.size() == 3);
    CHECK(v[0] == "b\r\n");
    CHECK(v[1] == s);
    CHECK(v[1].data() == s.data()); // payload doesn't get copied
    CHECK(v[2] == "\r\n");

    CHECK(req->final_chunk() == "0\r\n\r\n");
}

TEST("empty chunk is not a final chunk - it gets ignored") {
    auto req = Request::Builder().chunked().build();
    auto v = req->make_chunk("");
    CHECK(v.size() == 3);
    CHECK(v[0] == "");
    CHECK(v[1] == "");
    CHECK(v[2] == "");
}

//TEST("chunked message with all content given now") {
//    Body body;
//    body.parts.push_back("hello ");
//    body.parts.push_back("world");
//    auto req = Request::Builder().body(std::move(body)).chunked().build();
//    WARN(req->to_string());
//    WARN(        "GET / HTTP/1.1\r\n"
//        "Transfer-Encoding: chunked\r\n"
//        "\r\n"
//        "6\r\n"
//        "hello \r\n"
//        "5\r\n"
//        "world\r\n"
//        "0\r\n"
//        "\r\n"
//);
//    CHECK(req->to_string() ==
//        "GET / HTTP/1.1\r\n"
//        "Transfer-Encoding: chunked\r\n"
//        "\r\n"
//        "6\r\n"
//        "hello \r\n"
//        "5\r\n"
//        "world\r\n"
//        "0\r\n"
//        "\r\n"
//    );
//}
