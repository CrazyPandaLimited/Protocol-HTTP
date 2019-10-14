#pragma once
#include "Message.h"
#include <algorithm>
#include <memory>
#include <panda/string.h>
#include <panda/refcnt.h>
#include <panda/log.h>

namespace panda { namespace protocol { namespace http {

template <class T>
struct MessageParser {
    using MessageSP = iptr<T>;

    enum SizeLimit : size_t {
        SIZE_UNLIMITED = 0,
        SIZE_PROHIBITED = size_t(-1)
    };

    size_t max_body_size; // limits body
    size_t max_message_size; // limits all message with start line, headers and body

protected:
    enum class FinalFlag { CONTINUE, RESET };

    MessageParser (const MessageSP& message, int cs_initial_state) : cs_initial_state(cs_initial_state) {
        reset();
        current_message = message;
    }

    inline void reset () {
        state = State::not_yet;

        content_len = 0;
        body_so_far = 0;
        chunked = false;
        chunk_len = 0;
        chunk_so_far = 0;
        trailing_header = false;
        marked = false;
        copy_headers = false;
        mark = 0;

        max_body_size = SIZE_UNLIMITED;
        max_message_size = SIZE_UNLIMITED;

        // we don't want extra virtual call, so set machine state by hand
        cs = cs_initial_state;
        top = 0;
        current_message.reset();
    }

    inline void unmark () {
        marked = false;
        mark = 0;
        if (!marked_buffer.empty()) marked_buffer.clear();
    }

    // append buffer starting with 'mark', use substr if 'copy' is false.
    // 'copy' is always false when parsing body and set to 'copy_headers' when parsing headers
    inline string advance_buffer (const string& buffer, const char* fpc, bool copy) {
        if (marked_buffer.empty()) {
            if (copy) {
                return string(buffer.data() + mark, fpc - buffer.data() - mark);
            } else {
                return buffer.substr(mark, fpc - buffer.data() - mark);
            }
        } else {
            marked_buffer.append(buffer.substr(0, fpc - buffer.data()));
        }
        return marked_buffer;
    }

    // returns true if it is the last body part, false if more parts needed
    inline bool process_body (const string& buffer, const char*& fpc, const char* pe) {
        mark = fpc - buffer.data();
        marked = true;

        if (body_so_far + (pe - fpc) < content_len) {
            body_so_far += (pe - fpc);
            fpc = pe;

            current_message->add_body_part( advance_buffer(buffer, fpc, false) );
            // append into current marked buffer everything which is unparsed yet
            if(marked) {
                marked_buffer.append(buffer.substr(mark));
                unmark();
            }

            // content length is not reached, body is incomplete
            state = State::in_body;
            return false;
        } else {
            fpc += (content_len - body_so_far);
            body_so_far = content_len;

            current_message->add_body_part( advance_buffer(buffer, fpc, false) );
            unmark();

            // there was the last body part
            state = State::done;
            return true;
        }
    }

protected:
    // marked buffer contains unfinished field and used to parse messages that come in fragments
    // set only if parser stopped while processing buffer
    // for more details see Ragel guide 5.9 "Maintaining Pointers to Input Data"
    string    marked_buffer;
    string    current_field_buffer;
    MessageSP current_message;
    State     state; // more general parser state, not used by Ragel
    size_t    content_len;
    size_t    body_so_far;
    size_t    chunk_len;
    size_t    chunk_so_far;
    bool      chunked;
    bool      has_content_len;
    bool      trailing_header;
    bool      marked;
    bool      copy_headers;
    size_t    mark;
    const int cs_initial_state; // initial state, set by specific parser implementation
    // internal variables used by Ragel, see guide 5.1 "Variables Used by Ragel"
    int cs;            // current state
    int top, stack[1]; // to call subparsers with fcall/fret
};

}}}
