#pragma once
#include "Body.h"
#include "Error.h"
#include "Headers.h"
#include "compression/Compression.h"
#include <array>
#include <panda/refcnt.h>

namespace panda { namespace protocol { namespace http {

enum class State {headers, body, chunk, chunk_body, chunk_trailer, done, error};

struct Message : virtual Refcnt {
    template <class, class> struct Builder;

    Headers headers;
    Body    body;
    bool    chunked      = false;
    int     http_version = 0;

    compression::Compression compressed = compression::IDENTITY;

    Message () {}

    Message (Headers&& headers, Body&& body, bool chunked = false, int http_version = 0) :
        headers(std::move(headers)), body(std::move(body)), chunked(chunked), http_version(http_version)
    {}

    bool keep_alive () const;
    void keep_alive (bool val) { val ? headers.connection("keep-alive") : headers.connection("close"); }

    std::array<string, 3> make_chunk (const string& s) {
        if (!s) return {"", "", ""};
        return {string::from_number(s.length(), 16) + "\r\n", s, "\r\n"};
    }

    string final_chunk () { return "0\r\n\r\n"; }

protected:
    inline void _compile_prepare () {
        if (chunked) {
            http_version = 11;
            // need set(), not add(), otherwise multiple to_string/to_vector calls would result in multiple TEnc headers
            headers.set("Transfer-Encoding", "chunked");
        }
        // content-length logic is in request/response because it slightly differs
    }

    template <class T>
    inline std::vector<string> _to_vector (const T& f) {
        _compile_prepare();
        auto hdr = f();
        if (!body.length()) return {hdr};
        auto sz = body.parts.size();

        std::vector<string> result;
        if (chunked) {
            result.reserve(1 + sz * 3 + 1);
            result.emplace_back(hdr);
            for (auto& part : body.parts) {
                if (!part) continue;
                auto ss = make_chunk(part);
                for (auto& s : ss) result.emplace_back(s);
            }
            result.emplace_back(final_chunk());
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
        auto blen = body.length();
        if (chunked && blen) blen += body.parts.size() * 8 + 5;
        auto ret = f(blen);
        if (!blen) return ret;

        if (chunked) {
            for (auto& part : body.parts) {
                auto ss = make_chunk(part);
                for (auto& s : ss) ret += s;
            }
            ret += final_chunk();
        }
        else for (auto& part : body.parts) ret += part;

        return ret;
    }

private:
    //friend struct Parser; friend struct RequestParser; friend struct ResponseParser;
};
using MessageSP = iptr<Message>;

template <class T, class MP>
struct Message::Builder {
    T& headers (Headers&& headers) {
        _message->headers = std::move(headers);
        return self();
    }

    T& header (const string& k, const string& v) {
        _message->headers.add(k, v);
        return self();
    }

    T& body (Body&& val, const string& content_type = "") {
        _message->body = std::move(val);
        if (content_type) _message->headers.add("Content-Type", content_type);
        return self();
    }

    T& body (const string& body, const string& content_type = "") {
        _message->body = body;
        if (content_type) _message->headers.add("Content-Type", content_type);
        return self();
    }

    T& http_version (int http_version) {
        _message->http_version = http_version;
        return self();
    }

    T& chunked (const string& content_type = "") {
        _message->chunked = true;
        if (content_type) _message->headers.add("Content-Type", content_type);
        return self();
    }

    MP build () { return _message; }

protected:
    MP _message;

    Builder (const MP& msg) : _message(msg) {}

    T& self () { return static_cast<T&>(*this); }
};

}}}
