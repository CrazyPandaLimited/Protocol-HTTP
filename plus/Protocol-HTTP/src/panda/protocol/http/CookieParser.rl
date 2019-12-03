#include "Request.h"
#include "Response.h"

%%{
    machine http_cookie_parser;
    
    action mark {
        mark = fpc - ps;
    }

    action req_cookie_name {
        string v;
        SAVE(v);
        request->cookies.add(v, {});
    }
    
    action req_cookie_value {
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }

    action res_cookie_name {
        string v;
        SAVE(v);
        response->cookies.add(v, {});
    }

    action res_cookie_value {
        auto& v = response->cookies.fields.back().value._value;
        SAVE(v);
    }

    action res_cookie_domain {
        auto& v = response->cookies.fields.back().value._domain;
        SAVE(v);
    }

    action res_cookie_path {
        auto& v = response->cookies.fields.back().value._path;
        SAVE(v);
    }
    
    action res_cookie_max_age_start {
        auto& v = response->cookies.fields.back().value._max_age;
        v = 0;
    }
    
    action res_cookie_max_age_digit {
        auto& v = response->cookies.fields.back().value._max_age;
        ADD_DIGIT(v);
    }
    
    action res_cookie_expires {
        auto& v = response->cookies.fields.back().value._expires;
        SAVE(v);
    }
    
    action res_cookie_secure {
        response->cookies.fields.back().value._secure = true;
    }
    
    action res_cookie_http_only {
        response->cookies.fields.back().value._http_only = true;
    }
    
    action res_cookie_same_site_strict {
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Strict;
    }

    action res_cookie_same_site_lax {
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Lax;
    }

    action res_cookie_same_site_none {
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::None;
    }

    ################################## ALPHABETS ########################################
    CRLF          = "\r\n";
    CTL           = cntrl | 127;
    SP            = ' ';
    HTAB          = '\t';
    WSP           = SP | HTAB;
    OWS           = WSP*; # optional whitespace
    VCHAR         = 0x21..0x7e; # visible characters (no whitespace)
    obs_text      = 0x80..0xFF;
    obs_fold      = CRLF WSP+; # obsolete line folding
    tchar         = alnum | "!" | "#" | "$" | "%" | "&" | "'" | "*" | "+" | "-" | "." | "^" | "_" | "`" | "|" | "~"; #any VCHAR, except delimiters
    token         = tchar+;
     
    ################################## COOKIES ########################################
    cookie_octet      = any - (CTL | WSP | '"' | ',' | ';' | '\\');
    cookie_value      = cookie_octet* | ('"' cookie_octet* '"');
    cookie_pair       = token >mark %req_cookie_name  "=" cookie_value >mark %req_cookie_value;
    set_cookie_pair   = token >mark %res_cookie_name  "=" cookie_value >mark %res_cookie_value;
    cookie_header     := cookie_pair ("; " cookie_pair)* OWS;
    expires_av        = "Expires=" (alnum | SP | ":" | ",")* >mark %res_cookie_expires; # RFC 1123, will be lazy-parsed later by panda::date framework
    max_age_av        = "Max-Age=" ([1-9] digit*) >res_cookie_max_age_start $res_cookie_max_age_digit;
    domain_av         = "Domain=" (alnum | "." | "-")+  >mark %res_cookie_domain;
    path_av           = "Path=" ((any - CTL) - ";")+  >mark %res_cookie_path;
    secure_av         = "Secure"  %res_cookie_secure;
    httponly_av       = "HttpOnly"  %res_cookie_http_only;
    samesite_av       = ("SameSite" %res_cookie_same_site_strict) | "SameSite=" (("Strict" %res_cookie_same_site_strict) | ("Lax" %res_cookie_same_site_lax) | ("None" %res_cookie_same_site_none));
    extension_av      = ((any - CTL) - ";")+;
    cookie_av         = expires_av | max_age_av | domain_av | path_av | secure_av | httponly_av | samesite_av | extension_av;
    set_cookie_header := set_cookie_pair ("; " cookie_av)*;

}%%

namespace panda { namespace protocol { namespace http {

%% write data;

#ifndef PARSER_CONSTANTS

#define ADD_DIGIT(dest) \
    dest *= 10;         \
    dest += *p - '0';
    
#define SAVE(dest) dest = buffer.substr(mark, p - ps - mark);

void Request::parse_cookie (const string& buffer) {
    const char* ps = buffer.data();
    const char* p  = ps;
    const char* pe = ps + buffer.size();
    const char* eof = pe;
    Request* request = this;
    Response* response;
    size_t mark;
    int cs = http_cookie_parser_en_cookie_header;
    %% write exec;
}

void Response::parse_set_cookie (const string& buffer) {
    const char* ps = buffer.data();
    const char* p  = ps;
    const char* pe = ps + buffer.size();
    const char* eof = pe;
    Response* response = this;
    Request* request;
    size_t mark;
    int cs = http_cookie_parser_en_set_cookie_header;
    %% write exec;
}

#endif

}}}
