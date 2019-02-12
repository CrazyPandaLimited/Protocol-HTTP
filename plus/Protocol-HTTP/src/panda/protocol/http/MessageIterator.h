#pragma once

#include <panda/string.h>

#include "MessageParser.h"

namespace panda { namespace protocol { namespace http {

template <class P, class R>
class MessageIterator
{
    friend P;

public:
    using iterator_category = std::input_iterator_tag;
    using value_type        = R;
    using difference_type   = std::ptrdiff_t;
    using pointer           = R*;
    using reference         = R&;

    MessageIterator operator++() {
        MessageIterator i = *this;
        parse();
        return i;
    }

    MessageIterator operator++(int) {
        parse();
        return *this;
    }

    R& operator*() { return result_; }

    R* operator->() { return &result_; }

    bool operator==(const MessageIterator& rhs) const {
        return parser_ == rhs.parser_ && result_.state == rhs.result_.state && result_.position == rhs.result_.position && buffer_ == rhs.buffer_;
    }

    bool operator!=(const MessageIterator& rhs) const {
        return parser_ != rhs.parser_ || result_.state != rhs.result_.state || result_.position != rhs.result_.position || buffer_ != rhs.buffer_;
    }

private:
    // parse first message
    MessageIterator(P* parser, const string& buffer) : parser_(parser), buffer_(buffer) { parse(); }

    void parse() {
        _PDEBUG("parse iterator, buffer size: " << buffer_.size());
        result_ = parser_->parse_first(buffer_);
        if (result_.position >= buffer_.size()) {
            buffer_.clear();
        } else {
            buffer_ = buffer_.substr(result_.position);
        }
    }

private:
    P*     parser_;
    R      result_;
    string buffer_;
};

}}} // namespace panda::protocol::http
