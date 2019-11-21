#include "RequestParser.h"

namespace panda { namespace protocol { namespace http {

RequestParser::RequestParser (IFactory* fac) : factory(fac) {
    reset();
}

void RequestParser::reset () {
    Parser::reset();
    cs = http_parser_en_request;
    auto req = new_request();
    request = req;
    message = std::move(req);
}

RequestParser::Result RequestParser::parse (const string& buffer) {
    auto pos = Parser::parse(buffer,
        []{ return true; },
        [this] {
            request->state(State::done);
            return false;
        }
    );
    Result ret = {request, pos};
    if (request->state() == State::done || request->error()) reset();
    return ret;
}

}}}
