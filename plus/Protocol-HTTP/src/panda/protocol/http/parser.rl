%%{
    machine http_parser;
    
    action mark {
        mark = fpc - ps;
    }
    
    action unmark {
        mark = -1;
    }
    
    action add_header {
        string value;
        SAVE(value);
        if (!headers_finished) message->headers.add(field_name, value);
        else; // trailing header after chunks, currently we just ignore them
    }
    
    action content_length_start {
        if (has_content_length) {
            cs = http_parser_error;
            fbreak;
        }
        has_content_length = true;
        content_length = 0;
    }
    
    action request_target {
        string target;
        SAVE(target);
        message->uri = new URI(target);
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
    field_vchar    = VCHAR | obs_text;
    field_content  = field_vchar (WSP+ field_vchar)?;
    field_value    = field_vchar* >mark %add_header %unmark; # TODO: obsolete support: "*( field-content / obs-fold )"
    header_field   = field_name ":" OWS <: field_value OWS;
    content_length = /Content-Length/i ":" SP* digit+ >content_length_start ${ADD_DIGIT(content_length)};
    te_chunked     = /Transfer-Encoding/i ":" SP* /chunked/i %{message->chunked = true;};
    header         = content_length | te_chunked | header_field;
    headers        = (header CRLF)* CRLF;
    
    ################################## CHUNKS ########################################
    chunk_size      = xdigit+ >{chunk_length = 0;} ${ADD_XDIGIT(chunk_len)};
    chunk_ext_name  = token;
    chunk_ext_val   = token | quoted_string;
    chunk_extension = ( ";" chunk_ext_name ("=" chunk_ext_val)? )+;
    chunk_start    := chunk_size chunk_extension? CRLF;
    chunk_end      := CRLF;
    chunk_trailer  := (header_field CRLF)* CRLF;
    
    ################################## REQUEST ########################################
    method = (  "OPTIONS" %{message->method = Request::Method::OPTIONS; }
              | "GET"     %{message->method = Request::Method::GET; }
              | "HEAD"    %{message->method = Request::Method::HEAD; }
              | "POST"    %{message->method = Request::Method::POST; }
              | "PUT"     %{message->method = Request::Method::PUT; }
              | "DELETE"  %{message->method = Request::Method::DELETE; }
              | "TRACE"   %{message->method = Request::Method::TRACE; }
              | "CONNECT" %{message->method = Request::Method::CONNECT; }
             );
    request_target = VCHAR+ >mark %request_target %unmark;
    request_line   = method SP request_target SP http_version :> CRLF;
    request       := request_line headers;
    
    ################################## RESPONSE ########################################
    status_code = [1-9] digit{2} ${ADD_DIGIT(message->code)};
    reason_phrase = (VCHAR | WSP | obs_text)* >mark %{SAVE(message->message)} %unmark;
    status_line = http_version SP status_code SP reason_phrase :> CRLF;
    response := status_line headers;
    
    ################################## ACTIONS ########################################

}%%

#ifdef MACHINE_DATA
    #undef MACHINE_DATA

    #define ADD_DIGIT(dest) \
        dest *= 10;         \
        dest += fc - '0';
        
    #define ADD_XDIGIT(dest) \
        dest *= 16;          \
        dest += (fc | 0x20) >= 'a' ? (fc - 'a' + 10) : (fc - '0');
    
    #define SAVE(dest)                                              \
        if (mark != -1) dest = buffer.substr(mark, fpc - ps - mark);\
        else {                                                      \
            dest = std::move(acc);                                  \
            dest.append(ps, fpc - ps);                              \
        }

    %% write data;
#endif

#ifdef MACHINE_INIT
    #undef MACHINE_INIT
    %% write init;
#endif

#ifdef MACHINE_EXEC
    #undef MACHINE_EXEC
    %% write exec;
#endif
