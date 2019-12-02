#include "Parser.h"

%%{
    machine http_parser;
    
    action mark {
        mark   = fpc - ps;
        marked = true;
    }

    action unmark {
        marked = false;
    }

    action submark {
        submark   = fpc - ps;
        submarked = true;
    }

    action subunmark {
        submarked = false;
    }

    action header_name {
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
    
    action header_value {
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
    
    action content_length_start {
        if (has_content_length) {
            cs = http_parser_error;
            set_error(errc::multiple_content_length);
            fbreak;
        }
        has_content_length = true;
    }
    
    action req_cookie_name {
        string v;
        SUBSAVE(v);
        request->cookies.add(v, {});
    }
    
    action req_cookie_value {
        auto& v = request->cookies.fields.back().value;
        SUBSAVE(v);
    }

    action res_cookie_name {
        string v;
        SUBSAVE(v);
        response->cookies.add(v, {});
    }

    action res_cookie_value {
        auto& v = response->cookies.fields.back().value._value;
        SUBSAVE(v);
    }

    action res_cookie_domain {
        auto& v = response->cookies.fields.back().value._domain;
        SUBSAVE(v);
    }

    action res_cookie_path {
        auto& v = response->cookies.fields.back().value._path;
        SUBSAVE(v);
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
        SUBSAVE(v);
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

    action request_target {
        string target;
        SAVE(target);
        request->uri = new URI(target);
    }
    
    action done {
        fbreak;
    }
    
    action save2 {
        
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
    qdtext        = WSP | 0x21 | 0x23..0x5B | 0x5D..0x7E | obs_text;
    quoted_pair   = "\\" (WSP | VCHAR | obs_text);
    quoted_string = '"' (qdtext | quoted_pair)* '"';
     
    http_version  = "HTTP/1." (("0" %{message->http_version = 10;}) | ("1" %{message->http_version = 11;}));
    
    ################################## COOKIES ########################################
    cookie_octet      = any - (CTL | WSP | '"' | ',' | ';' | '\\');
    cookie_value      = cookie_octet* | ('"' cookie_octet* '"');
    cookie_pair       = token >submark %req_cookie_name %subunmark  "=" cookie_value >submark %req_cookie_value %subunmark;
    set_cookie_pair   = token >submark %res_cookie_name %subunmark  "=" cookie_value >submark %res_cookie_value %subunmark;
    cookie_header     = /Cookie/i ":" OWS cookie_pair ("; " cookie_pair)* OWS;
    expires_av        = "Expires=" (alnum | SP | ":" | ",")* >submark %res_cookie_expires %subunmark; # RFC 1123, will be lazy-parsed later by panda::date framework
    max_age_av        = "Max-Age=" ([1-9] digit*) >res_cookie_max_age_start $res_cookie_max_age_digit;
    domain_av         = "Domain=" (alnum | "." | "-")+  >submark %res_cookie_domain %subunmark;
    path_av           = "Path=" ((any - CTL) - ";")+  >submark %res_cookie_path %subunmark;
    secure_av         = "Secure"  %res_cookie_secure;
    httponly_av       = "HttpOnly"  %res_cookie_http_only;
    samesite_av       = ("SameSite" %res_cookie_same_site_strict) | "SameSite=" (("Strict" %res_cookie_same_site_strict) | ("Lax" %res_cookie_same_site_lax) | ("None" %res_cookie_same_site_none));
    extension_av      = ((any - CTL) - ";")+;
    cookie_av         = expires_av | max_age_av | domain_av | path_av | secure_av | httponly_av | samesite_av | extension_av;
    set_cookie_header = /Set-Cookie/i ": " set_cookie_pair ("; " cookie_av)*;

    ################################## HEADERS ########################################
    field_name     = token >mark %header_name %unmark;
    field_vchar    = VCHAR | WSP | obs_text;
    field_value    = field_vchar* >mark %header_value %unmark;
    header_field   = field_name ":" OWS <: field_value;
    content_length = /Content-Length/i ":" OWS digit+ >content_length_start ${ADD_DIGIT(content_length)} OWS;
    te_chunked     = /Transfer-Encoding/i ":" OWS /chunked/i %{message->chunked = true;} OWS;
    header         = content_length | te_chunked | header_field;
    
    ################################## CHUNKS ########################################
    chunk_size      = xdigit+ >{chunk_length = 0;} ${ADD_XDIGIT(chunk_length)};
    chunk_ext_name  = token;
    chunk_ext_val   = token | quoted_string;
    chunk_extension = ( ";" chunk_ext_name ("=" chunk_ext_val)? )+;
    _first_chunk    = chunk_size chunk_extension? CRLF;
    first_chunk    := _first_chunk @done;
    chunk          := CRLF _first_chunk @done;
    chunk_trailer  := (header_field CRLF)* CRLF @done;
    
    ################################## REQUEST ########################################
    method = (  "OPTIONS" %{request->method = Request::Method::OPTIONS; }
              | "GET"     %{request->method = Request::Method::GET; }
              | "HEAD"    %{request->method = Request::Method::HEAD; }
              | "POST"    %{request->method = Request::Method::POST; }
              | "PUT"     %{request->method = Request::Method::PUT; }
              | "DELETE"  %{request->method = Request::Method::DELETE; }
              | "TRACE"   %{request->method = Request::Method::TRACE; }
              | "CONNECT" %{request->method = Request::Method::CONNECT; }
             );
    request_target  = VCHAR+ >mark %request_target %unmark;
    request_line    = method SP request_target SP http_version :> CRLF;
    request_header  = cookie_header | header;
    request_headerX  = header;
    request_headers = (request_header CRLF)* CRLF;
    request        := request_line request_headers @done;
    
    ################################## RESPONSE ########################################
    status_code      = ([1-9] digit{2}) ${ADD_DIGIT(response->code)};
    reason_phrase    = (VCHAR | WSP | obs_text)* >mark %{SAVE(response->message)} %unmark;
    status_line      = http_version SP status_code SP reason_phrase :> CRLF;
    response_header  = set_cookie_header | header;
    response_headerX  = header;
    response_headers = (response_header CRLF)* CRLF;
    response        := status_line response_headers @done;
}%%

namespace panda { namespace protocol { namespace http {

%% write data;

#ifndef PARSER_CONSTANTS

#define ADD_DIGIT(dest) \
    dest *= 10;         \
    dest += *p - '0';
    
#define ADD_XDIGIT(dest) \
    char fc = *p | 0x20; \
    dest *= 16;          \
    dest += fc >= 'a' ? (fc - 'a' + 10) : (fc - '0');

#define _SAVE(dest, mark, acc)                                  \
    if (mark != -1) dest = buffer.substr(mark, p - ps - mark);  \
    else {                                                      \
        dest = std::move(acc);                                  \
        dest.append(ps, p - ps);                                \
    }

#define SAVE(dest)    _SAVE(dest, mark, acc)
#define SUBSAVE(dest) _SAVE(dest, submark, subacc)

size_t Parser::machine_exec (const string& buffer, size_t off) {
    const char* ps = buffer.data();
    const char* p  = ps + off;
    const char* pe = ps + buffer.size();
    %% write exec;
    return p - ps;
}

#endif

}}}
