%%{

    machine http_response_parser;

    include http_message_parser "MessageParser.rl";

    action begin {
        if (!current_message) create_message();
    }

    action reason_phrase {
        if(marked_buffer.empty()) {
            current_message->message = string(_HTTP_PARSER_PTR_TO(mark), _HTTP_PARSER_LEN(mark, fpc));
        } else {
            marked_buffer.append(string(_HTTP_PARSER_PTR_TO(0), _HTTP_PARSER_LEN(0, fpc)));
            current_message->message = marked_buffer;
        }
    }

    action status_code {
        string code_str;
        if (marked_buffer.empty()) {
            code_str = string(_HTTP_PARSER_PTR_TO(mark), _HTTP_PARSER_LEN(mark, fpc));
        } else {
            marked_buffer.append(string(_HTTP_PARSER_PTR_TO(0), _HTTP_PARSER_LEN(0, fpc)));
            code_str = marked_buffer;
        }
        auto res = panda::from_chars(code_str.data(), code_str.data() + code_str.length(), current_message->code);
        if (res.ec || current_message->code < 100 || current_message->code > 999) {
            state = State::error;
            fbreak;
        }
    }

    action append_mark {
        if(marked_buffer.empty()) {
        } else {
            marked_buffer.append(string(_HTTP_PARSER_PTR_TO(0), _HTTP_PARSER_LEN(0, fpc)));
        }
    }

    action done {
        state = State::got_header;

        // Response to HEAD is the same as response to GET, but without body
        if (!_request) throw_no_request();

        if (_request->method == Request::Method::HEAD || current_message->code  < 200 || current_message->code == 203 || current_message->code == 304) {
            state = State::done;
            fbreak;
        }

        if(chunked) {
            fcall chunked_body;
            state = State::done;
        }
        else if(has_content_len) {
            if(content_len > 0) {
                // we are between headers and body and there are no body yet
                // current position is on LF
                if(pe - fpc == 1) {
                    // set state and wait for the body in next calls
                    state = State::in_body;
                } else {
                    // we have more buffer to process,
                    // set position on the next character and proceed
                    process_body(buffer, ++fpc, pe);
                }
            } else {
                state = State::done;
            }
        } else if (!current_message->keep_alive()) { // Connection: close
            state = State::in_body;
            current_message->add_body_part(string(fpc+1, pe - fpc - 1));
            fpc = pe;
        }
        fbreak;
    }

    reason_phrase = (any -- crlf)+ >mark %reason_phrase %unmark;
    status_code = digit+ >mark %status_code %unmark;
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
