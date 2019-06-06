#pragma once

#include <panda/refcnt.h>
#include <panda/uri/URI.h>

namespace panda { namespace protocol { namespace http {

using URISP = iptr<uri::URI>;

class Response;
using ResponseSP = iptr<Response>;

class Request;
using RequestSP = iptr<Request>;

class RequestFactory;
using RequestFactorySP = iptr<RequestFactory>;

class ResponseParser;
using ResponseParserSP = iptr<ResponseParser>;

class RequestParser;
using RequestParserSP = iptr<RequestParser>;

struct Header;
//using HeaderSP = iptr<Header>;

struct Body;
using BodySP = iptr<Body>;

struct Message;
using MessageSP = iptr<Message>;

}}} // namespace panda::protocol::http
