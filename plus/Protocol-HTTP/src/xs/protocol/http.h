#pragma once

#include <xs.h>
#include <panda/protocol/http/Request.h>
#include <panda/protocol/http/Response.h>

namespace xs {


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
    static panda::iptr<TYPE> in (pTHX_ Sv arg) {
        if (!arg.defined()) return {};
        Object obj = arg.is_object_ref() ? Object(std::move(arg)) : Super::default_stash().call("new", arg);
        return Super::in(aTHX_ obj);
    }
};

}
