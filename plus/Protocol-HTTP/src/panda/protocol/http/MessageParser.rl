%%{

    machine http_message_parser;

    action mark {
        // mark the beginning of the buffer to copy it later
        // there is only one mark at a time, no inner buffers are possible
        mark = fpc - buffer_ptr;
        marked = true;
    }

    action unmark {
        marked = false;
        mark = 0;
        if (!marked_buffer.empty()) marked_buffer.clear();
    }

    action write_hdr_name {
        current_field_buffer = advance_buffer(buffer, fpc);
    }

    action write_hdr_value {
        // ignore trailing header
        // for details on trailing headers see https://developer.mozilla.org/ru/docs/Web/HTTP/Headers/Trailer
        if(!trailing_header) {
            marked_buffer = advance_buffer(buffer, fpc);

            // rtrim here is good enough for most cases, because proper grammar demands copying each symbol into
            // separate buffer, which is not cheap
            // full grammar could be found here: https://github.com/ki11roy/http_header_field_parser/blob/master/parse_header_field.rl
            rtrim(marked_buffer);
            current_message->headers.add(current_field_buffer, marked_buffer);
            headers_so_far += current_field_buffer.length() + marked_buffer.length() + 4;
        }
    }
    
    action hdr_clen_start {
        if (has_content_len) {
            state = State::error;
            fbreak;
        }
        has_content_len = true;
    }
    
    action hdr_clen_digit {
        if (content_len > 1000000000000000000) {
            state = State::error;
            fbreak;
        }
        content_len *= 10;
        content_len += fc - '0';
    }
    
    action hdr_te_chunked {
        current_message->chunked = true;
    }
    
    action write_trailing_header {
        trailing_header = true;
    }

    action chunk_size {
        string len_str;
        if(marked_buffer.empty()) {
            len_str = string(_HTTP_PARSER_PTR_TO(mark), _HTTP_PARSER_LEN(mark, fpc));
        } else {
            marked_buffer.append(string(_HTTP_PARSER_PTR_TO(0), _HTTP_PARSER_LEN(0, fpc)));
            len_str = marked_buffer;
        }
        auto len = len_str.length();
        if (len > 16 || panda::from_chars(len_str.data(), len_str.data() + len, chunk_len, 16).ec) {
            state = State::error;
            fbreak;
        }
        chunk_so_far = 0;
        body_so_far += chunk_len;
    }

    action chunk_data {
        if (chunk_len > 0) {
            current_message->body.parts.push_back(advance_buffer(buffer, fpc));
        }
    }
    
    action final_chunk {
        state = State::done;
        //instead of fret that does not work in the end of main we make its work manualy
        --top;
        cs = stack[top];
        fbreak;
    }

    action body_data {
        current_message->add_body_part( advance_buffer(buffer, fpc) );
    }

    action http_version10 {
        current_message->http_version = 10;
    }

    action http_version11 {
        current_message->http_version = 11;
    }
    
#### HTTP PROTOCOL GRAMMAR
    crlf = "\r\n" ;
    lws = crlf? (" " | "\t")+ ;

    # visible characters (no whitespace)
    vchar = 0x21..0x7e;

    http_ctl = cntrl | 127 ;
    http_separator = ( "(" | ")" | "<" | ">" | "@"
                     | "," | ";" | ":" | "\\" | "\""
                     | "/" | "[" | "]" | "?" | "="
                     | "{" | "}" | " " | "\t"
                     ) ;

    http_version10 = "HTTP/1.0" %http_version10;
    http_version11 = "HTTP/1.1" %http_version11;
    http_version = http_version11 | http_version10;

    token = ascii -- ( http_ctl | http_separator ) ;

    field_name = token+ >mark %write_hdr_name %unmark;

    field_value = (vchar (vchar | lws)*)? >mark %write_hdr_value %unmark;

    fields = field_name ":" space* field_value :> crlf;

    hdr_clen       = (/Content-Length/i ":" space * digit+ >hdr_clen_start $hdr_clen_digit) crlf;
    #hdr_conn_close = (/Connection/i ":" space* /close/i) crlf @hdr_conn_close;
    #hdr_conn_ka    = (/Connection/i ":" space* /keep-alive/i) crlf @hdr_conn_ka;
    hdr_te_chunked = (/Transfer-Encoding/i ":" space* /chunked/i) crlf @hdr_te_chunked;

    message_header = hdr_clen | hdr_te_chunked | fields;

    chunk_ext_val = token+;
    chunk_ext_name = token+;
    chunk_extension = (";" chunk_ext_name ("=" chunk_ext_val )? )*;
    chunk_size = xdigit+ >mark %chunk_size %unmark;
    chunk_data = any* >mark %chunk_data %unmark when { chunk_so_far++ < chunk_len };

    trailing_header = fields* >write_trailing_header;

    # the <: operator shifts priority to chunk_data machine, so it ignores crlf in chunk data
    chunk = chunk_size chunk_extension crlf chunk_data <: trailing_header :> crlf;
    final_chunk = "0" chunk_extension crlf trailing_header :> crlf;

    #separate chunked body parser
    chunked_body := (chunk - final_chunk)* final_chunk @final_chunk;
}%%
