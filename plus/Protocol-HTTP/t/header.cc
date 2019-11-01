#include "lib/test.h"

#define TEST(name) TEST_CASE("header: " name, "[header]")

TEST("case insensitive") {
    Header h;
    h.add("Aa", "value");
    CHECK(h.get("AA") == "value");
}

TEST("basic") {
    Header h;
    CHECK(h.length() == 0);
    CHECK(h.get("Content-Length", "default") == "default");

    h.add("field1", "value1");
    CHECK(h.get("field1", "default") == "value1");


    WARN(h);
    h.set("field1", "value2");
    CHECK(h.get("field1", "default") == "value2");

    h.set("field2", "value2");
    CHECK(h.get("field2", "default") == "value2");
}
