#include "../lib/test.h"
#include <regex>

#define TEST(name) TEST_CASE("compile-form: " name, "[compile-form]")

TEST("multipart/form-data") {
    std::srand(123);

    string str =
        "POST / HTTP/1.1\r\n"
        "Content-Length: 226\r\n"
        "Content-Type: multipart/form-data; boundary=-----------------------Tr8hHQ2MZKozcfPSt\r\n"
        "\r\n"
        "-----------------------Tr8hHQ2MZKozcfPSt\r\n"
        "Content-Disposition: form-data; name=\"k1\"\r\n"
        "\r\n"
        "v1\r\n"
        "-----------------------Tr8hHQ2MZKozcfPSt\r\n"
        "Content-Disposition: form-data; name=\"k2\"\r\n"
        "\r\n"
        "v2\r\n"
        "-----------------------Tr8hHQ2MZKozcfPSt--\r\n";
    //auto d = std::mismatch(data.begin(), data.end(), str.begin());

    SECTION("empty form -> no body is sent, method is still GET") {
        Request::Form form(Request::EncType::MULTIPART);
        auto req = Request::Builder().form(std::move(form)).build();
        CHECK(req->to_string() ==
            "GET / HTTP/1.1\r\n"
            "\r\n"
        );
    }

    SECTION("create simple form and serialize it") {
        Request::Form form(Request::EncType::MULTIPART);
        form.add("k1", "v1");
        form.add("k2", "v2");
        auto req = Request::Builder().form(std::move(form)).build();
        auto data = req->to_string();
        CHECK(data == str);
    }

    SECTION("uri query -> form") {
        Request::Form form(Request::EncType::MULTIPART);
        auto req = Request::Builder()
                .uri("/?k1=v1&k2=v2")
                .form(std::move(form))
                .build();
        auto data = req->to_string();
        CHECK(data == str);
    }

    SECTION("boundary cannot be part of key/value") {
        string sample =
            "POST / HTTP/1.1\r\n"
            "Content-Length: 173\r\n"
            "Content-Type: multipart/form-data; boundary=-----------------------FR7ODbhRMIR3XblaZ\r\n"
            "\r\n"
            "-----------------------FR7ODbhRMIR3XblaZ\r\n"
            "Content-Disposition: form-data; name=\"k1\"\r\n"
            "\r\n"
            "-----------------------Tr8hHQ2MZKozcfPSt\r\n"
            "-----------------------FR7ODbhRMIR3XblaZ--\r\n";
        Request::Form form(Request::EncType::MULTIPART);
        form.add("k1", "-----------------------Tr8hHQ2MZKozcfPSt");
        auto req = Request::Builder().form(std::move(form)).build();
        auto data = std::string(req->to_string());

        std::regex re("-----------------------Tr8hHQ2MZKozcfPSt");
        std::sregex_iterator begin(data.begin(), data.end(), re);
        std::sregex_iterator end;
        auto count = std::distance(begin, end);
        CHECK(count == 1);

        CHECK(req->to_string() == sample);
    }
}

TEST("application/x-www-form-urlencoded") {
    Request::Form form(Request::EncType::URLENCODED);
    form.add("k1", "v11");
    form.add("k1", "v12");
    form.add("k2", "v2");

    SECTION("enrich query") {
        auto req = Request::Builder()
                .method(Request::Method::POST)
                .uri("/path?k3=v3&k4=v4")
                .form(std::move(form)).build();
        CHECK(req->to_string() ==
            "POST /path?k1=v11&k1=v12&k2=v2&k3=v3&k4=v4 HTTP/1.1\r\n"
             "Content-Length: 0\r\n"
            "\r\n"
        );
    }

    SECTION("empty uri case") {
        auto req = Request::Builder()
                .form(std::move(form)).build();
        CHECK(req->to_string() ==
            "GET /?k1=v11&k1=v12&k2=v2 HTTP/1.1\r\n"
            "\r\n"
        );
    }
}
