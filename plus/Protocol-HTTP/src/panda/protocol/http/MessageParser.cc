
#line 1 "src/panda/protocol/http/MessageParser.rl"
#include "MessageParser.h"


#line 168 "src/panda/protocol/http/MessageParser.rl"


namespace panda { namespace protocol { namespace http {


#line 13 "src/panda/protocol/http/MessageParser.cc"
static const int message_parser_start = 1;
static const int message_parser_first_final = 316;
static const int message_parser_error = 0;

static const int message_parser_en_first_chunk = 96;
static const int message_parser_en_chunk = 106;
static const int message_parser_en_chunk_trailer = 118;
static const int message_parser_en_request = 124;
static const int message_parser_en_response = 1;


#line 173 "src/panda/protocol/http/MessageParser.rl"

#ifdef PARSER_DEFINITIONS_ONLY
#undef PARSER_DEFINITIONS_ONLY
#else

#define ADD_DIGIT(dest) \
    dest *= 10;         \
    dest += *p - '0';
    
#define ADD_XDIGIT(dest) \
    char fc = *p | 0x20; \
    dest *= 16;          \
    dest += fc >= 'a' ? (fc - 'a' + 10) : (fc - '0');

#define SAVE(dest)                                              \
    if (mark != -1) dest = buffer.substr(mark, p - ps - mark);  \
    else {                                                      \
        dest = std::move(acc);                                  \
        dest.append(ps, p - ps);                                \
    }

size_t MessageParser::machine_exec (const string& buffer, size_t off) {
    const char* ps = buffer.data();
    const char* p  = ps + off;
    const char* pe = ps + buffer.size();
    
#line 52 "src/panda/protocol/http/MessageParser.cc"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	if ( (*p) == 72 )
		goto st2;
	goto st0;
st0:
cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 84 )
		goto st3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 84 )
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 80 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 47 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 49 )
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 46 )
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	switch( (*p) ) {
		case 48: goto st9;
		case 49: goto st95;
	}
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 32 )
		goto tr10;
	goto st0;
tr10:
#line 102 "src/panda/protocol/http/MessageParser.rl"
	{message->http_version = 10;}
	goto st10;
tr123:
#line 102 "src/panda/protocol/http/MessageParser.rl"
	{message->http_version = 11;}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 135 "src/panda/protocol/http/MessageParser.cc"
	if ( 49 <= (*p) && (*p) <= 57 )
		goto tr11;
	goto st0;
tr11:
#line 162 "src/panda/protocol/http/MessageParser.rl"
	{ADD_DIGIT(response->code)}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 147 "src/panda/protocol/http/MessageParser.cc"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr12;
	goto st0;
tr12:
#line 162 "src/panda/protocol/http/MessageParser.rl"
	{ADD_DIGIT(response->code)}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 159 "src/panda/protocol/http/MessageParser.cc"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr13;
	goto st0;
tr13:
#line 162 "src/panda/protocol/http/MessageParser.rl"
	{ADD_DIGIT(response->code)}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 171 "src/panda/protocol/http/MessageParser.cc"
	if ( (*p) == 32 )
		goto st14;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	switch( (*p) ) {
		case 13: goto tr16;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto tr15;
tr15:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 200 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr18;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st15;
tr16:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
#line 163 "src/panda/protocol/http/MessageParser.rl"
	{SAVE(response->message)}
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st16;
tr18:
#line 163 "src/panda/protocol/http/MessageParser.rl"
	{SAVE(response->message)}
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st16;
tr29:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st16;
tr31:
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st16;
tr55:
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            cs = message_parser_error;
            set_error(errc::unsupported_compression);
            {p++; cs = 16; goto _out;}
        }
    }
#line 83 "src/panda/protocol/http/MessageParser.rl"
	{
        if (message->compressed != compression::IDENTITY) {
            rx_compressor = compressors[static_cast<int>(message->compressed)];
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st16;
tr63:
#line 72 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            if (message->compressed == compression::IDENTITY) { message->compressed = compression::DEFLATE; }
            else {
                cs = message_parser_error;
                set_error(errc::unsupported_compression);
                {p++; cs = 16; goto _out;}
            }
        }
    }
#line 83 "src/panda/protocol/http/MessageParser.rl"
	{
        if (message->compressed != compression::IDENTITY) {
            rx_compressor = compressors[static_cast<int>(message->compressed)];
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st16;
tr66:
#line 83 "src/panda/protocol/http/MessageParser.rl"
	{
        if (message->compressed != compression::IDENTITY) {
            rx_compressor = compressors[static_cast<int>(message->compressed)];
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st16;
tr75:
#line 61 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            if (message->compressed == compression::IDENTITY) { message->compressed = compression::GZIP; }
            else {
                cs = message_parser_error;
                set_error(errc::unsupported_compression);
                {p++; cs = 16; goto _out;}
            }
        }
    }
#line 83 "src/panda/protocol/http/MessageParser.rl"
	{
        if (message->compressed != compression::IDENTITY) {
            rx_compressor = compressors[static_cast<int>(message->compressed)];
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st16;
tr113:
#line 47 "src/panda/protocol/http/MessageParser.rl"
	{
        cs = message_parser_error;
        set_error(errc::unsupported_transfer_encoding);
        {p++; cs = 16; goto _out;}
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st16;
tr121:
#line 124 "src/panda/protocol/http/MessageParser.rl"
	{message->chunked = true;                     }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 423 "src/panda/protocol/http/MessageParser.cc"
	if ( (*p) == 10 )
		goto st17;
	goto st0;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	switch( (*p) ) {
		case 13: goto st18;
		case 33: goto tr21;
		case 67: goto tr22;
		case 84: goto tr23;
		case 99: goto tr22;
		case 116: goto tr23;
		case 124: goto tr21;
		case 126: goto tr21;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr21;
		} else if ( (*p) >= 35 )
			goto tr21;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr21;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr21;
		} else
			goto tr21;
	} else
		goto tr21;
	goto st0;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	if ( (*p) == 10 )
		goto tr24;
	goto st0;
tr24:
#line 16 "src/panda/protocol/http/MessageParser.rl"
	{
        {p++; cs = 316; goto _out;}
    }
	goto st316;
st316:
	if ( ++p == pe )
		goto _test_eof316;
case 316:
#line 476 "src/panda/protocol/http/MessageParser.cc"
	goto st0;
tr21:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 489 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
tr26:
#line 20 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 533 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st20;
		case 13: goto tr29;
		case 32: goto st20;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr27;
tr27:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 554 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr31;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
tr22:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
#line 576 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 79: goto st23;
		case 111: goto st23;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 78: goto st24;
		case 110: goto st24;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 84: goto st25;
		case 116: goto st25;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 69: goto st26;
		case 101: goto st26;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 78: goto st27;
		case 110: goto st27;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 84: goto st28;
		case 116: goto st28;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 33: goto st19;
		case 45: goto st29;
		case 46: goto st19;
		case 58: goto tr26;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else if ( (*p) >= 65 )
			goto st19;
	} else
		goto st19;
	goto st0;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 69: goto st30;
		case 76: goto st60;
		case 101: goto st30;
		case 108: goto st60;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 78: goto st31;
		case 110: goto st31;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 67: goto st32;
		case 99: goto st32;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 79: goto st33;
		case 111: goto st33;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 68: goto st34;
		case 100: goto st34;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 73: goto st35;
		case 105: goto st35;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 78: goto st36;
		case 110: goto st36;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 71: goto st37;
		case 103: goto st37;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr48;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
tr48:
#line 20 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st38;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
#line 1069 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st38;
		case 13: goto tr29;
		case 32: goto st38;
		case 100: goto tr51;
		case 103: goto tr52;
		case 105: goto tr53;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr49;
tr49:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st39;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
#line 1093 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr55;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
tr51:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st40;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
#line 1115 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr55;
		case 101: goto st41;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 13: goto tr55;
		case 102: goto st42;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 13: goto tr55;
		case 108: goto st43;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 13: goto tr55;
		case 97: goto st44;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 13: goto tr55;
		case 116: goto st45;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	switch( (*p) ) {
		case 13: goto tr55;
		case 101: goto st46;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	switch( (*p) ) {
		case 9: goto tr62;
		case 13: goto tr63;
		case 32: goto tr62;
		case 44: goto tr64;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st39;
tr62:
#line 72 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            if (message->compressed == compression::IDENTITY) { message->compressed = compression::DEFLATE; }
            else {
                cs = message_parser_error;
                set_error(errc::unsupported_compression);
                {p++; cs = 47; goto _out;}
            }
        }
    }
	goto st47;
tr74:
#line 61 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            if (message->compressed == compression::IDENTITY) { message->compressed = compression::GZIP; }
            else {
                cs = message_parser_error;
                set_error(errc::unsupported_compression);
                {p++; cs = 47; goto _out;}
            }
        }
    }
	goto st47;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
#line 1246 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st47;
		case 13: goto tr66;
		case 32: goto st47;
		case 44: goto st48;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st39;
tr64:
#line 72 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            if (message->compressed == compression::IDENTITY) { message->compressed = compression::DEFLATE; }
            else {
                cs = message_parser_error;
                set_error(errc::unsupported_compression);
                {p++; cs = 48; goto _out;}
            }
        }
    }
	goto st48;
