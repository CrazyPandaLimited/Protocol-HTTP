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

    MessageParser () {
        max_headers_size = SIZE_UNLIMITED;
        max_body_size    = SIZE_UNLIMITED;
    }

    MessageParser (const MessageParser&) = delete;
    MessageParser (MessageParser&&)      = default;

    inline void reset () {
        message.reset();
        state = State::headers;
        mark = nullptr;
        headers_so_far = 0;
        headers_finished = false;
        has_content_length = false;
//        body_so_far = 0;
//        chunk_len = 0;
//        chunk_so_far = 0;
//
//        // we don't want extra virtual call, so set machine state by hand
//        cs = cs_initial_state;
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
    MessageSP message;
    State     state; // high-level state
    int       cs; // ragel state
    ssize_t   mark;
    string    acc; // contains unfinished field and used to parse messages that come in fragments
    string    field_name;
    size_t    headers_so_far;
    bool      headers_finished;
    bool      has_content_length;
    uint64_t  content_length;
    size_t    chunk_length;
    //size_t    body_so_far;
    //size_t    chunk_so_far;
    //const int cs_initial_state; // initial state, set by specific parser implementation
};

}}}
