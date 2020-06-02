#include "../lib/test.h"

#define TEST(name) TEST_CASE("compile-form: " name, "[compile-form]")

TEST("simple form") {
    std::srand(123); // make boundary generator deterministic
    Request::Form form;
    form.add("k1", "v1");
    form.add("k2", "v2");

    auto req = Request::Builder().form(std::move(form)).build();
    auto data = req->to_string();
    string str =
        "POST / HTTP/1.1\r\n"
        "Content-Length: 226\r\n"
        "Content-Type: multipart/form-data; boundary=------------------------Vs0hJS3LYKozagRS\r\n"
        "\r\n"
        "------------------------Vs0hJS3LYKozagRS\r\n"
        "Content-Disposition: form-data; name=\"k1\"\r\n"
        "\r\n"
        "v1\r\n"
        "------------------------Vs0hJS3LYKozagRS\r\n"
        "Content-Disposition: form-data; name=\"k2\"\r\n"
        "\r\n"
        "v2\r\n"
        "------------------------Vs0hJS3LYKozagRS--\r\n";
    auto d = std::mismatch(data.begin(), data.end(), str.begin());

    CHECK(data == str);
}

