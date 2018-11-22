#pragma once

#include <vector>

#include <panda/refcnt.h>
#include <panda/string.h>

#include "Defines.h"
#include "HeaderField.h"

namespace panda { namespace protocol { namespace http {

static int const DEFAULT_FIELDS_RESERVE = 20;

struct Header : virtual Refcnt {
    friend std::ostream& operator<<(std::ostream& os, const HeaderField& hf);

    virtual ~Header();

    Header();

    Header(const std::vector<HeaderField>& fields);

    struct Builder {
        Builder& connection_close() {
            fields.emplace_back("Connection", "close");
            return *this;
        }
        
        Builder& date(const string& date) {
            fields.emplace_back("Date", date);
            return *this;
        }
        
        Builder& host(const string& host) {
            fields.emplace_back("Host", host);
            return *this;
        }
        
        Builder& location(const string& location) {
            fields.emplace_back("Location", location);
            return *this;
        }
        
        Builder& chunked() {
            fields.emplace_back("Transfer-Encoding", "chunked");
            return *this;
        }
        
        Builder& add_field(const string& name, const string& value) {
            fields.emplace_back(name, value);
            return *this;
        }

        HeaderSP build() {
            return make_iptr<Header>(fields);
        }

    protected:
        std::vector<HeaderField> fields;
    };
    
    bool has_field(const string& key) const;

    string get_field(const string& key) const;
    
    void add_field(const string& key, const string& value);
    
    void set_field(const string& key, const string& value);

    bool empty() const {
        return fields.empty();
    }

    std::vector<HeaderField> fields;
};

inline
std::ostream& operator<<(std::ostream& os, const Header& h) {
    for(auto field : h.fields) {
        os << field << "\r\n";
    }
    return os;  
} 

inline
std::ostream& operator<<(std::ostream& os, const HeaderSP& ptr) {
    if(ptr) {
        os << *ptr;
    }
    return os;
}

}}} // namespace panda::protocol::http
