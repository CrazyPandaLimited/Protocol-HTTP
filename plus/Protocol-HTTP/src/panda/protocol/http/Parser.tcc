#pragma once
#include "Parser.h"

#define PARSER_CONSTANTS
#include "Parser.cc"

namespace panda { namespace protocol { namespace http {

#define RETURN_IF_PARSE_ERROR do if (cs == http_parser_error) { \
    if (!message->error()) message->error(errc::lexical_error); \
    return pos;                                                 \
} while (0)

#define RETURN_IF_INCOMPLETE do if (cs < http_parser_first_final) { \
    if (marked) {                                                   \
        if (mark != -1) {                                           \
            acc = buffer.substr(mark, len - mark);                  \
            mark = -1;                                              \
        }                                                           \
        else acc += buffer;                                         \
    }                                                               \
    return pos;                                                     \
} while (0)

#define RETURN_IF_MAX_BODY_SIZE(current_size) do if (current_size > max_body_size) {    \
    message->error(max_body_size ? errc::body_too_large : errc::unexpected_body);       \
    return pos;                                                                         \
} while (0)

template <class F1, class F2>
size_t Parser::parse (const string& buffer, F1&& after_headers_cb, F2&& no_body_cb) {
    auto   len = buffer.length();
    size_t pos = 0;
    //printf("parse: %s\n", buffer.c_str());

    while (pos != len) switch (message->state()) {
        case State::headers: {
            //printf("headers\n");
            pos = machine_exec(buffer, pos);
            RETURN_IF_PARSE_ERROR;

            headers_so_far += pos;
            if (headers_so_far > max_headers_size) {
                message->error(errc::headers_too_large);
                return pos;
            }
            
            RETURN_IF_INCOMPLETE;
            
            headers_finished = true;
            if (!after_headers_cb()) return pos;

            if (message->chunked) {
                message->state(State::chunk);
                cs = http_parser_en_first_chunk;
            }
            else if (has_content_length) {
                if (content_length > 0) {
                    message->state(State::body);
                    RETURN_IF_MAX_BODY_SIZE(content_length);
                } else {
                    message->state(State::done);
                    return pos;
                }
            }
            else if (!no_body_cb()) return pos;
            
            continue;
        }
        case State::body: {
            //printf("body\n");
            auto have = len - pos;
            
            if (content_length) {
                auto left = content_length - body_so_far;
                if (have >= left) {
                    message->body.parts.push_back(buffer.substr(pos, left));
                    message->state(State::done);
                    return pos + left;
                }
                else {
                    body_so_far += have;
                    message->body.parts.push_back(buffer.substr(pos));
                    return len;
                }
            }

            body_so_far += have;
            RETURN_IF_MAX_BODY_SIZE(body_so_far);
            message->body.parts.push_back(buffer.substr(pos));
            return len;
        }
        case State::chunk: {
            //printf("chunk. rest: %s\n", buffer.substr(pos).c_str());
            pos = machine_exec(buffer, pos);
            RETURN_IF_PARSE_ERROR;
            RETURN_IF_INCOMPLETE;

            if (!chunk_length) { // final chunk
                message->state(State::chunk_trailer);
                cs = http_parser_en_chunk_trailer;
                continue;
            }
            //printf("chunk len = %llu\n", chunk_length);

            body_so_far += chunk_length;
            RETURN_IF_MAX_BODY_SIZE(body_so_far);

            chunk_so_far = 0;
            message->state(State::chunk_body);
            continue;
        }
        case State::chunk_body: {
            //printf("chunk body\n");
            auto left = chunk_length - chunk_so_far;
            auto have = len - pos;

            if (have >= left) {
                message->body.parts.push_back(buffer.substr(pos, left));
                message->state(State::chunk);
                cs = http_parser_en_chunk;
                pos += left;
                continue;
            } else {
                message->body.parts.push_back(buffer.substr(pos));
                chunk_so_far += have;
                return len;
            }
        }
        case State::chunk_trailer: {
            //printf("chjunk trailer\n");
            pos = machine_exec(buffer, pos);
            RETURN_IF_PARSE_ERROR;
            RETURN_IF_INCOMPLETE;
            message->state(State::done);
            return pos;
        }
        default: abort();
    }
    
    return len;
}

}}}
