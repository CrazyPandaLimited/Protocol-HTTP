#pragma once

#include <vector>
#include <iostream>

#include <panda/refcnt.h>
#include <panda/string.h>

#include "Body.h"
#include "Header.h"

namespace panda { namespace protocol { namespace http {

struct Message : virtual Refcnt {
    friend std::ostream& operator<<(std::ostream& os, const Message& message);

    Message();

    Message(Header&& header, BodySP body, const string& http_version);

    Header headers;
    BodySP body;

    void add_header_field(const string& key, const string& value);

    void add_body_part(const string& body_part);

    bool is_valid() const;

    void set_valid();

    bool has_header() const;

    void set_header();

    bool has_body() const;

    void set_body();

    string http_version() const {
        return http_version_;
    }

    void http_version(const string& http_version) {
        http_version_ = http_version;
    }

    virtual std::ostream& print(std::ostream& os) const;

    size_t buf_size() const {return _buf_size;}

protected:
    bool is_valid_;
    string http_version_;
    bool has_header_;
    bool has_body_;
    size_t _buf_size; // only for parser inner limits
};

}}} // namespace panda::protocol::http