tr76:
#line 61 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            if (message->compressed == compression::IDENTITY) { message->compressed = compression::GZIP; }
            else {
                cs = message_parser_error;
                set_error(errc::unsupported_compression);
                {p++; cs = 48; goto _out;}
            }
        }
    }
	goto st48;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
#line 1287 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st48;
		case 13: goto tr55;
		case 32: goto st48;
		case 100: goto st40;
		case 103: goto st49;
		case 105: goto st53;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st39;
tr52:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st49;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
#line 1311 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr55;
		case 122: goto st50;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	switch( (*p) ) {
		case 13: goto tr55;
		case 105: goto st51;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 13: goto tr55;
		case 112: goto st52;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	switch( (*p) ) {
		case 9: goto tr74;
		case 13: goto tr75;
		case 32: goto tr74;
		case 44: goto tr76;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st39;
tr53:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st53;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
#line 1378 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr55;
		case 100: goto st54;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 13: goto tr55;
		case 101: goto st55;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 13: goto tr55;
		case 110: goto st56;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 13: goto tr55;
		case 116: goto st57;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 13: goto tr55;
		case 105: goto st58;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 13: goto tr55;
		case 116: goto st59;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 13: goto tr55;
		case 121: goto st47;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st39;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 69: goto st61;
		case 101: goto st61;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 78: goto st62;
		case 110: goto st62;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 71: goto st63;
		case 103: goto st63;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 84: goto st64;
		case 116: goto st64;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 72: goto st65;
		case 104: goto st65;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr88;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
tr88:
#line 20 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st66;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
#line 1677 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st66;
		case 13: goto tr29;
		case 32: goto st66;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr90;
	} else if ( (*p) >= 0 )
		goto st0;
	goto tr27;
tr90:
#line 38 "src/panda/protocol/http/MessageParser.rl"
	{
        if (has_content_length) {
            cs = message_parser_error;
            set_error(errc::multiple_content_length);
            {p++; cs = 67; goto _out;}
        }
        has_content_length = true;
    }
#line 123 "src/panda/protocol/http/MessageParser.rl"
	{ADD_DIGIT(content_length)}
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st67;
tr91:
#line 123 "src/panda/protocol/http/MessageParser.rl"
	{ADD_DIGIT(content_length)}
	goto st67;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
#line 1716 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr31;
		case 127: goto st0;
	}
	if ( (*p) < 10 ) {
		if ( 0 <= (*p) && (*p) <= 8 )
			goto st0;
	} else if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr91;
	} else
		goto st0;
	goto st21;
tr23:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st68;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
#line 1741 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 82: goto st69;
		case 114: goto st69;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 65: goto st70;
		case 97: goto st70;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 66 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 78: goto st71;
		case 110: goto st71;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 83: goto st72;
		case 115: goto st72;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 70: goto st73;
		case 102: goto st73;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 69: goto st74;
		case 101: goto st74;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 82: goto st75;
		case 114: goto st75;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	switch( (*p) ) {
		case 33: goto st19;
		case 45: goto st76;
		case 46: goto st19;
		case 58: goto tr26;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else if ( (*p) >= 65 )
			goto st19;
	} else
		goto st19;
	goto st0;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 69: goto st77;
		case 101: goto st77;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 78: goto st78;
		case 110: goto st78;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 67: goto st79;
		case 99: goto st79;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 79: goto st80;
		case 111: goto st80;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 68: goto st81;
		case 100: goto st81;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 73: goto st82;
		case 105: goto st82;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 78: goto st83;
		case 110: goto st83;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 71: goto st84;
		case 103: goto st84;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr108;
		case 124: goto st19;
		case 126: goto st19;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st19;
		} else if ( (*p) >= 35 )
			goto st19;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st19;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st19;
		} else
			goto st19;
	} else
		goto st19;
	goto st0;
tr108:
#line 20 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st85;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
#line 2262 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st85;
		case 13: goto tr29;
		case 32: goto st85;
		case 67: goto tr111;
		case 99: goto tr111;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr109;
tr109:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st86;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
#line 2285 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr113;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st86;
tr111:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st87;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
#line 2307 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr113;
		case 72: goto st88;
		case 104: goto st88;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st86;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	switch( (*p) ) {
		case 13: goto tr113;
		case 85: goto st89;
		case 117: goto st89;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st86;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	switch( (*p) ) {
		case 13: goto tr113;
		case 78: goto st90;
		case 110: goto st90;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st86;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	switch( (*p) ) {
		case 13: goto tr113;
		case 75: goto st91;
		case 107: goto st91;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st86;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	switch( (*p) ) {
		case 13: goto tr113;
		case 69: goto st92;
		case 101: goto st92;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st86;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	switch( (*p) ) {
		case 13: goto tr113;
		case 68: goto st93;
		case 100: goto st93;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st86;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	switch( (*p) ) {
		case 9: goto tr120;
		case 13: goto tr121;
		case 32: goto tr120;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st86;
tr120:
#line 124 "src/panda/protocol/http/MessageParser.rl"
	{message->chunked = true;                     }
	goto st94;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
#line 2421 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st94;
		case 13: goto tr31;
		case 32: goto st94;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st86;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	if ( (*p) == 32 )
		goto tr123;
	goto st0;
case 96:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr124;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr124;
	} else
		goto tr124;
	goto st0;
tr124:
#line 136 "src/panda/protocol/http/MessageParser.rl"
	{chunk_length = 0;}
#line 136 "src/panda/protocol/http/MessageParser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st97;
tr126:
#line 136 "src/panda/protocol/http/MessageParser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st97;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
#line 2462 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto st98;
		case 59: goto st99;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr126;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr126;
	} else
		goto tr126;
	goto st0;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	if ( (*p) == 10 )
		goto tr128;
	goto st0;
tr128:
#line 16 "src/panda/protocol/http/MessageParser.rl"
	{
        {p++; cs = 317; goto _out;}
    }
	goto st317;
st317:
	if ( ++p == pe )
		goto _test_eof317;
case 317:
#line 2493 "src/panda/protocol/http/MessageParser.cc"
	goto st0;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	switch( (*p) ) {
		case 33: goto st100;
		case 124: goto st100;
		case 126: goto st100;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st100;
		} else if ( (*p) >= 35 )
			goto st100;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st100;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st100;
		} else
			goto st100;
	} else
		goto st100;
	goto st0;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	switch( (*p) ) {
		case 13: goto st98;
		case 33: goto st100;
		case 59: goto st99;
		case 61: goto st101;
		case 124: goto st100;
		case 126: goto st100;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st100;
		} else if ( (*p) >= 35 )
			goto st100;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st100;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st100;
		} else
			goto st100;
	} else
		goto st100;
	goto st0;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
	switch( (*p) ) {
		case 34: goto st103;
		case 124: goto st102;
		case 126: goto st102;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st102;
		} else if ( (*p) >= 33 )
			goto st102;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st102;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st102;
		} else
			goto st102;
	} else
		goto st102;
	goto st0;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	switch( (*p) ) {
		case 13: goto st98;
		case 33: goto st102;
		case 59: goto st99;
		case 124: goto st102;
		case 126: goto st102;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st102;
		} else if ( (*p) >= 35 )
			goto st102;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st102;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st102;
		} else
			goto st102;
	} else
		goto st102;
	goto st0;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
	switch( (*p) ) {
		case 34: goto st104;
		case 92: goto st105;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st103;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	switch( (*p) ) {
		case 13: goto st98;
		case 59: goto st99;
	}
	goto st0;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
	if ( (*p) == 127 )
		goto st0;
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st103;
case 106:
	if ( (*p) == 13 )
		goto st107;
	goto st0;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
	if ( (*p) == 10 )
		goto st108;
	goto st0;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr137;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr137;
	} else
		goto tr137;
	goto st0;
tr137:
#line 136 "src/panda/protocol/http/MessageParser.rl"
	{chunk_length = 0;}
#line 136 "src/panda/protocol/http/MessageParser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st109;
tr139:
#line 136 "src/panda/protocol/http/MessageParser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st109;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
#line 2682 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto st110;
		case 59: goto st111;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr139;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr139;
	} else
		goto tr139;
	goto st0;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
	if ( (*p) == 10 )
		goto tr141;
	goto st0;
tr141:
#line 16 "src/panda/protocol/http/MessageParser.rl"
	{
        {p++; cs = 318; goto _out;}
    }
	goto st318;
st318:
	if ( ++p == pe )
		goto _test_eof318;
