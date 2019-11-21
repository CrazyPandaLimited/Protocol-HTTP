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
    }
    
    action request_target {
        string target;
        SAVE(target);
        request->uri = new URI(target);
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
    _first_chunk    = chunk_size chunk_extension? CRLF;
    first_chunk    := _first_chunk;
    chunk          := CRLF _first_chunk;
    chunk_trailer  := (header_field CRLF)* CRLF;
    
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
    request       := request_line headers;
    
    ################################## RESPONSE ########################################
    status_code = [1-9] digit{2} ${ADD_DIGIT(response->code)};
    reason_phrase = (VCHAR | WSP | obs_text)* >mark %{SAVE(response->message)} %unmark;
    status_line = http_version SP status_code SP reason_phrase :> CRLF;
    response := status_line headers;
}%%

#include "Parser.h"

namespace panda { namespace protocol { namespace http {

%% write data;

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

size_t Parser::machine_exec (const string& buffer, size_t off) {
    const char* ps = buffer.data();
    const char* p  = ps + off;
    const char* pe = ps + buffer.size();
    %% write exec;
    return p - ps;
}

#define RETURN_IF_PARSE_ERROR do if (cs == http_parser_error) { \
    if (!message->error()) message->error(errc::lexical_error); \
    return pos;                                                 \
} while (0)

#define RETURN_IF_INCOMPLETE do if (cs < http_parser_first_final) { \
    if (mark) {                                                     \
        acc = buffer.substr(mark - ps, p - mark);                   \
        mark = nullptr;                                             \
    }                                                               \
    return pos;                                                     \
} while (0)

#define RETURN_IF_MAX_BODY_SIZE(current_size) do if (current_size > max_body_size) {    /
    message->error(max_body_size ? errc::body_too_large : errc::unexpected_body);       /
    return pos;                                                                         /
} while (0)

template <class F1, class F2>
size_t Parser::parse (const string& buffer, F1&& headers_finished_cb, F2&& no_body_cb) {
    auto   len = buffer.length();
    size_t pos = 0;

    while (pos != len) switch (message->state()) {
        case State::headers:
            pos = machine_exec(buffer, pos);
            RETURN_IF_PARSE_ERROR;

            headers_so_far += pos;
            if (headers_so_far > max_headers_size) {
                message->error(errc::headers_too_large);
                return pos;
            }
            
            RETURN_IF_INCOMPLETE;
            
            if (!headers_finished_cb()) return pos;

            if (message->chunked) {
                message->state(State::chunk);
                cs = http_parser_en_first_chunk;
            }
            else if (content_length > 0) {
                message->state(State::body);
                RETURN_IF_MAX_BODY_SIZE(content_length);
            }
            else if (!no_body_cb()) return pos;
            
            continue;

        case State::body:
            auto have = len - pos;
            
            if (content_length) {
                auto left = content_length - body_so_far;
                if (have >= left) {
                    message->body.parts.push_back(buffer.substr(pos, left));
                    message->state(State::done);
                    return pos + left;
                }
                else {
                    body_so_far += have;
                    message->body.parts.push_back(buffer.substr(pos));
                    return len;
                }
            }

            body_so_far += have;
            RETURN_IF_MAX_BODY_SIZE(body_so_far);
            message->body.parts.push_back(buffer.substr(pos));
            return len;

        case State::chunk:
            pos = machine_exec(buffer, pos);
            RETURN_IF_PARSE_ERROR;
            RETURN_IF_INCOMPLETE;

            if (!chunk_length) { // final chunk
                message->state(State::chunk_trailer);
                cs = http_parser_en_chunk_trailer;
                continue;
            }

            body_so_far += chunk_length;
            RETURN_IF_MAX_BODY_SIZE(body_so_far);

            chunk_so_far = 0;
            message->state(State::chunk_body);
            continue;

        case State::chunk_body:
            auto left = chunk_length - chunk_so_far;
            auto have = len - pos;

            if (have >= left) {
                message->body.parts.push_back(buffer.substr(off, left));
                message->state(State::chunk);
                cs = http_parser_en_chunk;
                pos += left;
                continue;
            } else {
                message->body.parts.push_back(buffer.substr(pos));
                chunk_so_far += have;
                return len;
            }

        case State::chunk_trailer:
            pos = machine_exec(buffer, pos);
            RETURN_IF_PARSE_ERROR;
            RETURN_IF_INCOMPLETE;
            message->state(State::done);
            return pos;
    }
}

}}}
