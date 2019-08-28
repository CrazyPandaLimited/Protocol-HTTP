#pragma once

#include <iostream>
#include <algorithm>
#include <memory>

#include <panda/string.h>
#include <panda/refcnt.h>
#include <panda/log.h>

#include "Message.h"

#define _HTTP_PARSER_LEN(AT, FPC) (FPC - buffer_ptr - AT)
#define _HTTP_PARSER_PTR_TO(F) (buffer_ptr + F)

// do copy headers or to substr them while parsing
#define ENABLE_HTTP_COPYING_HEADERS 1
#ifdef ENABLE_HTTP_COPYING_HEADERS
#define HTTP_COPYING_HEADERS true
#else
#define HTTP_COPYING_HEADERS false
#endif

//#define HTTP_PARSER_DEBUG 1

#ifdef HTTP_PARSER_DEBUG
#define _PDEBUG(x) do { std::cerr << "[http parser]" << x << std::endl; } while (0)
#else
#define _PDEBUG(x)
#endif

namespace panda { namespace protocol { namespace http {

// Base class for a HTTP request parser.
// Uncomment HTTP_PARSER_DEBUG to enable debug messages.
template <class I, class T>
class MessageParser : public virtual Refcnt {
public:
    using MessageSP = iptr<T>;

    MessageParser(MessageSP message, int cs_initial_state) :
        current_message_(message),
        cs_initial_state_(cs_initial_state)
    {
        init();
    }

    enum class State {
        not_yet,
        got_header,
        in_body,
        done,
        error
    };

    MessageSP create_message() { return static_cast<I*>(this)->create_message(); }

    virtual MessageSP message() {
        return current_message_;
    }

    void inline init() {
        state_ = State::not_yet;

        content_len = 0;
        body_so_far = 0;
        chunked = false;
        chunk_len = 0;
        chunk_so_far = 0;
        connection_close = false;
        trailing_header = false;
        marked = false;
        mark = 0;

        max_body_size = SIZE_UNLIMITED;
        max_message_size = SIZE_UNLIMITED;

        // we don't want extra virtual call, so set machine state by hand
        cs = cs_initial_state_;
        top = 0;
    }

    enum SizeLimit : size_t {
        SIZE_UNLIMITED = 0,
        SIZE_PROHIBITED = size_t(-1)
    };

    size_t max_body_size; // limits body
    size_t max_message_size; // limmits all message with start line, headers and body

protected:
    enum class FinalFlag {
        CONTINUE, RESET
    };

    inline void unmark() {
        _PDEBUG("unmark");
        marked = false;
        mark = 0;
        if(!marked_buffer_.empty())
            marked_buffer_.clear();
    }

    // append buffer starting with 'mark', use substr if 'want_copy' is false
    inline string advance_buffer(const string& buffer, const char* fpc, bool want_copy=true) {
        if(marked_buffer_.empty()) {
            if(want_copy) {
                return string(buffer.data() + mark, fpc - buffer.data() - mark);
            } else {
                return buffer.substr(mark, fpc - buffer.data() - mark);
            }
        } else {
            marked_buffer_.append(buffer.substr(0, fpc - buffer.data()));
        }
        return marked_buffer_;
    }

    // returns true if it is the last body part, false if more parts needed
    inline bool process_body(const string& buffer, const char*& fpc, const char* pe) {
        _PDEBUG("processing body");

        mark = fpc - buffer.data();
        marked = true;

        if(body_so_far + (pe - fpc) < content_len) {
            _PDEBUG("processing body, incomplete");
            body_so_far += (pe - fpc);
            fpc = pe;

            current_message_->add_body_part( advance_buffer(buffer, fpc, false) );
            // append into current marked buffer everything which is unparsed yet
            if(marked) {
                marked_buffer_.append(buffer.substr(mark));
                unmark();
            }

            // content length is not reached, body is incomplete
            state_ = State::in_body;
            return false;
        } else {
            _PDEBUG("processing body, last part");
            fpc += (content_len - body_so_far);
            body_so_far = content_len;

            current_message_->add_body_part( advance_buffer(buffer, fpc, false) );
            unmark();

            // there was the last body part
            state_ = State::done;
            current_message_->set_body();
            return true;
        }
    }

protected:
    // marked buffer contains unfinished field and used to parse messages that come in fragments
    // set only if parser stopped while processing buffer
    // for more details see Ragel guide 5.9 "Maintaining Pointers to Input Data"
    string marked_buffer_;
    string current_field_buffer_;
    MessageSP current_message_;

    // more general parser state, not used by Ragel
    State state_;

    size_t content_len;
    size_t body_so_far;
    bool chunked;
    size_t chunk_len;
    size_t chunk_so_far;
    bool connection_close;
    bool trailing_header;
    bool marked;
    size_t mark;

    // initial state, set by specific parser implementation
    int cs_initial_state_;

    // internal variables used by Ragel, see guide 5.1 "Variables Used by Ragel"
    int cs;  // current state
    int top, stack[1]; // to call subparsers with fcall/fret
};

inline
string rtrim(string const& str) {
    static char const* whitespaceChars = " ";
    string::size_type end = str.find_last_not_of( whitespaceChars );
    return end == string::npos ? str : str.substr( 0, end + 1);
}

}}} // namespace panda::protocol::http
