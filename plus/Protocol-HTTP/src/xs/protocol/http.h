#pragma once
#include <xs.h>
#include <panda/protocol/http/RequestParser.h>
#include <panda/protocol/http/ResponseParser.h>

namespace xs { namespace protocol { namespace http {
    using namespace panda::protocol::http;

    RequestSP  make_request  (const Hash&, const RequestSP& = {});
    ResponseSP make_response (const Hash&, const ResponseSP& = {});

    void set_headers (Message* p, const Hash& headers);
    void set_method  (Request* req, const Sv& method);

    Simple strings_to_sv (const std::vector<panda::string>&);
}}}

namespace xs {

template <class TYPE>
struct Typemap<panda::protocol::http::Message*, TYPE> : TypemapObject<panda::protocol::http::Message*, TYPE, ObjectTypeRefcntPtr, ObjectStorageMG> {};

template <class TYPE>
struct Typemap<panda::protocol::http::Request*, TYPE> : Typemap<panda::protocol::http::Message*, TYPE> {
    static panda::string_view package () { return "Protocol::HTTP::Request"; }
};

template <class TYPE>
struct Typemap<panda::protocol::http::RequestSP, panda::iptr<TYPE>> : Typemap<TYPE*> {
    using Super = Typemap<TYPE*>;
    static panda::iptr<TYPE> in (Sv arg) {
        if (arg.is_hash_ref()) return xs::protocol::http::make_request(arg, new TYPE());
        return Super::in(arg);
    }
};

template <class TYPE>
struct Typemap<panda::protocol::http::Response*, TYPE> : Typemap<panda::protocol::http::Message*, TYPE> {
    static panda::string_view package () { return "Protocol::HTTP::Response"; }
};

template <class TYPE>
struct Typemap<panda::protocol::http::ResponseSP, panda::iptr<TYPE>> : Typemap<TYPE*> {
    using Super = Typemap<TYPE*>;
    static panda::iptr<TYPE> in (Sv arg) {
        if (arg.is_hash_ref()) return xs::protocol::http::make_response(arg, new TYPE());
        return Super::in(arg);
    }
};

template <class TYPE>
struct Typemap<panda::protocol::http::RequestParser*, TYPE> : TypemapObject<panda::protocol::http::RequestParser*, TYPE, ObjectTypePtr, ObjectStorageMG> {
    static std::string package () { return "Protocol::HTTP::RequestParser"; }
};

template <class TYPE>
struct Typemap<panda::protocol::http::ResponseParser*, TYPE> : TypemapObject<panda::protocol::http::ResponseParser*, TYPE, ObjectTypePtr, ObjectStorageMG> {
    static std::string package () { return "Protocol::HTTP::ResponseParser"; }
};

}
