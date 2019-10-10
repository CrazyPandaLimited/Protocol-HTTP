#pragma once
#include "Body.h"
#include "Header.h"
#include <array>
#include <panda/refcnt.h>

namespace panda { namespace protocol { namespace http {

struct Message : virtual Refcnt {
    template <class T> struct Builder;

    enum class State {not_yet, got_header, in_body, done, error};

    Header headers;
    Body   body;
    string http_version;
    bool   chunked;

    Message () : chunked(), _buf_size() {}
    Message (Header&& header, Body&& body, const string& http_version, bool chunked);

    bool keep_alive () const;
    void keep_alive (bool val) { val ? headers.connection("keep-alive") : headers.connection("close"); }

    std::array<string, 3> make_chunk (const string& str) { return {string::from_number(buf.length(), 16) + "\r\n", str, "\r\n"}; }

    string end_chunk () { return "0\r\n\r\n"; }

    size_t buf_size () const {return _buf_size;}

protected:
    size_t _buf_size;

    void add_header_field (const string& key, const string& value);
    void add_body_part    (const string& body_part);

    size_t body_length () {
        auto l = body.length();
        if (!chunked || !l) return l;
        return l + body.size() * 8 + 5;
    }

    void prepare_tostr () {
        if (chunked) {
            http_version = "1.1";
            headers.add_field("Transfer-Encoding", "chunked");
        }
        else {
            auto blen = body.length();
            if (blen) {
                headers.add_field("Content-Length", panda::to_string(blen));
                if (!headers.has_field("Content-Type")) headers.add_field("Content-Type", "text/plain");
            }
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
