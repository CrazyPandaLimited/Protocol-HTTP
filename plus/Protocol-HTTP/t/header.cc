#include "lib/test.h"

TEST_CASE("http::Header", "[header]") {
    Header h;
    CHECK(h.length() == 0);
    CHECK(h.get_field("Content-Length", "default") == "default");

    h.add_field("field1", "value1");
    CHECK(h.get_field("field1", "default") == "value1");


    WARN(h);
    h.set_field("field1", "value2");
    CHECK(h.get_field("field1", "default") == "value2");

    h.set_field("field2", "value2");
    CHECK(h.get_field("field2", "default") == "value2");
}
