#include "../lib/test.h"

const std::string TEST_DIR = TEST_ROOT + "test-fragmented-response";

TEST_CASE("parsing response byte by byte", "[fragmented]") {
    http::ResponseParser response_parser;
    http::RequestSP request = new http::Request(http::Request::Method::GET, new uri::URI("http://dev/"), http::Header(), new http::Body, "1.1");
    response_parser.append_request(request);
    http::ResponseSP response = response_parser.message();

    const size_t CHUNK = GENERATE(1, 10);
    char file_buffer[CHUNK];
    for(auto file_name : read_directory(TEST_DIR)) {
        REQUIRE(!response->is_valid());

        std::ifstream file(TEST_DIR+"/"+file_name, std::ios::binary);

        while (!file.eof()) {
            file.read(file_buffer, CHUNK);
            std::streamsize dataSize = file.gcount();
            if (dataSize == 0) break; // TODO: should work without this
            string str(file_buffer, dataSize);
            response = response_parser.parse_first(str).response;
        }

    }

    _DBG(response);

    REQUIRE(response);
    REQUIRE(response->is_valid());
    REQUIRE(response->http_version() == "1.1");

    CHECK(response->code == 101);
    CHECK(response->full_message() == "101 Switching Protocols");
    CHECK(response->headers.get_field("Upgrade") == "websocket");
    CHECK(response->headers.get_field("Connection") == "Upgrade");
    CHECK(response->headers.get_field("Sec-WebSocket-Extensions") == "permessage-deflate; client_max_window_bits=15");
}
