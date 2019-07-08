%%{

    machine http_response_parser;

    include http_message_parser "MessageParser.rl";

    action begin {
        _PDEBUG("begin");
        if(!current_message_) {
            create_message();
        }
    }

    action reason_phrase {
        _PDEBUG("reason");
        if(marked_buffer_.empty()) {
            current_message_->message = string(_HTTP_PARSER_PTR_TO(mark), _HTTP_PARSER_LEN(mark, fpc));
        } else {
            marked_buffer_.append(string(_HTTP_PARSER_PTR_TO(0), _HTTP_PARSER_LEN(0, fpc)));
            current_message_->message = marked_buffer_;
        }
    }

    action status_code {
        _PDEBUG("status code");
        if(marked_buffer_.empty()) {
            current_message_->code = std::stol(_HTTP_PARSER_PTR_TO(mark), 0);
        } else {
            marked_buffer_.append(string(_HTTP_PARSER_PTR_TO(0), _HTTP_PARSER_LEN(0, fpc)));
            current_message_->code = std::stol(marked_buffer_, 0);
        }
    }

    action done {
        _PDEBUG("done");
        state_ = State::got_header;
        current_message_->set_header();

        // Response to HEAD is the same as response to GET, but without body
        if(requests_.empty()) {
            throw ParserError("Cannot create response as there are no corresponding request");
        }

        if(requests_.back()->method == Request::Method::HEAD
           || current_message_->code  < 200
           || current_message_->code == 203
           || current_message_->code == 304)
        {
            fbreak;
        }

        if(chunked) {
            fcall chunked_body;
            state_ = State::got_body;
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
        fbreak;
    }

    reason_phrase = (any -- crlf)+ >mark %reason_phrase;
    status_code = digit+ >mark %status_code;
    status_line = http_version " " status_code " " reason_phrase :> crlf;

    main := status_line >begin message_header* :> crlf @done;

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
