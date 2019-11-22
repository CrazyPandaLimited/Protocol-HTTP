#include "RequestParser.h"
#include "Parser.tcc"

namespace panda { namespace protocol { namespace http {

RequestParser::RequestParser (IFactory* fac) : factory(fac) {
    reset();
}

void RequestParser::reset () {
    Parser::reset();
    cs = http_parser_en_request;
}

RequestParser::Result RequestParser::parse (const string& buffer) {
    if (!request) {
        request = new_request();
        message = request;
    }

    auto pos = Parser::parse(buffer,
        []{ return true; },
        [this] {
            request->state(State::done);
            return false;
        }
    );
    Result ret = {request, pos};
    if (request->state() >= State::done) reset();
    return ret;
}

}}}
