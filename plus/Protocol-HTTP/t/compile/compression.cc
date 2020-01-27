#include "../lib/test.h"

#define TEST(name) TEST_CASE("compile-compression: " name, "[compile-compression]")

TEST("Accept-Encoding") {
    SECTION("identity") {
        auto req = Request::Builder().allow_compression(compression::IDENTITY).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n\r\n");
        CHECK(req->compression_mask() == compression::IDENTITY);
    }

    SECTION("identity, identity") {
        auto req = Request::Builder()
                .allow_compression(compression::IDENTITY)
                .allow_compression(compression::IDENTITY)
            .build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n\r\n");
        CHECK(req->compression_mask() == compression::IDENTITY);
    }

    SECTION("(empty aka default)") {
        auto req = Request::Builder().build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n\r\n");
        CHECK((req->compression_mask() & compression::IDENTITY));
    }

    SECTION("gzip") {
        auto req = Request::Builder().allow_compression(compression::GZIP).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: gzip\r\n"
        "\r\n");
        CHECK((req->compression_mask() & compression::GZIP));
        CHECK((req->compression_mask() & compression::IDENTITY));
    }

    SECTION("deflate") {
        auto req = Request::Builder().allow_compression(compression::DEFLATE).build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: deflate\r\n"
        "\r\n");
        CHECK((req->compression_mask() & compression::DEFLATE));
        CHECK((req->compression_mask() & compression::IDENTITY));
    }

    SECTION("deflate, gzip") {
        auto req = Request::Builder()
                .allow_compression(compression::DEFLATE)
                .allow_compression(compression::GZIP)
            .build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: deflate, gzip\r\n"
        "\r\n");
        CHECK((req->compression_mask() & compression::GZIP));
        CHECK((req->compression_mask() & compression::DEFLATE));
        CHECK((req->compression_mask() & compression::IDENTITY));
    }

    SECTION("deflate, gzip, gzip, gzip, gzip, gzip, gzip, gzip, gzip, identity") {
        auto req = Request::Builder()
                .allow_compression(compression::DEFLATE)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::GZIP)
                .allow_compression(compression::IDENTITY)
            .build();
        CHECK(req->to_string() == "GET / HTTP/1.1\r\n"
            "Accept-Encoding: deflate, gzip, gzip, gzip, gzip, gzip, gzip\r\n"
        "\r\n");
    }
}

