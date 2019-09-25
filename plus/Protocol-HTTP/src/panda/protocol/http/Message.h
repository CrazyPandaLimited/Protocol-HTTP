#pragma once
#include "Body.h"
#include "Header.h"

namespace panda { namespace protocol { namespace http {

struct Message : virtual Refcnt {
    Message ();
    Message (Header&& header, const BodySP& body, const string& http_version);

    Header headers;
    BodySP body;

    void add_header_field (const string& key, const string& value);
    void add_body_part    (const string& body_part);

    bool is_valid  () const { return is_valid_; }
    void set_valid ()       { is_valid_ = true; }

    bool has_header () const { return has_header_; }
    void set_header ()       { has_header_ = true; }

    bool has_body () const { return has_body_; }
    void set_body ()       { has_body_ = true; }

    string http_version () const { return http_version_; }

    void http_version (const string& http_version) { http_version_ = http_version; }

    size_t buf_size () const {return _buf_size;}

    virtual std::ostream& print (std::ostream& os) const;

protected:
    bool   is_valid_;
    string http_version_;
    bool   has_header_;
    bool   has_body_;
    size_t _buf_size; // only for parser inner limits
};

std::ostream& operator<< (std::ostream&, const Message&);

}}}