case 318:
#line 2713 "src/panda/protocol/http/MessageParser.cc"
	goto st0;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	switch( (*p) ) {
		case 33: goto st112;
		case 124: goto st112;
		case 126: goto st112;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st112;
		} else if ( (*p) >= 35 )
			goto st112;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st112;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st112;
		} else
			goto st112;
	} else
		goto st112;
	goto st0;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	switch( (*p) ) {
		case 13: goto st110;
		case 33: goto st112;
		case 59: goto st111;
		case 61: goto st113;
		case 124: goto st112;
		case 126: goto st112;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st112;
		} else if ( (*p) >= 35 )
			goto st112;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st112;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st112;
		} else
			goto st112;
	} else
		goto st112;
	goto st0;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
	switch( (*p) ) {
		case 34: goto st115;
		case 124: goto st114;
		case 126: goto st114;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st114;
		} else if ( (*p) >= 33 )
			goto st114;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st114;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st114;
		} else
			goto st114;
	} else
		goto st114;
	goto st0;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	switch( (*p) ) {
		case 13: goto st110;
		case 33: goto st114;
		case 59: goto st111;
		case 124: goto st114;
		case 126: goto st114;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st114;
		} else if ( (*p) >= 35 )
			goto st114;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st114;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st114;
		} else
			goto st114;
	} else
		goto st114;
	goto st0;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
	switch( (*p) ) {
		case 34: goto st116;
		case 92: goto st117;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st115;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
	switch( (*p) ) {
		case 13: goto st110;
		case 59: goto st111;
	}
	goto st0;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
	if ( (*p) == 127 )
		goto st0;
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st115;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
	switch( (*p) ) {
		case 13: goto st119;
		case 33: goto tr149;
		case 124: goto tr149;
		case 126: goto tr149;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr149;
		} else if ( (*p) >= 35 )
			goto tr149;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr149;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr149;
		} else
			goto tr149;
	} else
		goto tr149;
	goto st0;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
	if ( (*p) == 10 )
		goto tr150;
	goto st0;
tr150:
#line 16 "src/panda/protocol/http/MessageParser.rl"
	{
        {p++; cs = 319; goto _out;}
    }
	goto st319;
st319:
	if ( ++p == pe )
		goto _test_eof319;
case 319:
#line 2909 "src/panda/protocol/http/MessageParser.cc"
	goto st0;
tr149:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st120;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
#line 2922 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st120;
		case 58: goto tr152;
		case 124: goto st120;
		case 126: goto st120;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st120;
		} else if ( (*p) >= 35 )
			goto st120;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st120;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st120;
		} else
			goto st120;
	} else
		goto st120;
	goto st0;
tr152:
#line 20 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st121;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
#line 2966 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st121;
		case 13: goto tr155;
		case 32: goto st121;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr153;
tr153:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st122;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
#line 2987 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr157;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st122;
tr155:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st123;
tr157:
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st123;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
#line 3037 "src/panda/protocol/http/MessageParser.cc"
	if ( (*p) == 10 )
		goto st118;
	goto st0;
case 124:
	switch( (*p) ) {
		case 67: goto st125;
		case 68: goto st285;
		case 71: goto st291;
		case 72: goto st294;
		case 79: goto st298;
		case 80: goto st305;
		case 84: goto st311;
	}
	goto st0;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
	if ( (*p) == 79 )
		goto st126;
	goto st0;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
	if ( (*p) == 78 )
		goto st127;
	goto st0;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
	if ( (*p) == 78 )
		goto st128;
	goto st0;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
	if ( (*p) == 69 )
		goto st129;
	goto st0;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
	if ( (*p) == 67 )
		goto st130;
	goto st0;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
	if ( (*p) == 84 )
		goto st131;
	goto st0;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
	if ( (*p) == 32 )
		goto tr172;
	goto st0;
tr172:
#line 153 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::CONNECT; }
	goto st132;
tr384:
#line 151 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::DELETE; }
	goto st132;
tr387:
#line 147 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::GET; }
	goto st132;
tr391:
#line 148 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::HEAD; }
	goto st132;
tr398:
#line 146 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::OPTIONS; }
	goto st132;
tr403:
#line 149 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::POST; }
	goto st132;
tr405:
#line 150 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::PUT; }
	goto st132;
tr410:
#line 152 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::TRACE; }
	goto st132;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
#line 3137 "src/panda/protocol/http/MessageParser.cc"
	if ( 33 <= (*p) && (*p) <= 126 )
		goto tr173;
	goto st0;
tr173:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st133;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
#line 3152 "src/panda/protocol/http/MessageParser.cc"
	if ( (*p) == 32 )
		goto tr174;
	if ( 33 <= (*p) && (*p) <= 126 )
		goto st133;
	goto st0;
tr174:
#line 89 "src/panda/protocol/http/MessageParser.rl"
	{
        string target;
        SAVE(target);
        request->uri = new URI(target);
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st134;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
#line 3174 "src/panda/protocol/http/MessageParser.cc"
	if ( (*p) == 72 )
		goto st135;
	goto st0;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
	if ( (*p) == 84 )
		goto st136;
	goto st0;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
	if ( (*p) == 84 )
		goto st137;
	goto st0;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
	if ( (*p) == 80 )
		goto st138;
	goto st0;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
	if ( (*p) == 47 )
		goto st139;
	goto st0;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
	if ( (*p) == 49 )
		goto st140;
	goto st0;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
	if ( (*p) == 46 )
		goto st141;
	goto st0;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
	switch( (*p) ) {
		case 48: goto st142;
		case 49: goto st284;
	}
	goto st0;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
	if ( (*p) == 13 )
		goto tr185;
	goto st0;
tr185:
#line 102 "src/panda/protocol/http/MessageParser.rl"
	{message->http_version = 10;}
	goto st143;
tr197:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
tr199:
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
tr310:
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            cs = message_parser_error;
            set_error(errc::unsupported_compression);
            {p++; cs = 143; goto _out;}
        }
    }
#line 83 "src/panda/protocol/http/MessageParser.rl"
	{
        if (message->compressed != compression::IDENTITY) {
            rx_compressor = compressors[static_cast<int>(message->compressed)];
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
tr318:
#line 72 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            if (message->compressed == compression::IDENTITY) { message->compressed = compression::DEFLATE; }
            else {
                cs = message_parser_error;
                set_error(errc::unsupported_compression);
                {p++; cs = 143; goto _out;}
            }
        }
    }
