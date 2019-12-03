#include "MessageParser.h"

%%{
    machine message_parser;
    include rules "Rules.rl";
    
    action mark {
        mark   = fpc - ps;
        marked = true;
    }

    action unmark {
        marked = false;
    }

    action done {
        fbreak;
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
            cs = message_parser_error;
            set_error(errc::multiple_content_length);
            fbreak;
        }
        has_content_length = true;
    }

    action request_target {
        string target;
        SAVE(target);
        request->uri = new URI(target);
    }
    
    http_version  = "HTTP/1." (("0" %{message->http_version = 10;}) | ("1" %{message->http_version = 11;}));
    
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
    method = "OPTIONS" %{request->method = Request::Method::OPTIONS; }
           | "GET"     %{request->method = Request::Method::GET; }
           | "HEAD"    %{request->method = Request::Method::HEAD; }
           | "POST"    %{request->method = Request::Method::POST; }
           | "PUT"     %{request->method = Request::Method::PUT; }
           | "DELETE"  %{request->method = Request::Method::DELETE; }
           | "TRACE"   %{request->method = Request::Method::TRACE; }
           | "CONNECT" %{request->method = Request::Method::CONNECT; }
           ;
    request_target  = VCHAR+ >mark %request_target %unmark;
    request_line    = method SP request_target SP http_version :> CRLF;
    request_header  = header;
    request_headers = (request_header CRLF)* CRLF;
    request        := request_line request_headers @done;
    
    ################################## RESPONSE ########################################
    status_code      = ([1-9] digit{2}) ${ADD_DIGIT(response->code)};
    reason_phrase    = (VCHAR | WSP | obs_text)* >mark %{SAVE(response->message)} %unmark;
    status_line      = http_version SP status_code SP reason_phrase :> CRLF;
    response_header  = header;
    response_headers = (response_header CRLF)* CRLF;
    response        := status_line response_headers @done;
}%%

namespace panda { namespace protocol { namespace http {

%% write data;

#ifdef PARSER_DEFINITIONS_ONLY
#undef PARSER_DEFINITIONS_ONLY
#else

#define ADD_DIGIT(dest) \
    dest *= 10;         \
    dest += *p - '0';
    
#define ADD_XDIGIT(dest) \
    char fc = *p | 0x20; \
    dest *= 16;          \
    dest += fc >= 'a' ? (fc - 'a' + 10) : (fc - '0');

#define SAVE(dest)                                              \
    if (mark != -1) dest = buffer.substr(mark, p - ps - mark);  \
    else {                                                      \
        dest = std::move(acc);                                  \
        dest.append(ps, p - ps);                                \
    }

size_t MessageParser::machine_exec (const string& buffer, size_t off) {
    const char* ps = buffer.data();
    const char* p  = ps + off;
    const char* pe = ps + buffer.size();
    %% write exec;
    return p - ps;
}

#endif

}}}