TEST("gzip compression") {
    SECTION("small body") {
        auto req = Request::Builder()
            .method(Method::POST)
            .uri("http://crazypanda.ru/hello/world")
            .body("my body")
            .compress(compression::GZIP)
            .build();

        auto data = req->to_string();
        REQUIRE_THAT(data, StartsWith(
            "POST /hello/world HTTP/1.1\r\n"
            "Content-Length: 27\r\n"
            "Host: crazypanda.ru\r\n"
            "Content-Encoding: gzip\r\n"
            "\r\n"
        ));
        CHECK(req->body.to_string() == "my body");

        SECTION("to_vector") {
            auto vec = req->to_vector();
            string buff;
            for(auto& it:vec) { buff += it; }
            CHECK(buff == req->to_string());
        }

        RequestParser p;
        auto result = p.parse(data);
        CHECK(result.state == State::done);
        CHECK(result.error.value() == 0);
        CHECK(req->compressed == compression::GZIP);
        REQUIRE(req->body.to_string() == "my body");
    }

    SECTION("average body") {
        const char * body_raw = R"END(
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse vel eros sit amet ex gravida tempor sit amet sit amet nisi. Sed ultrices, enim mattis sagittis tincidunt, tortor quam fermentum lectus, vitae mattis felis diam quis lorem. Suspendisse facilisis lorem dui, porta consectetur velit consectetur ac. Maecenas libero justo, porta in finibus vitae, blandit sed felis. Donec aliquam, leo eget ultrices tincidunt, purus ante ornare ipsum, sit amet auctor nunc ligula id nisi. Praesent sit amet sapien eget orci porta accumsan. Ut sed tortor ligula. Aliquam odio dolor, volutpat vitae elit eget, aliquet accumsan nisl. In ac placerat ligula.

In eu ultrices turpis, in porta risus. Sed erat dui, euismod in pellentesque in, auctor sit amet erat. Fusce consectetur fermentum neque, vel viverra mauris finibus efficitur. Donec blandit accumsan lacus sit amet viverra. In leo erat, mollis et laoreet eu, vulputate id odio. Suspendisse elementum blandit malesuada. Mauris in tellus lobortis, ullamcorper nulla at, elementum ligula. Vestibulum congue consequat tellus vel gravida. Nam in pharetra tortor, vel tempor tellus. Sed ac pulvinar odio, ac convallis augue. Pellentesque tortor dui, eleifend id ante eget, consequat faucibus felis. Nam vitae lacinia tortor. Praesent lacinia quam ac augue pretium, in auctor nunc consectetur. Cras est sapien, commodo quis tincidunt vitae, faucibus eget quam. Praesent placerat enim lectus, vitae cursus erat semper sed.

Fusce quis nulla lacus. Nulla non vulputate diam, eget pulvinar sapien. Vivamus congue tortor ut nulla ultrices, sit amet elementum dolor dignissim. Cras gravida, nisl vel venenatis lacinia, urna magna accumsan turpis, eu porta urna ex vel nulla. Integer ut malesuada ante, quis pulvinar risus. Aenean suscipit gravida ante quis vestibulum. Cras id enim a arcu tristique pretium. Ut euismod ante accumsan tempor sollicitudin. Nunc sed risus bibendum, congue ipsum a, ornare est. Pellentesque vitae est auctor, consectetur nunc at, viverra lectus. Sed nunc leo, ullamcorper eu tortor a, lacinia dapibus est. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Cras dictum vel odio at tempus. Mauris quam ligula, viverra eget semper et, ultricies vitae lectus. Maecenas quis libero nibh.

Duis congue lacus sit amet rutrum mollis. Donec facilisis mollis arcu vitae lobortis. Donec efficitur mi et diam fringilla finibus. Aenean rhoncus volutpat eleifend. Fusce dictum mauris nunc, at rutrum tortor convallis sed. Phasellus id consequat felis. Maecenas tincidunt nibh nisi, sed blandit velit egestas nec. Integer dapibus dolor felis, ac mollis massa mattis non. Curabitur nisi diam, viverra vel magna et, tempor feugiat tortor. Etiam eu nulla id orci posuere egestas nec non tortor.

Nullam quis tempus lectus. Quisque purus est, venenatis at auctor a, laoreet in purus. Ut convallis, odio eget ullamcorper sollicitudin, nunc felis consectetur erat, ac varius neque diam in magna. Aenean quis orci eu urna blandit laoreet. Pellentesque ultricies metus dui, a luctus justo dignissim a. Suspendisse interdum hendrerit facilisis. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aenean facilisis viverra tortor, et malesuada nisl hendrerit vitae. Duis magna ipsum, mattis in feugiat vitae, tristique eget elit. Vivamus quis arcu felis. Praesent et nunc quis dui dictum laoreet. Praesent auctor urna sit amet quam pulvinar fringilla. Integer in elit maximus, mollis neque a, tempor metus. Donec sodales sapien ut lorem tristique, tristique ultricies arcu porta. Morbi mi nisl, efficitur et fermentum vel, aliquam ac erat.
)END";
        string body_sample(body_raw);
        auto req = Request::Builder()
            .method(Method::POST)
            .uri("http://crazypanda.ru/hello/world")
            .body(body_sample)
            .compress(compression::GZIP, compression::Level::optimal)
            .build();

        auto data = req->to_string();
        REQUIRE_THAT(data, StartsWith(
            "POST /hello/world HTTP/1.1\r\n"
            "Content-Length: 1483\r\n"
            "Host: crazypanda.ru\r\n"
            "Content-Encoding: gzip\r\n"
            "\r\n"
        ));
        CHECK(req->body.to_string() == body_sample);
        RequestParser p;
        auto result = p.parse(data);
        CHECK(result.state == State::done);
        CHECK(result.error.value() == 0);
        CHECK(req->compressed == compression::GZIP);
        REQUIRE(req->body.to_string() == body_sample);
    }

    SECTION("chunked & gzipped") {
        const char * body_raw[] = {
"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse vel eros sit amet ex gravida tempor sit amet sit amet nisi. Sed ultrices, enim mattis sagittis tincidunt, tortor quam fermentum lectus, vitae mattis felis diam quis lorem. Suspendisse facilisis lorem dui, porta consectetur velit consectetur ac. Maecenas libero justo, porta in finibus vitae, blandit sed felis. Donec aliquam, leo eget ultrices tincidunt, purus ante ornare ipsum, sit amet auctor nunc ligula id nisi. Praesent sit amet sapien eget orci porta accumsan. Ut sed tortor ligula. Aliquam odio dolor, volutpat vitae elit eget, aliquet accumsan nisl. In ac placerat ligula.",
"In eu ultrices turpis, in porta risus. Sed erat dui, euismod in pellentesque in, auctor sit amet erat. Fusce consectetur fermentum neque, vel viverra mauris finibus efficitur. Donec blandit accumsan lacus sit amet viverra. In leo erat, mollis et laoreet eu, vulputate id odio. Suspendisse elementum blandit malesuada. Mauris in tellus lobortis, ullamcorper nulla at, elementum ligula. Vestibulum congue consequat tellus vel gravida. Nam in pharetra tortor, vel tempor tellus. Sed ac pulvinar odio, ac convallis augue. Pellentesque tortor dui, eleifend id ante eget, consequat faucibus felis. Nam vitae lacinia tortor. Praesent lacinia quam ac augue pretium, in auctor nunc consectetur. Cras est sapien, commodo quis tincidunt vitae, faucibus eget quam. Praesent placerat enim lectus, vitae cursus erat semper sed.",
"Fusce quis nulla lacus. Nulla non vulputate diam, eget pulvinar sapien. Vivamus congue tortor ut nulla ultrices, sit amet elementum dolor dignissim. Cras gravida, nisl vel venenatis lacinia, urna magna accumsan turpis, eu porta urna ex vel nulla. Integer ut malesuada ante, quis pulvinar risus. Aenean suscipit gravida ante quis vestibulum. Cras id enim a arcu tristique pretium. Ut euismod ante accumsan tempor sollicitudin. Nunc sed risus bibendum, congue ipsum a, ornare est. Pellentesque vitae est auctor, consectetur nunc at, viverra lectus. Sed nunc leo, ullamcorper eu tortor a, lacinia dapibus est. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Cras dictum vel odio at tempus. Mauris quam ligula, viverra eget semper et, ultricies vitae lectus. Maecenas quis libero nibh.",
"Duis congue lacus sit amet rutrum mollis. Donec facilisis mollis arcu vitae lobortis. Donec efficitur mi et diam fringilla finibus. Aenean rhoncus volutpat eleifend. Fusce dictum mauris nunc, at rutrum tortor convallis sed. Phasellus id consequat felis. Maecenas tincidunt nibh nisi, sed blandit velit egestas nec. Integer dapibus dolor felis, ac mollis massa mattis non. Curabitur nisi diam, viverra vel magna et, tempor feugiat tortor. Etiam eu nulla id orci posuere egestas nec non tortor.",
"Nullam quis tempus lectus. Quisque purus est, venenatis at auctor a, laoreet in purus. Ut convallis, odio eget ullamcorper sollicitudin, nunc felis consectetur erat, ac varius neque diam in magna. Aenean quis orci eu urna blandit laoreet. Pellentesque ultricies metus dui, a luctus justo dignissim a. Suspendisse interdum hendrerit facilisis. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aenean facilisis viverra tortor, et malesuada nisl hendrerit vitae. Duis magna ipsum, mattis in feugiat vitae, tristique eget elit. Vivamus quis arcu felis. Praesent et nunc quis dui dictum laoreet. Praesent auctor urna sit amet quam pulvinar fringilla. Integer in elit maximus, mollis neque a, tempor metus. Donec sodales sapien ut lorem tristique, tristique ultricies arcu porta. Morbi mi nisl, efficitur et fermentum vel, aliquam ac erat.",
};
        Body body;
        string body_concat;
        for(auto& it : body_raw) { body.parts.push_back(string(it)); body_concat += string(it); }
        auto req = Request::Builder().method(Method::POST).body(std::move(body)).chunked().compress(compression::GZIP).build();
        auto data = req->to_string();
        REQUIRE_THAT(data, StartsWith(
            "POST / HTTP/1.1\r\n"
            "Transfer-Encoding: chunked\r\n"
            "Content-Encoding: gzip\r\n"
            "\r\n"
        ));
        RequestParser p;
        auto result = p.parse(data);
        CHECK(result.state == State::done);
        CHECK(result.error.value() == 0);
        CHECK(req->compressed == compression::GZIP);
        REQUIRE(req->body.to_string() == body_concat);
    }
}

