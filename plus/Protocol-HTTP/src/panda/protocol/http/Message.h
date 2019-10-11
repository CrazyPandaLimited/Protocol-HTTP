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

    std::array<string, 3> make_chunk (const string& s) { return {string::from_number(s.length(), 16) + "\r\n", s, "\r\n"}; }

    string end_chunk () { return "0\r\n\r\n"; }

    size_t buf_size () const {return _buf_size;}

protected:
    template <class T> friend struct MessageParser;

    size_t _buf_size;

    void add_header_field (const string& key, const string& value);
    void add_body_part    (const string& body_part);

    size_t body_length () {
        auto l = body.length();
        if (!chunked || !l) return l;
        return l + body.parts.size() * 8 + 5;
    }

    inline void _compile_prepare () {
        if (chunked) {
            http_version = "1.1";
            headers.add_field("Transfer-Encoding", "chunked");
        }
        else {
            auto blen = body.length();
            if (blen) {
                headers.add_field("Content-Length", panda::to_string(blen));
                //if (!headers.has_field("Content-Type")) headers.add_field("Content-Type", "text/plain");
            }
        }
    }

    template <class T>
    inline std::vector<string> _to_vector (const T& f) {
        _compile_prepare();
        auto hdr = f();
        auto sz = body.parts.size();
        if (!sz) return {hdr};

        std::vector<string> result;
        if (chunked) {
            result.reserve(1 + sz * 3 + 1);
            result.emplace_back(hdr);
            for (auto& part : body.parts) {
                auto ss = make_chunk(part);
                for (auto& s : ss) result.emplace_back(s);
            }
            result.emplace_back(end_chunk());
        } else {
            result.reserve(1 + sz);
            result.emplace_back(hdr);
            for (auto& part : body.parts) result.emplace_back(part);
        }

        return result;
    }

    template <class T>
    inline string _to_string (const T& f) {
        _compile_prepare();
        auto blen = body_length();
        auto ret = f(blen);
        if (!blen) return ret;

        if (chunked) {
            for (auto& part : body.parts) {
                auto ss = make_chunk(part);
                for (auto& s : ss) ret += s;
            }
            ret += end_chunk();
        }
        else for (auto& part : body.parts) ret += part;

        return ret;
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

}}}
