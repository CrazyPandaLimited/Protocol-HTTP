%%{
    machine http_request_parser;

    include http_message_parser "MessageParser.rl";

    action request_uri {
        _PDEBUG("uri");
        if(marked_buffer_.empty()) {
            current_message_->uri = make_iptr<uri::URI>(string(_HTTP_PARSER_PTR_TO(mark), _HTTP_PARSER_LEN(mark, fpc)));
        } else {
            marked_buffer_.append(string(_HTTP_PARSER_PTR_TO(0), _HTTP_PARSER_LEN(0, fpc)));
            current_message_->uri = make_iptr<uri::URI>(marked_buffer_);
        }
    }

    action done {
        _PDEBUG("done");
        state_ = State::got_header;
        current_message_->set_header();
        if(chunked) {
            fcall chunked_body;
            state_ = State::done;
            current_message_->set_body();;
        }
        else if(content_len > 0) {
            // we are between headers and body and there are no body yet
            // current position is on LF
            if(pe - fpc == 1) {
                // set state and wait for the body in next calls
                state_ = State::in_body;
            } else {
                // we have more buffer to process,
                // set position on the next character and proceed
                process_body(buffer, ++fpc, pe);
            }
        }
        else {
            state_ = State::done;
        }
        fbreak;
    }

    method = ( "OPTIONS" @{current_message_->method = Request::Method::OPTIONS; }
             | "GET" @{current_message_->method = Request::Method::GET; }
             | "HEAD" @{current_message_->method = Request::Method::HEAD; }
             | "POST" @{current_message_->method = Request::Method::POST; }
             | "PUT" @{current_message_->method = Request::Method::PUT; }
             | "DELETE" @{current_message_->method = Request::Method::DELETE; }
             | "TRACE" @{current_message_->method = Request::Method::TRACE; }
             | "CONNECT" @{current_message_->method = Request::Method::CONNECT; }
             ) ;

    uri_reference = vchar+ >mark %request_uri %unmark;

    request_line = method " " uri_reference " " http_version crlf;

    main := request_line message_header* :> crlf @done;
}%%

#if defined(MACHINE_DATA)
#undef MACHINE_DATA
%%{
    write data;
}%%
#endif

#if defined(MACHINE_INIT)
#undef MACHINE_INIT
%%{
    write init;
}%%
#endif

#if defined(MACHINE_EXEC)
#undef MACHINE_EXEC
%%{
    write exec;
}%%
#endif