#line 83 "src/panda/protocol/http/MessageParser.rl"
	{
        if (message->compressed != compression::IDENTITY) {
            rx_compressor = compressors[static_cast<int>(message->compressed)];
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
tr321:
#line 83 "src/panda/protocol/http/MessageParser.rl"
	{
        if (message->compressed != compression::IDENTITY) {
            rx_compressor = compressors[static_cast<int>(message->compressed)];
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
tr330:
#line 61 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            if (message->compressed == compression::IDENTITY) { message->compressed = compression::GZIP; }
            else {
                cs = message_parser_error;
                set_error(errc::unsupported_compression);
                {p++; cs = 143; goto _out;}
            }
        }
    }
#line 83 "src/panda/protocol/http/MessageParser.rl"
	{
        if (message->compressed != compression::IDENTITY) {
            rx_compressor = compressors[static_cast<int>(message->compressed)];
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
tr368:
#line 47 "src/panda/protocol/http/MessageParser.rl"
	{
        cs = message_parser_error;
        set_error(errc::unsupported_transfer_encoding);
        {p++; cs = 143; goto _out;}
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
tr376:
#line 124 "src/panda/protocol/http/MessageParser.rl"
	{message->chunked = true;                     }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
tr378:
#line 102 "src/panda/protocol/http/MessageParser.rl"
	{message->http_version = 11;}
	goto st143;
tr223:
#line 110 "src/panda/protocol/http/MessageParser.rl"
	{compr = compression::GZIP | compression::DEFLATE; }
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
tr237:
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
tr244:
#line 112 "src/panda/protocol/http/MessageParser.rl"
	{ compr = 0; }
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
tr271:
#line 106 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::DEFLATE;  }
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
tr278:
#line 105 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::GZIP;     }
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
#line 29 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st143;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
#line 3553 "src/panda/protocol/http/MessageParser.cc"
	if ( (*p) == 10 )
		goto st144;
	goto st0;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
	switch( (*p) ) {
		case 13: goto st145;
		case 33: goto tr188;
		case 65: goto tr189;
		case 67: goto tr190;
		case 84: goto tr191;
		case 97: goto tr189;
		case 99: goto tr190;
		case 116: goto tr191;
		case 124: goto tr188;
		case 126: goto tr188;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr188;
		} else if ( (*p) >= 35 )
			goto tr188;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 66 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr188;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr188;
		} else
			goto tr188;
	} else
		goto tr188;
	goto st0;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
	if ( (*p) == 10 )
		goto tr192;
	goto st0;
tr192:
#line 16 "src/panda/protocol/http/MessageParser.rl"
	{
        {p++; cs = 320; goto _out;}
    }
	goto st320;
st320:
	if ( ++p == pe )
		goto _test_eof320;
case 320:
#line 3608 "src/panda/protocol/http/MessageParser.cc"
	goto st0;
tr188:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st146;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
#line 3621 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
tr194:
#line 20 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st147;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
#line 3665 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st147;
		case 13: goto tr197;
		case 32: goto st147;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr195;
tr195:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st148;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
#line 3686 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr199;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
tr189:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st149;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
#line 3708 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 67: goto st150;
		case 99: goto st150;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 67: goto st151;
		case 99: goto st151;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 69: goto st152;
		case 101: goto st152;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 80: goto st153;
		case 112: goto st153;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 84: goto st154;
		case 116: goto st154;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
	switch( (*p) ) {
		case 33: goto st146;
		case 45: goto st155;
		case 46: goto st146;
		case 58: goto tr194;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else if ( (*p) >= 65 )
			goto st146;
	} else
		goto st146;
	goto st0;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 69: goto st156;
		case 101: goto st156;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 78: goto st157;
		case 110: goto st157;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 67: goto st158;
		case 99: goto st158;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 79: goto st159;
		case 111: goto st159;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 68: goto st160;
		case 100: goto st160;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st160:
	if ( ++p == pe )
		goto _test_eof160;
case 160:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 73: goto st161;
		case 105: goto st161;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st161:
	if ( ++p == pe )
		goto _test_eof161;
case 161:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 78: goto st162;
		case 110: goto st162;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st162:
	if ( ++p == pe )
		goto _test_eof162;
case 162:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 71: goto st163;
		case 103: goto st163;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st163:
	if ( ++p == pe )
		goto _test_eof163;
case 163:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr214;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
tr214:
#line 20 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st164;
st164:
	if ( ++p == pe )
		goto _test_eof164;
case 164:
#line 4169 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st164;
		case 13: goto tr197;
		case 32: goto st164;
		case 42: goto tr216;
		case 98: goto tr217;
		case 99: goto tr218;
		case 100: goto tr219;
		case 103: goto tr220;
		case 105: goto tr221;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr195;
tr216:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st165;
st165:
	if ( ++p == pe )
		goto _test_eof165;
case 165:
#line 4196 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto tr222;
		case 13: goto tr223;
		case 32: goto tr222;
		case 44: goto tr224;
		case 59: goto tr225;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
tr222:
#line 110 "src/panda/protocol/http/MessageParser.rl"
	{compr = compression::GZIP | compression::DEFLATE; }
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st166;
tr236:
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st166;
tr270:
#line 106 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::DEFLATE;  }
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st166;
tr277:
#line 105 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::GZIP;     }
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st166;
st166:
	if ( ++p == pe )
		goto _test_eof166;
case 166:
#line 4254 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st166;
		case 13: goto tr199;
		case 32: goto st166;
		case 44: goto st167;
		case 59: goto st170;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
tr224:
#line 110 "src/panda/protocol/http/MessageParser.rl"
	{compr = compression::GZIP | compression::DEFLATE; }
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st167;
tr238:
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st167;
tr245:
#line 112 "src/panda/protocol/http/MessageParser.rl"
	{ compr = 0; }
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st167;
tr272:
#line 106 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::DEFLATE;  }
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st167;
tr279:
#line 105 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::GZIP;     }
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st167;
st167:
	if ( ++p == pe )
		goto _test_eof167;
case 167:
#line 4323 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st167;
		case 13: goto tr199;
		case 32: goto st167;
		case 42: goto st165;
		case 98: goto st168;
		case 99: goto st186;
		case 100: goto st193;
		case 103: goto st200;
		case 105: goto st204;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
tr217:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st168;
st168:
	if ( ++p == pe )
		goto _test_eof168;
case 168:
#line 4350 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr199;
		case 114: goto st169;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st169:
	if ( ++p == pe )
		goto _test_eof169;
case 169:
	switch( (*p) ) {
		case 9: goto tr236;
		case 13: goto tr237;
		case 32: goto tr236;
		case 44: goto tr238;
		case 59: goto st170;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
tr225:
#line 110 "src/panda/protocol/http/MessageParser.rl"
	{compr = compression::GZIP | compression::DEFLATE; }
	goto st170;
tr273:
#line 106 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::DEFLATE;  }
	goto st170;
tr280:
#line 105 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::GZIP;     }
	goto st170;
st170:
	if ( ++p == pe )
		goto _test_eof170;
case 170:
#line 4393 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st170;
		case 13: goto tr199;
		case 32: goto st170;
		case 113: goto st171;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
st171:
	if ( ++p == pe )
		goto _test_eof171;
case 171:
	switch( (*p) ) {
		case 13: goto tr199;
		case 61: goto st172;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st172:
	if ( ++p == pe )
		goto _test_eof172;
case 172:
	switch( (*p) ) {
		case 13: goto tr199;
		case 48: goto st173;
		case 49: goto st182;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st173:
	if ( ++p == pe )
		goto _test_eof173;
case 173:
	switch( (*p) ) {
		case 9: goto tr243;
		case 13: goto tr244;
		case 32: goto tr243;
		case 44: goto tr245;
		case 46: goto st175;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
tr254:
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st174;
tr243:
#line 112 "src/panda/protocol/http/MessageParser.rl"
	{ compr = 0; }
#line 95 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st174;
st174:
	if ( ++p == pe )
		goto _test_eof174;
case 174:
#line 4474 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st174;
		case 13: goto tr199;
		case 32: goto st174;
		case 44: goto st167;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
st175:
	if ( ++p == pe )
		goto _test_eof175;
case 175:
	switch( (*p) ) {
		case 9: goto tr243;
		case 13: goto tr244;
		case 32: goto tr243;
		case 44: goto tr245;
		case 48: goto st176;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st181;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st176:
	if ( ++p == pe )
		goto _test_eof176;
case 176:
	switch( (*p) ) {
		case 9: goto tr243;
		case 13: goto tr244;
		case 32: goto tr243;
		case 44: goto tr245;
		case 48: goto st177;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st180;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st177:
	if ( ++p == pe )
		goto _test_eof177;
case 177:
	switch( (*p) ) {
		case 9: goto tr243;
		case 13: goto tr244;
		case 32: goto tr243;
		case 44: goto tr245;
		case 48: goto st178;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st179;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st178:
	if ( ++p == pe )
		goto _test_eof178;
case 178:
	switch( (*p) ) {
		case 9: goto tr243;
		case 13: goto tr244;
		case 32: goto tr243;
		case 44: goto tr245;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
st179:
	if ( ++p == pe )
		goto _test_eof179;
case 179:
	switch( (*p) ) {
		case 9: goto tr254;
		case 13: goto tr237;
		case 32: goto tr254;
		case 44: goto tr238;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
st180:
	if ( ++p == pe )
		goto _test_eof180;
case 180:
	switch( (*p) ) {
		case 9: goto tr254;
		case 13: goto tr237;
		case 32: goto tr254;
		case 44: goto tr238;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st179;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st181:
	if ( ++p == pe )
		goto _test_eof181;
case 181:
	switch( (*p) ) {
		case 9: goto tr254;
		case 13: goto tr237;
		case 32: goto tr254;
		case 44: goto tr238;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st180;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st182:
	if ( ++p == pe )
		goto _test_eof182;
case 182:
	switch( (*p) ) {
		case 9: goto tr254;
		case 13: goto tr237;
		case 32: goto tr254;
		case 44: goto tr238;
		case 46: goto st183;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
st183:
	if ( ++p == pe )
		goto _test_eof183;
case 183:
	switch( (*p) ) {
		case 9: goto tr254;
		case 13: goto tr237;
		case 32: goto tr254;
		case 44: goto tr238;
		case 48: goto st184;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
st184:
	if ( ++p == pe )
		goto _test_eof184;
case 184:
	switch( (*p) ) {
		case 9: goto tr254;
		case 13: goto tr237;
		case 32: goto tr254;
		case 44: goto tr238;
		case 48: goto st185;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
st185:
	if ( ++p == pe )
		goto _test_eof185;
case 185:
	switch( (*p) ) {
		case 9: goto tr254;
		case 13: goto tr237;
		case 32: goto tr254;
		case 44: goto tr238;
		case 48: goto st179;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
tr218:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st186;
st186:
	if ( ++p == pe )
		goto _test_eof186;
case 186:
#line 4672 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr199;
		case 111: goto st187;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st187:
	if ( ++p == pe )
		goto _test_eof187;
case 187:
	switch( (*p) ) {
		case 13: goto tr199;
		case 109: goto st188;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st188:
	if ( ++p == pe )
		goto _test_eof188;
case 188:
	switch( (*p) ) {
		case 13: goto tr199;
		case 112: goto st189;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st189:
	if ( ++p == pe )
		goto _test_eof189;
case 189:
	switch( (*p) ) {
		case 13: goto tr199;
		case 114: goto st190;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st190:
	if ( ++p == pe )
		goto _test_eof190;
case 190:
	switch( (*p) ) {
		case 13: goto tr199;
		case 101: goto st191;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st191:
	if ( ++p == pe )
		goto _test_eof191;
case 191:
	switch( (*p) ) {
		case 13: goto tr199;
		case 115: goto st192;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st192:
	if ( ++p == pe )
		goto _test_eof192;
case 192:
	switch( (*p) ) {
		case 13: goto tr199;
		case 115: goto st169;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
tr219:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st193;
st193:
	if ( ++p == pe )
		goto _test_eof193;
case 193:
#line 4785 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr199;
		case 101: goto st194;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st194:
	if ( ++p == pe )
		goto _test_eof194;
case 194:
	switch( (*p) ) {
		case 13: goto tr199;
		case 102: goto st195;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st195:
	if ( ++p == pe )
		goto _test_eof195;
case 195:
	switch( (*p) ) {
		case 13: goto tr199;
		case 108: goto st196;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st196:
	if ( ++p == pe )
		goto _test_eof196;
case 196:
	switch( (*p) ) {
		case 13: goto tr199;
		case 97: goto st197;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st197:
	if ( ++p == pe )
		goto _test_eof197;
case 197:
	switch( (*p) ) {
		case 13: goto tr199;
		case 116: goto st198;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st198:
	if ( ++p == pe )
		goto _test_eof198;
case 198:
	switch( (*p) ) {
		case 13: goto tr199;
		case 101: goto st199;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st199:
	if ( ++p == pe )
		goto _test_eof199;
case 199:
	switch( (*p) ) {
		case 9: goto tr270;
		case 13: goto tr271;
		case 32: goto tr270;
		case 44: goto tr272;
		case 59: goto tr273;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
tr220:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st200;
st200:
	if ( ++p == pe )
		goto _test_eof200;
case 200:
#line 4898 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr199;
		case 122: goto st201;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st201:
	if ( ++p == pe )
		goto _test_eof201;
case 201:
	switch( (*p) ) {
		case 13: goto tr199;
		case 105: goto st202;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st202:
	if ( ++p == pe )
		goto _test_eof202;
case 202:
	switch( (*p) ) {
		case 13: goto tr199;
		case 112: goto st203;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st203:
	if ( ++p == pe )
		goto _test_eof203;
case 203:
	switch( (*p) ) {
		case 9: goto tr277;
		case 13: goto tr278;
		case 32: goto tr277;
		case 44: goto tr279;
		case 59: goto tr280;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st148;
tr221:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st204;
st204:
	if ( ++p == pe )
		goto _test_eof204;
case 204:
#line 4966 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr199;
		case 100: goto st205;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st205:
	if ( ++p == pe )
		goto _test_eof205;
case 205:
	switch( (*p) ) {
		case 13: goto tr199;
		case 101: goto st206;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st206:
	if ( ++p == pe )
		goto _test_eof206;
case 206:
	switch( (*p) ) {
		case 13: goto tr199;
		case 110: goto st207;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st207:
	if ( ++p == pe )
		goto _test_eof207;
case 207:
	switch( (*p) ) {
		case 13: goto tr199;
		case 116: goto st208;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st208:
	if ( ++p == pe )
		goto _test_eof208;
case 208:
	switch( (*p) ) {
		case 13: goto tr199;
		case 105: goto st209;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st209:
	if ( ++p == pe )
		goto _test_eof209;
case 209:
	switch( (*p) ) {
		case 13: goto tr199;
		case 116: goto st210;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
st210:
	if ( ++p == pe )
		goto _test_eof210;
case 210:
	switch( (*p) ) {
		case 13: goto tr199;
		case 121: goto st169;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st148;
tr190:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st211;
st211:
	if ( ++p == pe )
		goto _test_eof211;
case 211:
#line 5079 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 79: goto st212;
		case 111: goto st212;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st212:
	if ( ++p == pe )
		goto _test_eof212;
case 212:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 78: goto st213;
		case 110: goto st213;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st213:
	if ( ++p == pe )
		goto _test_eof213;
case 213:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 84: goto st214;
		case 116: goto st214;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st214:
	if ( ++p == pe )
		goto _test_eof214;
case 214:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 69: goto st215;
		case 101: goto st215;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st215:
	if ( ++p == pe )
		goto _test_eof215;
case 215:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 78: goto st216;
		case 110: goto st216;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st216:
	if ( ++p == pe )
		goto _test_eof216;
case 216:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 84: goto st217;
		case 116: goto st217;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st217:
	if ( ++p == pe )
		goto _test_eof217;
case 217:
	switch( (*p) ) {
		case 33: goto st146;
		case 45: goto st218;
		case 46: goto st146;
		case 58: goto tr194;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else if ( (*p) >= 65 )
			goto st146;
	} else
		goto st146;
	goto st0;
st218:
	if ( ++p == pe )
		goto _test_eof218;
case 218:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 69: goto st219;
		case 76: goto st249;
		case 101: goto st219;
		case 108: goto st249;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st219:
	if ( ++p == pe )
		goto _test_eof219;
case 219:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 78: goto st220;
		case 110: goto st220;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st220:
	if ( ++p == pe )
		goto _test_eof220;
case 220:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 67: goto st221;
		case 99: goto st221;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st221:
	if ( ++p == pe )
		goto _test_eof221;
case 221:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 79: goto st222;
		case 111: goto st222;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st222:
	if ( ++p == pe )
		goto _test_eof222;
case 222:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 68: goto st223;
		case 100: goto st223;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st223:
	if ( ++p == pe )
		goto _test_eof223;
case 223:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 73: goto st224;
		case 105: goto st224;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st224:
	if ( ++p == pe )
		goto _test_eof224;
case 224:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 78: goto st225;
		case 110: goto st225;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st225:
	if ( ++p == pe )
		goto _test_eof225;
case 225:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 71: goto st226;
		case 103: goto st226;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st226:
	if ( ++p == pe )
		goto _test_eof226;
case 226:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr303;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
tr303:
#line 20 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st227;
st227:
	if ( ++p == pe )
		goto _test_eof227;
case 227:
#line 5572 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st227;
		case 13: goto tr197;
		case 32: goto st227;
		case 100: goto tr306;
		case 103: goto tr307;
		case 105: goto tr308;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr304;
tr304:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st228;
st228:
	if ( ++p == pe )
		goto _test_eof228;
case 228:
#line 5596 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr310;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
tr306:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st229;
st229:
	if ( ++p == pe )
		goto _test_eof229;
case 229:
#line 5618 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr310;
		case 101: goto st230;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st230:
	if ( ++p == pe )
		goto _test_eof230;
case 230:
	switch( (*p) ) {
		case 13: goto tr310;
		case 102: goto st231;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st231:
	if ( ++p == pe )
		goto _test_eof231;
case 231:
	switch( (*p) ) {
		case 13: goto tr310;
		case 108: goto st232;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st232:
	if ( ++p == pe )
		goto _test_eof232;
case 232:
	switch( (*p) ) {
		case 13: goto tr310;
		case 97: goto st233;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st233:
	if ( ++p == pe )
		goto _test_eof233;
case 233:
	switch( (*p) ) {
		case 13: goto tr310;
		case 116: goto st234;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st234:
	if ( ++p == pe )
		goto _test_eof234;
case 234:
	switch( (*p) ) {
		case 13: goto tr310;
		case 101: goto st235;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st235:
	if ( ++p == pe )
		goto _test_eof235;
case 235:
	switch( (*p) ) {
		case 9: goto tr317;
		case 13: goto tr318;
		case 32: goto tr317;
		case 44: goto tr319;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st228;
tr317:
#line 72 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            if (message->compressed == compression::IDENTITY) { message->compressed = compression::DEFLATE; }
            else {
                cs = message_parser_error;
                set_error(errc::unsupported_compression);
                {p++; cs = 236; goto _out;}
            }
        }
    }
	goto st236;
tr329:
#line 61 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            if (message->compressed == compression::IDENTITY) { message->compressed = compression::GZIP; }
            else {
                cs = message_parser_error;
                set_error(errc::unsupported_compression);
                {p++; cs = 236; goto _out;}
            }
        }
    }
	goto st236;
st236:
	if ( ++p == pe )
		goto _test_eof236;
case 236:
#line 5749 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st236;
		case 13: goto tr321;
		case 32: goto st236;
		case 44: goto st237;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st228;
tr319:
#line 72 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            if (message->compressed == compression::IDENTITY) { message->compressed = compression::DEFLATE; }
            else {
                cs = message_parser_error;
                set_error(errc::unsupported_compression);
                {p++; cs = 237; goto _out;}
            }
        }
    }
	goto st237;
tr331:
#line 61 "src/panda/protocol/http/MessageParser.rl"
	{
        if (uncompress_content) {
            if (message->compressed == compression::IDENTITY) { message->compressed = compression::GZIP; }
            else {
                cs = message_parser_error;
                set_error(errc::unsupported_compression);
                {p++; cs = 237; goto _out;}
            }
        }
    }
	goto st237;
st237:
	if ( ++p == pe )
		goto _test_eof237;
case 237:
#line 5790 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st237;
		case 13: goto tr310;
		case 32: goto st237;
		case 100: goto st229;
		case 103: goto st238;
		case 105: goto st242;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st228;
tr307:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st238;
st238:
	if ( ++p == pe )
		goto _test_eof238;
case 238:
#line 5814 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr310;
		case 122: goto st239;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st239:
	if ( ++p == pe )
		goto _test_eof239;
case 239:
	switch( (*p) ) {
		case 13: goto tr310;
		case 105: goto st240;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st240:
	if ( ++p == pe )
		goto _test_eof240;
case 240:
	switch( (*p) ) {
		case 13: goto tr310;
		case 112: goto st241;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st241:
	if ( ++p == pe )
		goto _test_eof241;
case 241:
	switch( (*p) ) {
		case 9: goto tr329;
		case 13: goto tr330;
		case 32: goto tr329;
		case 44: goto tr331;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st228;
tr308:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st242;
st242:
	if ( ++p == pe )
		goto _test_eof242;
case 242:
#line 5881 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr310;
		case 100: goto st243;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st243:
	if ( ++p == pe )
		goto _test_eof243;
case 243:
	switch( (*p) ) {
		case 13: goto tr310;
		case 101: goto st244;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st244:
	if ( ++p == pe )
		goto _test_eof244;
case 244:
	switch( (*p) ) {
		case 13: goto tr310;
		case 110: goto st245;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st245:
	if ( ++p == pe )
		goto _test_eof245;
case 245:
	switch( (*p) ) {
		case 13: goto tr310;
		case 116: goto st246;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st246:
	if ( ++p == pe )
		goto _test_eof246;
case 246:
	switch( (*p) ) {
		case 13: goto tr310;
		case 105: goto st247;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st247:
	if ( ++p == pe )
		goto _test_eof247;
case 247:
	switch( (*p) ) {
		case 13: goto tr310;
		case 116: goto st248;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st248:
	if ( ++p == pe )
		goto _test_eof248;
case 248:
	switch( (*p) ) {
		case 13: goto tr310;
		case 121: goto st236;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st228;
st249:
	if ( ++p == pe )
		goto _test_eof249;
case 249:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 69: goto st250;
		case 101: goto st250;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st250:
	if ( ++p == pe )
		goto _test_eof250;
case 250:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 78: goto st251;
		case 110: goto st251;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st251:
	if ( ++p == pe )
		goto _test_eof251;
case 251:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 71: goto st252;
		case 103: goto st252;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st252:
	if ( ++p == pe )
		goto _test_eof252;
case 252:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 84: goto st253;
		case 116: goto st253;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st253:
	if ( ++p == pe )
		goto _test_eof253;
case 253:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 72: goto st254;
		case 104: goto st254;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st254:
	if ( ++p == pe )
		goto _test_eof254;
case 254:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr343;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
tr343:
#line 20 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st255;
st255:
	if ( ++p == pe )
		goto _test_eof255;
case 255:
#line 6180 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st255;
		case 13: goto tr197;
		case 32: goto st255;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr345;
	} else if ( (*p) >= 0 )
		goto st0;
	goto tr195;
tr345:
#line 38 "src/panda/protocol/http/MessageParser.rl"
	{
        if (has_content_length) {
            cs = message_parser_error;
            set_error(errc::multiple_content_length);
            {p++; cs = 256; goto _out;}
        }
        has_content_length = true;
    }
#line 123 "src/panda/protocol/http/MessageParser.rl"
	{ADD_DIGIT(content_length)}
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st256;
tr346:
#line 123 "src/panda/protocol/http/MessageParser.rl"
	{ADD_DIGIT(content_length)}
	goto st256;
st256:
	if ( ++p == pe )
		goto _test_eof256;
case 256:
#line 6219 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr199;
		case 127: goto st0;
	}
	if ( (*p) < 10 ) {
		if ( 0 <= (*p) && (*p) <= 8 )
			goto st0;
	} else if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr346;
	} else
		goto st0;
	goto st148;
tr191:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st257;
st257:
	if ( ++p == pe )
		goto _test_eof257;
case 257:
#line 6244 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 82: goto st258;
		case 114: goto st258;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st258:
	if ( ++p == pe )
		goto _test_eof258;
case 258:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 65: goto st259;
		case 97: goto st259;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 66 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st259:
	if ( ++p == pe )
		goto _test_eof259;
case 259:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 78: goto st260;
		case 110: goto st260;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st260:
	if ( ++p == pe )
		goto _test_eof260;
case 260:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 83: goto st261;
		case 115: goto st261;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st261:
	if ( ++p == pe )
		goto _test_eof261;
case 261:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 70: goto st262;
		case 102: goto st262;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st262:
	if ( ++p == pe )
		goto _test_eof262;
case 262:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 69: goto st263;
		case 101: goto st263;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st263:
	if ( ++p == pe )
		goto _test_eof263;
case 263:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 82: goto st264;
		case 114: goto st264;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st264:
	if ( ++p == pe )
		goto _test_eof264;
case 264:
	switch( (*p) ) {
		case 33: goto st146;
		case 45: goto st265;
		case 46: goto st146;
		case 58: goto tr194;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else if ( (*p) >= 65 )
			goto st146;
	} else
		goto st146;
	goto st0;
st265:
	if ( ++p == pe )
		goto _test_eof265;
case 265:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 69: goto st266;
		case 101: goto st266;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st266:
	if ( ++p == pe )
		goto _test_eof266;
case 266:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 78: goto st267;
		case 110: goto st267;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st267:
	if ( ++p == pe )
		goto _test_eof267;
case 267:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 67: goto st268;
		case 99: goto st268;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st268:
	if ( ++p == pe )
		goto _test_eof268;
case 268:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 79: goto st269;
		case 111: goto st269;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st269:
	if ( ++p == pe )
		goto _test_eof269;
case 269:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 68: goto st270;
		case 100: goto st270;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st270:
	if ( ++p == pe )
		goto _test_eof270;
case 270:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 73: goto st271;
		case 105: goto st271;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st271:
	if ( ++p == pe )
		goto _test_eof271;
case 271:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 78: goto st272;
		case 110: goto st272;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st272:
	if ( ++p == pe )
		goto _test_eof272;
case 272:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr194;
		case 71: goto st273;
		case 103: goto st273;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
st273:
	if ( ++p == pe )
		goto _test_eof273;
case 273:
	switch( (*p) ) {
		case 33: goto st146;
		case 58: goto tr363;
		case 124: goto st146;
		case 126: goto st146;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st146;
		} else if ( (*p) >= 35 )
			goto st146;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st146;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st146;
		} else
			goto st146;
	} else
		goto st146;
	goto st0;
tr363:
#line 20 "src/panda/protocol/http/MessageParser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st274;
st274:
	if ( ++p == pe )
		goto _test_eof274;
case 274:
#line 6765 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st274;
		case 13: goto tr197;
		case 32: goto st274;
		case 67: goto tr366;
		case 99: goto tr366;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr364;
tr364:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st275;
st275:
	if ( ++p == pe )
		goto _test_eof275;
case 275:
#line 6788 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr368;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st275;
tr366:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st276;
st276:
	if ( ++p == pe )
		goto _test_eof276;
case 276:
#line 6810 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr368;
		case 72: goto st277;
		case 104: goto st277;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st275;
st277:
	if ( ++p == pe )
		goto _test_eof277;
case 277:
	switch( (*p) ) {
		case 13: goto tr368;
		case 85: goto st278;
		case 117: goto st278;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st275;
st278:
	if ( ++p == pe )
		goto _test_eof278;
case 278:
	switch( (*p) ) {
		case 13: goto tr368;
		case 78: goto st279;
		case 110: goto st279;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st275;
st279:
	if ( ++p == pe )
		goto _test_eof279;
case 279:
	switch( (*p) ) {
		case 13: goto tr368;
		case 75: goto st280;
		case 107: goto st280;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st275;
st280:
	if ( ++p == pe )
		goto _test_eof280;
case 280:
	switch( (*p) ) {
		case 13: goto tr368;
		case 69: goto st281;
		case 101: goto st281;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st275;
st281:
	if ( ++p == pe )
		goto _test_eof281;
case 281:
	switch( (*p) ) {
		case 13: goto tr368;
		case 68: goto st282;
		case 100: goto st282;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st275;
st282:
	if ( ++p == pe )
		goto _test_eof282;
case 282:
	switch( (*p) ) {
		case 9: goto tr375;
		case 13: goto tr376;
		case 32: goto tr375;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st275;
tr375:
#line 124 "src/panda/protocol/http/MessageParser.rl"
	{message->chunked = true;                     }
	goto st283;
st283:
	if ( ++p == pe )
		goto _test_eof283;
case 283:
#line 6924 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st283;
		case 13: goto tr199;
		case 32: goto st283;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st275;
st284:
	if ( ++p == pe )
		goto _test_eof284;
case 284:
	if ( (*p) == 13 )
		goto tr378;
	goto st0;
st285:
	if ( ++p == pe )
		goto _test_eof285;
case 285:
	if ( (*p) == 69 )
		goto st286;
	goto st0;
st286:
	if ( ++p == pe )
		goto _test_eof286;
case 286:
	if ( (*p) == 76 )
		goto st287;
	goto st0;
st287:
	if ( ++p == pe )
		goto _test_eof287;
case 287:
	if ( (*p) == 69 )
		goto st288;
	goto st0;
st288:
	if ( ++p == pe )
		goto _test_eof288;
case 288:
	if ( (*p) == 84 )
		goto st289;
	goto st0;
st289:
	if ( ++p == pe )
		goto _test_eof289;
case 289:
	if ( (*p) == 69 )
		goto st290;
	goto st0;
st290:
	if ( ++p == pe )
		goto _test_eof290;
case 290:
	if ( (*p) == 32 )
		goto tr384;
	goto st0;
st291:
	if ( ++p == pe )
		goto _test_eof291;
case 291:
	if ( (*p) == 69 )
		goto st292;
	goto st0;
st292:
	if ( ++p == pe )
		goto _test_eof292;
case 292:
	if ( (*p) == 84 )
		goto st293;
	goto st0;
st293:
	if ( ++p == pe )
		goto _test_eof293;
case 293:
	if ( (*p) == 32 )
		goto tr387;
	goto st0;
st294:
	if ( ++p == pe )
		goto _test_eof294;
case 294:
	if ( (*p) == 69 )
		goto st295;
	goto st0;
st295:
	if ( ++p == pe )
		goto _test_eof295;
case 295:
	if ( (*p) == 65 )
		goto st296;
	goto st0;
st296:
	if ( ++p == pe )
		goto _test_eof296;
case 296:
	if ( (*p) == 68 )
		goto st297;
	goto st0;
st297:
	if ( ++p == pe )
		goto _test_eof297;
case 297:
	if ( (*p) == 32 )
		goto tr391;
	goto st0;
st298:
	if ( ++p == pe )
		goto _test_eof298;
case 298:
	if ( (*p) == 80 )
		goto st299;
	goto st0;
st299:
	if ( ++p == pe )
		goto _test_eof299;
case 299:
	if ( (*p) == 84 )
		goto st300;
	goto st0;
st300:
	if ( ++p == pe )
		goto _test_eof300;
case 300:
	if ( (*p) == 73 )
		goto st301;
	goto st0;
st301:
	if ( ++p == pe )
		goto _test_eof301;
case 301:
	if ( (*p) == 79 )
		goto st302;
	goto st0;
st302:
	if ( ++p == pe )
		goto _test_eof302;
case 302:
	if ( (*p) == 78 )
		goto st303;
	goto st0;
st303:
	if ( ++p == pe )
		goto _test_eof303;
case 303:
	if ( (*p) == 83 )
		goto st304;
	goto st0;
st304:
	if ( ++p == pe )
		goto _test_eof304;
case 304:
	if ( (*p) == 32 )
		goto tr398;
	goto st0;
st305:
	if ( ++p == pe )
		goto _test_eof305;
case 305:
	switch( (*p) ) {
		case 79: goto st306;
		case 85: goto st309;
	}
	goto st0;
st306:
	if ( ++p == pe )
		goto _test_eof306;
case 306:
	if ( (*p) == 83 )
		goto st307;
	goto st0;
st307:
	if ( ++p == pe )
		goto _test_eof307;
case 307:
	if ( (*p) == 84 )
		goto st308;
	goto st0;
st308:
	if ( ++p == pe )
		goto _test_eof308;
case 308:
	if ( (*p) == 32 )
		goto tr403;
	goto st0;
st309:
	if ( ++p == pe )
		goto _test_eof309;
case 309:
	if ( (*p) == 84 )
		goto st310;
	goto st0;
st310:
	if ( ++p == pe )
		goto _test_eof310;
case 310:
	if ( (*p) == 32 )
		goto tr405;
	goto st0;
st311:
	if ( ++p == pe )
		goto _test_eof311;
case 311:
	if ( (*p) == 82 )
		goto st312;
	goto st0;
st312:
	if ( ++p == pe )
		goto _test_eof312;
case 312:
	if ( (*p) == 65 )
		goto st313;
	goto st0;
st313:
	if ( ++p == pe )
		goto _test_eof313;
case 313:
	if ( (*p) == 67 )
		goto st314;
	goto st0;
st314:
	if ( ++p == pe )
		goto _test_eof314;
case 314:
	if ( (*p) == 69 )
		goto st315;
	goto st0;
st315:
	if ( ++p == pe )
		goto _test_eof315;
case 315:
	if ( (*p) == 32 )
		goto tr410;
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof316: cs = 316; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof41: cs = 41; goto _test_eof; 
	_test_eof42: cs = 42; goto _test_eof; 
	_test_eof43: cs = 43; goto _test_eof; 
	_test_eof44: cs = 44; goto _test_eof; 
	_test_eof45: cs = 45; goto _test_eof; 
	_test_eof46: cs = 46; goto _test_eof; 
	_test_eof47: cs = 47; goto _test_eof; 
	_test_eof48: cs = 48; goto _test_eof; 
	_test_eof49: cs = 49; goto _test_eof; 
	_test_eof50: cs = 50; goto _test_eof; 
	_test_eof51: cs = 51; goto _test_eof; 
	_test_eof52: cs = 52; goto _test_eof; 
	_test_eof53: cs = 53; goto _test_eof; 
	_test_eof54: cs = 54; goto _test_eof; 
	_test_eof55: cs = 55; goto _test_eof; 
	_test_eof56: cs = 56; goto _test_eof; 
	_test_eof57: cs = 57; goto _test_eof; 
	_test_eof58: cs = 58; goto _test_eof; 
	_test_eof59: cs = 59; goto _test_eof; 
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof92: cs = 92; goto _test_eof; 
	_test_eof93: cs = 93; goto _test_eof; 
	_test_eof94: cs = 94; goto _test_eof; 
	_test_eof95: cs = 95; goto _test_eof; 
	_test_eof97: cs = 97; goto _test_eof; 
	_test_eof98: cs = 98; goto _test_eof; 
	_test_eof317: cs = 317; goto _test_eof; 
	_test_eof99: cs = 99; goto _test_eof; 
	_test_eof100: cs = 100; goto _test_eof; 
	_test_eof101: cs = 101; goto _test_eof; 
	_test_eof102: cs = 102; goto _test_eof; 
	_test_eof103: cs = 103; goto _test_eof; 
	_test_eof104: cs = 104; goto _test_eof; 
	_test_eof105: cs = 105; goto _test_eof; 
	_test_eof107: cs = 107; goto _test_eof; 
	_test_eof108: cs = 108; goto _test_eof; 
	_test_eof109: cs = 109; goto _test_eof; 
	_test_eof110: cs = 110; goto _test_eof; 
	_test_eof318: cs = 318; goto _test_eof; 
	_test_eof111: cs = 111; goto _test_eof; 
	_test_eof112: cs = 112; goto _test_eof; 
	_test_eof113: cs = 113; goto _test_eof; 
	_test_eof114: cs = 114; goto _test_eof; 
	_test_eof115: cs = 115; goto _test_eof; 
	_test_eof116: cs = 116; goto _test_eof; 
	_test_eof117: cs = 117; goto _test_eof; 
	_test_eof118: cs = 118; goto _test_eof; 
	_test_eof119: cs = 119; goto _test_eof; 
	_test_eof319: cs = 319; goto _test_eof; 
	_test_eof120: cs = 120; goto _test_eof; 
	_test_eof121: cs = 121; goto _test_eof; 
	_test_eof122: cs = 122; goto _test_eof; 
	_test_eof123: cs = 123; goto _test_eof; 
	_test_eof125: cs = 125; goto _test_eof; 
	_test_eof126: cs = 126; goto _test_eof; 
	_test_eof127: cs = 127; goto _test_eof; 
	_test_eof128: cs = 128; goto _test_eof; 
	_test_eof129: cs = 129; goto _test_eof; 
	_test_eof130: cs = 130; goto _test_eof; 
	_test_eof131: cs = 131; goto _test_eof; 
	_test_eof132: cs = 132; goto _test_eof; 
	_test_eof133: cs = 133; goto _test_eof; 
	_test_eof134: cs = 134; goto _test_eof; 
	_test_eof135: cs = 135; goto _test_eof; 
	_test_eof136: cs = 136; goto _test_eof; 
	_test_eof137: cs = 137; goto _test_eof; 
	_test_eof138: cs = 138; goto _test_eof; 
	_test_eof139: cs = 139; goto _test_eof; 
	_test_eof140: cs = 140; goto _test_eof; 
	_test_eof141: cs = 141; goto _test_eof; 
	_test_eof142: cs = 142; goto _test_eof; 
	_test_eof143: cs = 143; goto _test_eof; 
	_test_eof144: cs = 144; goto _test_eof; 
	_test_eof145: cs = 145; goto _test_eof; 
	_test_eof320: cs = 320; goto _test_eof; 
	_test_eof146: cs = 146; goto _test_eof; 
	_test_eof147: cs = 147; goto _test_eof; 
	_test_eof148: cs = 148; goto _test_eof; 
	_test_eof149: cs = 149; goto _test_eof; 
	_test_eof150: cs = 150; goto _test_eof; 
	_test_eof151: cs = 151; goto _test_eof; 
	_test_eof152: cs = 152; goto _test_eof; 
	_test_eof153: cs = 153; goto _test_eof; 
	_test_eof154: cs = 154; goto _test_eof; 
	_test_eof155: cs = 155; goto _test_eof; 
	_test_eof156: cs = 156; goto _test_eof; 
	_test_eof157: cs = 157; goto _test_eof; 
	_test_eof158: cs = 158; goto _test_eof; 
	_test_eof159: cs = 159; goto _test_eof; 
	_test_eof160: cs = 160; goto _test_eof; 
	_test_eof161: cs = 161; goto _test_eof; 
	_test_eof162: cs = 162; goto _test_eof; 
	_test_eof163: cs = 163; goto _test_eof; 
	_test_eof164: cs = 164; goto _test_eof; 
	_test_eof165: cs = 165; goto _test_eof; 
	_test_eof166: cs = 166; goto _test_eof; 
	_test_eof167: cs = 167; goto _test_eof; 
	_test_eof168: cs = 168; goto _test_eof; 
	_test_eof169: cs = 169; goto _test_eof; 
	_test_eof170: cs = 170; goto _test_eof; 
	_test_eof171: cs = 171; goto _test_eof; 
	_test_eof172: cs = 172; goto _test_eof; 
	_test_eof173: cs = 173; goto _test_eof; 
	_test_eof174: cs = 174; goto _test_eof; 
	_test_eof175: cs = 175; goto _test_eof; 
	_test_eof176: cs = 176; goto _test_eof; 
	_test_eof177: cs = 177; goto _test_eof; 
	_test_eof178: cs = 178; goto _test_eof; 
	_test_eof179: cs = 179; goto _test_eof; 
	_test_eof180: cs = 180; goto _test_eof; 
	_test_eof181: cs = 181; goto _test_eof; 
	_test_eof182: cs = 182; goto _test_eof; 
	_test_eof183: cs = 183; goto _test_eof; 
	_test_eof184: cs = 184; goto _test_eof; 
	_test_eof185: cs = 185; goto _test_eof; 
	_test_eof186: cs = 186; goto _test_eof; 
	_test_eof187: cs = 187; goto _test_eof; 
	_test_eof188: cs = 188; goto _test_eof; 
	_test_eof189: cs = 189; goto _test_eof; 
	_test_eof190: cs = 190; goto _test_eof; 
	_test_eof191: cs = 191; goto _test_eof; 
	_test_eof192: cs = 192; goto _test_eof; 
	_test_eof193: cs = 193; goto _test_eof; 
	_test_eof194: cs = 194; goto _test_eof; 
	_test_eof195: cs = 195; goto _test_eof; 
	_test_eof196: cs = 196; goto _test_eof; 
	_test_eof197: cs = 197; goto _test_eof; 
	_test_eof198: cs = 198; goto _test_eof; 
	_test_eof199: cs = 199; goto _test_eof; 
	_test_eof200: cs = 200; goto _test_eof; 
	_test_eof201: cs = 201; goto _test_eof; 
	_test_eof202: cs = 202; goto _test_eof; 
	_test_eof203: cs = 203; goto _test_eof; 
	_test_eof204: cs = 204; goto _test_eof; 
	_test_eof205: cs = 205; goto _test_eof; 
	_test_eof206: cs = 206; goto _test_eof; 
	_test_eof207: cs = 207; goto _test_eof; 
	_test_eof208: cs = 208; goto _test_eof; 
	_test_eof209: cs = 209; goto _test_eof; 
	_test_eof210: cs = 210; goto _test_eof; 
	_test_eof211: cs = 211; goto _test_eof; 
	_test_eof212: cs = 212; goto _test_eof; 
	_test_eof213: cs = 213; goto _test_eof; 
	_test_eof214: cs = 214; goto _test_eof; 
	_test_eof215: cs = 215; goto _test_eof; 
	_test_eof216: cs = 216; goto _test_eof; 
	_test_eof217: cs = 217; goto _test_eof; 
	_test_eof218: cs = 218; goto _test_eof; 
	_test_eof219: cs = 219; goto _test_eof; 
	_test_eof220: cs = 220; goto _test_eof; 
	_test_eof221: cs = 221; goto _test_eof; 
	_test_eof222: cs = 222; goto _test_eof; 
	_test_eof223: cs = 223; goto _test_eof; 
	_test_eof224: cs = 224; goto _test_eof; 
	_test_eof225: cs = 225; goto _test_eof; 
	_test_eof226: cs = 226; goto _test_eof; 
	_test_eof227: cs = 227; goto _test_eof; 
	_test_eof228: cs = 228; goto _test_eof; 
	_test_eof229: cs = 229; goto _test_eof; 
	_test_eof230: cs = 230; goto _test_eof; 
	_test_eof231: cs = 231; goto _test_eof; 
	_test_eof232: cs = 232; goto _test_eof; 
	_test_eof233: cs = 233; goto _test_eof; 
	_test_eof234: cs = 234; goto _test_eof; 
	_test_eof235: cs = 235; goto _test_eof; 
	_test_eof236: cs = 236; goto _test_eof; 
	_test_eof237: cs = 237; goto _test_eof; 
	_test_eof238: cs = 238; goto _test_eof; 
	_test_eof239: cs = 239; goto _test_eof; 
	_test_eof240: cs = 240; goto _test_eof; 
	_test_eof241: cs = 241; goto _test_eof; 
	_test_eof242: cs = 242; goto _test_eof; 
	_test_eof243: cs = 243; goto _test_eof; 
	_test_eof244: cs = 244; goto _test_eof; 
	_test_eof245: cs = 245; goto _test_eof; 
	_test_eof246: cs = 246; goto _test_eof; 
	_test_eof247: cs = 247; goto _test_eof; 
	_test_eof248: cs = 248; goto _test_eof; 
	_test_eof249: cs = 249; goto _test_eof; 
	_test_eof250: cs = 250; goto _test_eof; 
	_test_eof251: cs = 251; goto _test_eof; 
	_test_eof252: cs = 252; goto _test_eof; 
	_test_eof253: cs = 253; goto _test_eof; 
	_test_eof254: cs = 254; goto _test_eof; 
	_test_eof255: cs = 255; goto _test_eof; 
	_test_eof256: cs = 256; goto _test_eof; 
	_test_eof257: cs = 257; goto _test_eof; 
	_test_eof258: cs = 258; goto _test_eof; 
	_test_eof259: cs = 259; goto _test_eof; 
	_test_eof260: cs = 260; goto _test_eof; 
	_test_eof261: cs = 261; goto _test_eof; 
	_test_eof262: cs = 262; goto _test_eof; 
	_test_eof263: cs = 263; goto _test_eof; 
	_test_eof264: cs = 264; goto _test_eof; 
	_test_eof265: cs = 265; goto _test_eof; 
	_test_eof266: cs = 266; goto _test_eof; 
	_test_eof267: cs = 267; goto _test_eof; 
	_test_eof268: cs = 268; goto _test_eof; 
	_test_eof269: cs = 269; goto _test_eof; 
	_test_eof270: cs = 270; goto _test_eof; 
	_test_eof271: cs = 271; goto _test_eof; 
	_test_eof272: cs = 272; goto _test_eof; 
	_test_eof273: cs = 273; goto _test_eof; 
	_test_eof274: cs = 274; goto _test_eof; 
	_test_eof275: cs = 275; goto _test_eof; 
	_test_eof276: cs = 276; goto _test_eof; 
	_test_eof277: cs = 277; goto _test_eof; 
	_test_eof278: cs = 278; goto _test_eof; 
	_test_eof279: cs = 279; goto _test_eof; 
	_test_eof280: cs = 280; goto _test_eof; 
	_test_eof281: cs = 281; goto _test_eof; 
	_test_eof282: cs = 282; goto _test_eof; 
	_test_eof283: cs = 283; goto _test_eof; 
	_test_eof284: cs = 284; goto _test_eof; 
	_test_eof285: cs = 285; goto _test_eof; 
	_test_eof286: cs = 286; goto _test_eof; 
	_test_eof287: cs = 287; goto _test_eof; 
	_test_eof288: cs = 288; goto _test_eof; 
	_test_eof289: cs = 289; goto _test_eof; 
	_test_eof290: cs = 290; goto _test_eof; 
	_test_eof291: cs = 291; goto _test_eof; 
	_test_eof292: cs = 292; goto _test_eof; 
	_test_eof293: cs = 293; goto _test_eof; 
	_test_eof294: cs = 294; goto _test_eof; 
	_test_eof295: cs = 295; goto _test_eof; 
	_test_eof296: cs = 296; goto _test_eof; 
	_test_eof297: cs = 297; goto _test_eof; 
	_test_eof298: cs = 298; goto _test_eof; 
	_test_eof299: cs = 299; goto _test_eof; 
	_test_eof300: cs = 300; goto _test_eof; 
	_test_eof301: cs = 301; goto _test_eof; 
	_test_eof302: cs = 302; goto _test_eof; 
	_test_eof303: cs = 303; goto _test_eof; 
	_test_eof304: cs = 304; goto _test_eof; 
	_test_eof305: cs = 305; goto _test_eof; 
	_test_eof306: cs = 306; goto _test_eof; 
	_test_eof307: cs = 307; goto _test_eof; 
	_test_eof308: cs = 308; goto _test_eof; 
	_test_eof309: cs = 309; goto _test_eof; 
	_test_eof310: cs = 310; goto _test_eof; 
	_test_eof311: cs = 311; goto _test_eof; 
	_test_eof312: cs = 312; goto _test_eof; 
	_test_eof313: cs = 313; goto _test_eof; 
	_test_eof314: cs = 314; goto _test_eof; 
	_test_eof315: cs = 315; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 199 "src/panda/protocol/http/MessageParser.rl"
    return p - ps;
}

#endif

}}}
