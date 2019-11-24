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
    
    action add_header {
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
    
    action content_length_start {
        if (has_content_length) {
            cs = http_parser_error;
            fbreak;
        }
        has_content_length = true;
    }
    
    action request_target {
        string target;
        SAVE(target);
        request->uri = new URI(target);
    }
    
    action done {
        fbreak;
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

    ################################## HEADERS ########################################
    field_name     = token >mark %{SAVE(field_name)} %unmark;
    field_vchar    = VCHAR | obs_text | WSP;
    field_value    = field_vchar* >mark %add_header %unmark; # TODO: obsolete support: "*( field-content / obs-fold )"
    header_field   = field_name ":" OWS <: field_value;
    content_length = /Content-Length/i ":" OWS digit+ >content_length_start ${ADD_DIGIT(content_length)} OWS;
    te_chunked     = /Transfer-Encoding/i ":" OWS /chunked/i %{message->chunked = true;} OWS;
    header         = content_length | te_chunked | header_field;
    headers        = (header CRLF)* CRLF;
    
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
    request_target = VCHAR+ >mark %request_target %unmark;
    request_line   = method SP request_target SP http_version :> CRLF;
    request       := request_line headers @done;
    
    ################################## RESPONSE ########################################
    status_code = ([1-9] digit{2}) ${ADD_DIGIT(response->code)};
    reason_phrase = (VCHAR | WSP | obs_text)* >mark %{SAVE(response->message)} %unmark;
    status_line = http_version SP status_code SP reason_phrase :> CRLF;
    response := status_line headers @done;
}%%

namespace panda { namespace protocol { namespace http {

%% write data;

#ifndef PARSER_CONSTANTS

#define ADD_DIGIT(dest) \
    dest *= 10;         \
    dest += *p - '0';
    
#define ADD_XDIGIT(dest) \
    dest *= 16;          \
    dest += (*p | 0x20) >= 'a' ? (*p - 'a' + 10) : (*p - '0');

#define SAVE(dest)                                              \
    if (mark != -1) dest = buffer.substr(mark, p - ps - mark);  \
    else {                                                      \
        dest = std::move(acc);                                  \
        dest.append(ps, p - ps);                                \
    }

size_t Parser::machine_exec (const string& buffer, size_t off) {
    const char* ps = buffer.data();
    const char* p  = ps + off;
    const char* pe = ps + buffer.size();
    %% write exec;
    return p - ps;
}

#endif

}}}
