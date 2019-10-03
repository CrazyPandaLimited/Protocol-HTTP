/**
 *
 * Copyright (c) 2010, Zed A. Shaw and Mongrel2 Project Contributors.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 *     * Neither the name of the Mongrel2 Project, Zed A. Shaw, nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//
// See Ragel Guide for a full info: https://www.colm.net/files/ragel/ragel-guide-6.4.pdf
//

%%{

    machine http_message_parser;

    action return {
        state = State::done;
        fret;
    }

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

    action write_field {
        marked_buffer = advance_buffer(buffer, fpc, copy_headers);
        current_field_buffer = marked_buffer;
    }

    action write_value {
        // ignore trailing header
        // for details on trailing headers see https://developer.mozilla.org/ru/docs/Web/HTTP/Headers/Trailer
        if(!trailing_header) {
            marked_buffer = advance_buffer(buffer, fpc, copy_headers);

            // rtrim here is good enough for most cases, because proper grammar demands copying each symbol into
            // separate buffer, which is not cheap
            // full grammar could be found here: https://github.com/ki11roy/http_header_field_parser/blob/master/parse_header_field.rl
            current_message->add_header_field(current_field_buffer, rtrim(marked_buffer));
        }
    }

    action write_content_len {
        auto res = panda::from_chars(marked_buffer.data(), marked_buffer.data() + marked_buffer.length(), content_len);
        if (res.ec) {
            state = State::error;
            fbreak;
        } else {
            has_content_len = true;
            body_so_far = 0;
        }
    }

    action write_connection_close {
        connection_close = true;
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
    }

    action chunk_data {
        if(chunk_len > 0) {
            current_message->add_body_part( advance_buffer(buffer, fpc, false) );
        }
    }

    action body_data {
        current_message->add_body_part( advance_buffer(buffer, fpc, false) );
    }

    action trans_chunked {
        chunked = true;
    }

    action http_version {
        if(marked_buffer.empty()) {
            current_message->http_version = string(_HTTP_PARSER_PTR_TO(mark), _HTTP_PARSER_LEN(mark, fpc));
        } else {
            marked_buffer.append(string(_HTTP_PARSER_PTR_TO(0), _HTTP_PARSER_LEN(0, fpc)));
            current_message->http_version = marked_buffer;
        }
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

    http_version = "HTTP/" ( "1." ("0" | "1") ) >mark %http_version %unmark;

    token = ascii -- ( http_ctl | http_separator ) ;

    field_name = token+ >mark %write_field %unmark;

    field_value = (vchar (vchar | lws)*)? >mark %write_value %unmark;

    fields = field_name ":" space* field_value :> crlf;

    content_length = (/Content-Length/i >mark %write_field %unmark ":" space *
            digit+ >mark %write_value %write_content_len %unmark) crlf;

    conn_close = (/Connection/i ":" space* /close/i) crlf %write_connection_close;

    transfer_encoding_chunked = (/Transfer-Encoding/i >mark %write_field %unmark
            ":" space* /chunked/i >mark %write_value %unmark) crlf @trans_chunked;

    message_header = transfer_encoding_chunked | conn_close | content_length | fields;

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
    chunked_body := chunk* final_chunk %return;
}%%