TEST("ignore compression in response if request didn't support it") {
    auto req = Request::Builder()
        .method(Method::GET)
        .allow_compression(compression::IDENTITY)
        .uri("/")
        .build();

    auto res = Response::Builder().code(200)
            .body("my body")
            .compress(compression::GZIP)
            .build();

    auto data = res->to_string(req);
    CHECK(data == "HTTP/1.1 200 OK\r\nContent-Length: 7\r\n\r\nmy body");
}

TEST("brotli is ignored if there is no plugin for it") {
    auto req = Request::Builder()
        .method(Method::GET)
        .allow_compression(compression::IDENTITY)
        .allow_compression(compression::BROTLI)
        .uri("/")
        .build();

    auto res = Response::Builder().code(200)
            .body("my body")
            .compress(compression::BROTLI)
            .build();

    auto data = res->to_string(req);
    CHECK(data == "HTTP/1.1 200 OK\r\nContent-Length: 7\r\n\r\nmy body");
}

TEST("is_valid_compression") {
    CHECK(compression::is_valid_compression(1) == true);
    CHECK(compression::is_valid_compression(2) == true);
    CHECK(compression::is_valid_compression(4) == true);
    CHECK(compression::is_valid_compression(8) == true);
    CHECK(compression::is_valid_compression(0) == false);
    CHECK(compression::is_valid_compression(3) == false);
    CHECK(compression::is_valid_compression(5) == false);
    CHECK(compression::is_valid_compression(6) == false);
}
