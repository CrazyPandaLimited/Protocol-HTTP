#pragma once
#include "Message.h"
#include <algorithm>
#include <memory>
#include <panda/string.h>
#include <panda/refcnt.h>
#include <panda/log.h>

namespace panda { namespace protocol { namespace http {

constexpr const size_t SIZE_UNLIMITED = size_t(-1);

template <class T>
struct MessageParser {
    using MessageSP = iptr<T>;

    size_t max_headers_size;
    size_t max_body_size;

protected:
    enum class FinalFlag { CONTINUE, RESET };

    MessageParser (const MessageSP& message, int cs_initial_state) : cs_initial_state(cs_initial_state) {
        reset();
        current_message = message;
        max_headers_size = SIZE_UNLIMITED;
        max_body_size = SIZE_UNLIMITED;
    }

    inline void reset () {
        state = State::not_yet;

        headers_so_far = 0;
        content_len = 0;
        body_so_far = 0;
        chunk_len = 0;
        chunk_so_far = 0;
        has_content_len = false;
        trailing_header = false;
        marked = false;
        mark = 0;

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
    inline string advance_buffer (const string& buffer, const char* fpc) {
        if (marked_buffer.empty()) {
            return buffer.substr(mark, fpc - buffer.data() - mark);
        } else {
            marked_buffer.append(buffer.substr(0, fpc - buffer.data()));
        }
        return marked_buffer;
    }

    // returns true if it is the last body part, false if more parts needed
    inline bool process_body (const string& buffer, const char*& fpc, const char* pe) {
        mark = fpc - buffer.data();
        marked = true;

        if (!content_len || body_so_far + (pe - fpc) < content_len) {
            body_so_far += (pe - fpc);
            fpc = pe;

            current_message->body.parts.push_back(advance_buffer(buffer, fpc));
            // append into current marked buffer everything which is unparsed yet
            if (marked) {
                marked_buffer.append(buffer.substr(mark));
                unmark();
            }

            // content length is not reached, body is incomplete
            state = State::in_body;
            return false;
        } else {
            fpc += (content_len - body_so_far);
            body_so_far = content_len;

            current_message->body.parts.push_back(advance_buffer(buffer, fpc));
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
    size_t    headers_so_far;
    uint64_t  content_len;
    size_t    body_so_far;
    size_t    chunk_len;
    size_t    chunk_so_far;
    bool      has_content_len;
    bool      trailing_header;
    bool      marked;
    size_t    mark;
    const int cs_initial_state; // initial state, set by specific parser implementation
    // internal variables used by Ragel, see guide 5.1 "Variables Used by Ragel"
    int cs;            // current state
    int top, stack[1]; // to call subparsers with fcall/fret
};

}}}
