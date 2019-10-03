#pragma once
#include "Body.h"
#include "Header.h"
#include <panda/refcnt.h>

namespace panda { namespace protocol { namespace http {

struct Message : virtual Refcnt {
    template <class T> struct Builder;

    Header headers;
    Body   body;
    string http_version;
    bool   chunked;

    Message ();
    Message (Header&& header, Body&& body, const string& http_version, bool chunked);

    void add_header_field (const string& key, const string& value);
    void add_body_part    (const string& body_part);

    bool keep_alive () const;
    void keep_alive (bool val) { val ? headers.connection("keep-alive") : headers.connection("close"); }

    bool has_headers () const { return !headers.empty(); }
    bool has_body    () const { return !body.empty(); }

    size_t buf_size () const {return _buf_size;}

    virtual std::vector<string> to_vector () const = 0;
    virtual string              to_string () const = 0;

protected:
    size_t _buf_size; // only for parser inner limits

    void prepare_tostr () {
        if (!http_version) http_version = "1.1";
        auto blen = body.length();
        if (blen) {
            headers.add_field("Content-Length", panda::to_string(blen));
            if (!headers.has_field("Content-Type")) headers.add_field("Content-Type", "text/plain");
        }
        else if (chunked) {
            headers.add_field("Transfer-Encoding", "chunked");
        }
    }
};

template <class T>
struct Message::Builder {
    T& headers (Header&& headers) {
        _headers = std::move(headers);
        return self();
    }

    T& body (Body&& val, const string& content_type = "") {
        _body = std::move(val);
        if (content_type) _headers.add_field("Content-Type", content_type);
        return self();
    }

    T& body (const string& body, const string& content_type = "") {
        _body = body;
        if (content_type) _headers.add_field("Content-Type", content_type);
        return self();
    }

    T& version (const string& http_version) {
        _http_version = http_version;
        return self();
    }

    T& chunked (const string& content_type = "") {
        _chunked = true;
        if (content_type) _headers.add_field("Content-Type", content_type);
        return self();
    }

protected:
    Header _headers;
    Body   _body;
    string _http_version;
    string _content_type;
    bool   _chunked;

    Builder () : _chunked() {}

    T& self () { return static_cast<T&>(*this); }
};

std::ostream& operator<< (std::ostream&, const Message&);

}}}
