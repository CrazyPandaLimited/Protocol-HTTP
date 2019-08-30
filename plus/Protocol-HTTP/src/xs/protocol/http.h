#pragma once

#include <xs.h>
#include <xs/uri.h>
#include <panda/protocol/http/Request.h>
#include <panda/protocol/http/Response.h>
#include <panda/protocol/http/RequestParser.h>
#include <panda/string.h>

namespace xs {

namespace protocol {
namespace http {
    using panda::string;
    using panda::string_view;

    void http_packet_set_headers (panda::protocol::http::Message* p, const Hash& headers);
    void http_packet_set_body    (panda::protocol::http::Message* p, const Simple& body);

    template <class T>
    Simple strings_to_sv (const T& v) {
        size_t len = 0;
        for (const string& s : v) len += s.length();
        if (!len) return Simple::undef;

        auto ret = Simple::create(len);
        char* dest = ret.get<char*>();
        for (const string& s : v) {
            memcpy(dest, s.data(), s.length());
            dest += s.length();
        }
        *dest = 0;
        ret.length(len);
        return ret;
    }

    Simple strings_to_sv (const string& s1, const string& s2);
}}

template <class TYPE>
struct Typemap<panda::protocol::http::Message*, TYPE> : TypemapObject<panda::protocol::http::Message*, TYPE, ObjectTypeRefcntPtr, ObjectStorageMG> {};

template <class TYPE>
struct Typemap<panda::protocol::http::Request*, TYPE> : Typemap<panda::protocol::http::Message*, TYPE> {};

template <class TYPE>
struct Typemap<panda::protocol::http::Response*, TYPE> : Typemap<panda::protocol::http::Message*, TYPE> {
    static std::string package () { return "Protocol::HTTP::Response"; }
};

template <class TYPE>
struct Typemap<panda::protocol::http::ResponseSP, panda::iptr<TYPE>> : Typemap<TYPE*> {
    using Super = Typemap<TYPE*>;
    static panda::iptr<TYPE> in (Sv arg) {
        if (!arg.defined()) return {};
        if (!arg.is_object_ref()) arg = Super::default_stash().call("new", arg);
        return Super::in(arg);
    }
};

template <class TYPE>
struct Typemap<panda::protocol::http::RequestParser*, TYPE> : TypemapObject<panda::protocol::http::RequestParser*, TYPE, ObjectTypeRefcntPtr, ObjectStorageMG> {};

}
