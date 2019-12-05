
#line 1 "src/panda/protocol/http/MessageParser.rl"
#include "MessageParser.h"


#line 118 "src/panda/protocol/http/MessageParser.rl"


namespace panda { namespace protocol { namespace http {


#line 13 "src/panda/protocol/http/MessageParser.cc"
static const int message_parser_start = 1;
static const int message_parser_first_final = 252;
static const int message_parser_error = 0;

static const int message_parser_en_first_chunk = 64;
static const int message_parser_en_chunk = 74;
static const int message_parser_en_chunk_trailer = 86;
static const int message_parser_en_request = 92;
static const int message_parser_en_response = 1;


#line 123 "src/panda/protocol/http/MessageParser.rl"

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
		case 49: goto st63;
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
#line 60 "src/panda/protocol/http/MessageParser.rl"
	{message->http_version = 10;}
	goto st10;
tr76:
#line 60 "src/panda/protocol/http/MessageParser.rl"
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
#line 112 "src/panda/protocol/http/MessageParser.rl"
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
#line 112 "src/panda/protocol/http/MessageParser.rl"
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
#line 112 "src/panda/protocol/http/MessageParser.rl"
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
#line 113 "src/panda/protocol/http/MessageParser.rl"
	{SAVE(response->message)}
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st16;
tr18:
#line 113 "src/panda/protocol/http/MessageParser.rl"
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
tr75:
#line 82 "src/panda/protocol/http/MessageParser.rl"
	{message->chunked = true;}
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
#line 288 "src/panda/protocol/http/MessageParser.cc"
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
        {p++; cs = 252; goto _out;}
    }
	goto st252;
st252:
	if ( ++p == pe )
		goto _test_eof252;
case 252:
#line 341 "src/panda/protocol/http/MessageParser.cc"
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
#line 354 "src/panda/protocol/http/MessageParser.cc"
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
#line 398 "src/panda/protocol/http/MessageParser.cc"
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
tr74:
#line 82 "src/panda/protocol/http/MessageParser.rl"
	{message->chunked = true;}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 423 "src/panda/protocol/http/MessageParser.cc"
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
#line 445 "src/panda/protocol/http/MessageParser.cc"
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
		case 76: goto st30;
		case 108: goto st30;
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
		case 69: goto st31;
		case 101: goto st31;
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
		case 78: goto st32;
		case 110: goto st32;
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
		case 71: goto st33;
		case 103: goto st33;
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
		case 84: goto st34;
		case 116: goto st34;
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
		case 72: goto st35;
		case 104: goto st35;
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
		case 58: goto tr45;
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
tr45:
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
	goto st36;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
#line 876 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st36;
		case 13: goto tr29;
		case 32: goto st36;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr47;
	} else if ( (*p) >= 0 )
		goto st0;
	goto tr27;
tr47:
#line 38 "src/panda/protocol/http/MessageParser.rl"
	{
        if (has_content_length) {
            cs = message_parser_error;
            set_error(errc::multiple_content_length);
            {p++; cs = 37; goto _out;}
        }
        has_content_length = true;
    }
#line 81 "src/panda/protocol/http/MessageParser.rl"
	{ADD_DIGIT(content_length)}
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st37;
tr48:
#line 81 "src/panda/protocol/http/MessageParser.rl"
	{ADD_DIGIT(content_length)}
	goto st37;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
#line 915 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr31;
		case 127: goto st0;
	}
	if ( (*p) < 10 ) {
		if ( 0 <= (*p) && (*p) <= 8 )
			goto st0;
	} else if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr48;
	} else
		goto st0;
	goto st21;
tr23:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st38;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
#line 940 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 82: goto st39;
		case 114: goto st39;
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
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 65: goto st40;
		case 97: goto st40;
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
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 78: goto st41;
		case 110: goto st41;
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
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 83: goto st42;
		case 115: goto st42;
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
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 70: goto st43;
		case 102: goto st43;
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
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 69: goto st44;
		case 101: goto st44;
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
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 82: goto st45;
		case 114: goto st45;
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
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	switch( (*p) ) {
		case 33: goto st19;
		case 45: goto st46;
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
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 69: goto st47;
		case 101: goto st47;
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
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 78: goto st48;
		case 110: goto st48;
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
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 67: goto st49;
		case 99: goto st49;
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
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 79: goto st50;
		case 111: goto st50;
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
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 68: goto st51;
		case 100: goto st51;
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
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 73: goto st52;
		case 105: goto st52;
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
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 78: goto st53;
		case 110: goto st53;
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
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr26;
		case 71: goto st54;
		case 103: goto st54;
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
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr65;
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
tr65:
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
	goto st55;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
#line 1461 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st55;
		case 13: goto tr29;
		case 32: goto st55;
		case 67: goto tr67;
		case 99: goto tr67;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr27;
tr67:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st56;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
#line 1484 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr31;
		case 72: goto st57;
		case 104: goto st57;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 13: goto tr31;
		case 85: goto st58;
		case 117: goto st58;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 13: goto tr31;
		case 78: goto st59;
		case 110: goto st59;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 13: goto tr31;
		case 75: goto st60;
		case 107: goto st60;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 13: goto tr31;
		case 69: goto st61;
		case 101: goto st61;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 13: goto tr31;
		case 68: goto st62;
		case 100: goto st62;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	switch( (*p) ) {
		case 9: goto tr74;
		case 13: goto tr75;
		case 32: goto tr74;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st21;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	if ( (*p) == 32 )
		goto tr76;
	goto st0;
case 64:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr77;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr77;
	} else
		goto tr77;
	goto st0;
tr77:
#line 86 "src/panda/protocol/http/MessageParser.rl"
	{chunk_length = 0;}
#line 86 "src/panda/protocol/http/MessageParser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st65;
tr79:
#line 86 "src/panda/protocol/http/MessageParser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st65;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
#line 1621 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto st66;
		case 59: goto st67;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr79;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr79;
	} else
		goto tr79;
	goto st0;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	if ( (*p) == 10 )
		goto tr81;
	goto st0;
tr81:
#line 16 "src/panda/protocol/http/MessageParser.rl"
	{
        {p++; cs = 253; goto _out;}
    }
	goto st253;
st253:
	if ( ++p == pe )
		goto _test_eof253;
case 253:
#line 1652 "src/panda/protocol/http/MessageParser.cc"
	goto st0;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 33: goto st68;
		case 124: goto st68;
		case 126: goto st68;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st68;
		} else if ( (*p) >= 35 )
			goto st68;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st68;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st68;
		} else
			goto st68;
	} else
		goto st68;
	goto st0;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 13: goto st66;
		case 33: goto st68;
		case 59: goto st67;
		case 61: goto st69;
		case 124: goto st68;
		case 126: goto st68;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st68;
		} else if ( (*p) >= 35 )
			goto st68;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st68;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st68;
		} else
			goto st68;
	} else
		goto st68;
	goto st0;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 34: goto st71;
		case 124: goto st70;
		case 126: goto st70;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st70;
		} else if ( (*p) >= 33 )
			goto st70;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st70;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st70;
		} else
			goto st70;
	} else
		goto st70;
	goto st0;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	switch( (*p) ) {
		case 13: goto st66;
		case 33: goto st70;
		case 59: goto st67;
		case 124: goto st70;
		case 126: goto st70;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st70;
		} else if ( (*p) >= 35 )
			goto st70;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st70;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st70;
		} else
			goto st70;
	} else
		goto st70;
	goto st0;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 34: goto st72;
		case 92: goto st73;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st71;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 13: goto st66;
		case 59: goto st67;
	}
	goto st0;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	if ( (*p) == 127 )
		goto st0;
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st71;
case 74:
	if ( (*p) == 13 )
		goto st75;
	goto st0;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	if ( (*p) == 10 )
		goto st76;
	goto st0;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr90;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr90;
	} else
		goto tr90;
	goto st0;
tr90:
#line 86 "src/panda/protocol/http/MessageParser.rl"
	{chunk_length = 0;}
#line 86 "src/panda/protocol/http/MessageParser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st77;
tr92:
#line 86 "src/panda/protocol/http/MessageParser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st77;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
#line 1841 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto st78;
		case 59: goto st79;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr92;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr92;
	} else
		goto tr92;
	goto st0;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	if ( (*p) == 10 )
		goto tr94;
	goto st0;
tr94:
#line 16 "src/panda/protocol/http/MessageParser.rl"
	{
        {p++; cs = 254; goto _out;}
    }
	goto st254;
st254:
	if ( ++p == pe )
		goto _test_eof254;
case 254:
#line 1872 "src/panda/protocol/http/MessageParser.cc"
	goto st0;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 33: goto st80;
		case 124: goto st80;
		case 126: goto st80;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st80;
		} else if ( (*p) >= 35 )
			goto st80;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st80;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st80;
		} else
			goto st80;
	} else
		goto st80;
	goto st0;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 13: goto st78;
		case 33: goto st80;
		case 59: goto st79;
		case 61: goto st81;
		case 124: goto st80;
		case 126: goto st80;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st80;
		} else if ( (*p) >= 35 )
			goto st80;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st80;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st80;
		} else
			goto st80;
	} else
		goto st80;
	goto st0;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	switch( (*p) ) {
		case 34: goto st83;
		case 124: goto st82;
		case 126: goto st82;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st82;
		} else if ( (*p) >= 33 )
			goto st82;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st82;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st82;
		} else
			goto st82;
	} else
		goto st82;
	goto st0;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	switch( (*p) ) {
		case 13: goto st78;
		case 33: goto st82;
		case 59: goto st79;
		case 124: goto st82;
		case 126: goto st82;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st82;
		} else if ( (*p) >= 35 )
			goto st82;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st82;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st82;
		} else
			goto st82;
	} else
		goto st82;
	goto st0;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	switch( (*p) ) {
		case 34: goto st84;
		case 92: goto st85;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st83;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 13: goto st78;
		case 59: goto st79;
	}
	goto st0;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	if ( (*p) == 127 )
		goto st0;
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st83;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	switch( (*p) ) {
		case 13: goto st87;
		case 33: goto tr102;
		case 124: goto tr102;
		case 126: goto tr102;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr102;
		} else if ( (*p) >= 35 )
			goto tr102;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr102;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr102;
		} else
			goto tr102;
	} else
		goto tr102;
	goto st0;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	if ( (*p) == 10 )
		goto tr103;
	goto st0;
tr103:
#line 16 "src/panda/protocol/http/MessageParser.rl"
	{
        {p++; cs = 255; goto _out;}
    }
	goto st255;
st255:
	if ( ++p == pe )
		goto _test_eof255;
case 255:
#line 2068 "src/panda/protocol/http/MessageParser.cc"
	goto st0;
tr102:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st88;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
#line 2081 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st88;
		case 58: goto tr105;
		case 124: goto st88;
		case 126: goto st88;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st88;
		} else if ( (*p) >= 35 )
			goto st88;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st88;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st88;
		} else
			goto st88;
	} else
		goto st88;
	goto st0;
tr105:
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
	goto st89;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
#line 2125 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st89;
		case 13: goto tr108;
		case 32: goto st89;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr106;
tr106:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st90;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
#line 2146 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr110;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st90;
tr108:
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
	goto st91;
tr110:
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
	goto st91;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
#line 2196 "src/panda/protocol/http/MessageParser.cc"
	if ( (*p) == 10 )
		goto st86;
	goto st0;
case 92:
	switch( (*p) ) {
		case 67: goto st93;
		case 68: goto st221;
		case 71: goto st227;
		case 72: goto st230;
		case 79: goto st234;
		case 80: goto st241;
		case 84: goto st247;
	}
	goto st0;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	if ( (*p) == 79 )
		goto st94;
	goto st0;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	if ( (*p) == 78 )
		goto st95;
	goto st0;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	if ( (*p) == 78 )
		goto st96;
	goto st0;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	if ( (*p) == 69 )
		goto st97;
	goto st0;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	if ( (*p) == 67 )
		goto st98;
	goto st0;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	if ( (*p) == 84 )
		goto st99;
	goto st0;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	if ( (*p) == 32 )
		goto tr125;
	goto st0;
tr125:
#line 103 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::CONNECT; }
	goto st100;
tr290:
#line 101 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::DELETE; }
	goto st100;
tr293:
#line 97 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::GET; }
	goto st100;
tr297:
#line 98 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::HEAD; }
	goto st100;
tr304:
#line 96 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::OPTIONS; }
	goto st100;
tr309:
#line 99 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::POST; }
	goto st100;
tr311:
#line 100 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::PUT; }
	goto st100;
tr316:
#line 102 "src/panda/protocol/http/MessageParser.rl"
	{request->method = Request::Method::TRACE; }
	goto st100;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
#line 2296 "src/panda/protocol/http/MessageParser.cc"
	if ( 33 <= (*p) && (*p) <= 126 )
		goto tr126;
	goto st0;
tr126:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st101;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
#line 2311 "src/panda/protocol/http/MessageParser.cc"
	if ( (*p) == 32 )
		goto tr127;
	if ( 33 <= (*p) && (*p) <= 126 )
		goto st101;
	goto st0;
tr127:
#line 47 "src/panda/protocol/http/MessageParser.rl"
	{
        string target;
        SAVE(target);
        request->uri = new URI(target);
    }
#line 12 "src/panda/protocol/http/MessageParser.rl"
	{
        marked = false;
    }
	goto st102;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
#line 2333 "src/panda/protocol/http/MessageParser.cc"
	if ( (*p) == 72 )
		goto st103;
	goto st0;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
	if ( (*p) == 84 )
		goto st104;
	goto st0;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	if ( (*p) == 84 )
		goto st105;
	goto st0;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
	if ( (*p) == 80 )
		goto st106;
	goto st0;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
	if ( (*p) == 47 )
		goto st107;
	goto st0;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
	if ( (*p) == 49 )
		goto st108;
	goto st0;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	if ( (*p) == 46 )
		goto st109;
	goto st0;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
	switch( (*p) ) {
		case 48: goto st110;
		case 49: goto st220;
	}
	goto st0;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
	if ( (*p) == 13 )
		goto tr138;
	goto st0;
tr138:
#line 60 "src/panda/protocol/http/MessageParser.rl"
	{message->http_version = 10;}
	goto st111;
tr150:
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
	goto st111;
tr152:
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
	goto st111;
tr283:
#line 82 "src/panda/protocol/http/MessageParser.rl"
	{message->chunked = true;}
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
	goto st111;
tr284:
#line 60 "src/panda/protocol/http/MessageParser.rl"
	{message->http_version = 11;}
	goto st111;
tr176:
#line 68 "src/panda/protocol/http/MessageParser.rl"
	{compr = compression::GZIP | compression::DEFLATE; }
#line 53 "src/panda/protocol/http/MessageParser.rl"
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
	goto st111;
tr190:
#line 53 "src/panda/protocol/http/MessageParser.rl"
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
	goto st111;
tr197:
#line 70 "src/panda/protocol/http/MessageParser.rl"
	{ compr = 0; }
#line 53 "src/panda/protocol/http/MessageParser.rl"
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
	goto st111;
tr224:
#line 64 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::DEFLATE;  }
#line 53 "src/panda/protocol/http/MessageParser.rl"
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
	goto st111;
tr231:
#line 63 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::GZIP;     }
#line 53 "src/panda/protocol/http/MessageParser.rl"
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
	goto st111;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
#line 2577 "src/panda/protocol/http/MessageParser.cc"
	if ( (*p) == 10 )
		goto st112;
	goto st0;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	switch( (*p) ) {
		case 13: goto st113;
		case 33: goto tr141;
		case 65: goto tr142;
		case 67: goto tr143;
		case 84: goto tr144;
		case 97: goto tr142;
		case 99: goto tr143;
		case 116: goto tr144;
		case 124: goto tr141;
		case 126: goto tr141;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr141;
		} else if ( (*p) >= 35 )
			goto tr141;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 66 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr141;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr141;
		} else
			goto tr141;
	} else
		goto tr141;
	goto st0;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
	if ( (*p) == 10 )
		goto tr145;
	goto st0;
tr145:
#line 16 "src/panda/protocol/http/MessageParser.rl"
	{
        {p++; cs = 256; goto _out;}
    }
	goto st256;
st256:
	if ( ++p == pe )
		goto _test_eof256;
case 256:
#line 2632 "src/panda/protocol/http/MessageParser.cc"
	goto st0;
tr141:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st114;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
#line 2645 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
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
tr147:
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
	goto st115;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
#line 2689 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st115;
		case 13: goto tr150;
		case 32: goto st115;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr148;
tr148:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st116;
tr282:
#line 82 "src/panda/protocol/http/MessageParser.rl"
	{message->chunked = true;}
	goto st116;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
#line 2714 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr152;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
tr142:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st117;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
#line 2736 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 67: goto st118;
		case 99: goto st118;
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
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 67: goto st119;
		case 99: goto st119;
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
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 69: goto st120;
		case 101: goto st120;
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
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 80: goto st121;
		case 112: goto st121;
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
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 84: goto st122;
		case 116: goto st122;
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
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
	switch( (*p) ) {
		case 33: goto st114;
		case 45: goto st123;
		case 46: goto st114;
		case 58: goto tr147;
		case 124: goto st114;
		case 126: goto st114;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st114;
		} else if ( (*p) >= 35 )
			goto st114;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st114;
		} else if ( (*p) >= 65 )
			goto st114;
	} else
		goto st114;
	goto st0;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 69: goto st124;
		case 101: goto st124;
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
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 78: goto st125;
		case 110: goto st125;
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
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 67: goto st126;
		case 99: goto st126;
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
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 79: goto st127;
		case 111: goto st127;
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
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 68: goto st128;
		case 100: goto st128;
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
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 73: goto st129;
		case 105: goto st129;
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
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 78: goto st130;
		case 110: goto st130;
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
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 71: goto st131;
		case 103: goto st131;
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
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr167;
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
tr167:
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
	goto st132;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
#line 3197 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st132;
		case 13: goto tr150;
		case 32: goto st132;
		case 42: goto tr169;
		case 98: goto tr170;
		case 99: goto tr171;
		case 100: goto tr172;
		case 103: goto tr173;
		case 105: goto tr174;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr148;
tr169:
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
#line 3224 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto tr175;
		case 13: goto tr176;
		case 32: goto tr175;
		case 44: goto tr177;
		case 59: goto tr178;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
tr175:
#line 68 "src/panda/protocol/http/MessageParser.rl"
	{compr = compression::GZIP | compression::DEFLATE; }
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st134;
tr189:
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st134;
tr223:
#line 64 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::DEFLATE;  }
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st134;
tr230:
#line 63 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::GZIP;     }
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st134;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
#line 3282 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st134;
		case 13: goto tr152;
		case 32: goto st134;
		case 44: goto st135;
		case 59: goto st138;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
tr177:
#line 68 "src/panda/protocol/http/MessageParser.rl"
	{compr = compression::GZIP | compression::DEFLATE; }
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st135;
tr191:
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st135;
tr198:
#line 70 "src/panda/protocol/http/MessageParser.rl"
	{ compr = 0; }
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st135;
tr225:
#line 64 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::DEFLATE;  }
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st135;
tr232:
#line 63 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::GZIP;     }
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st135;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
#line 3351 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st135;
		case 13: goto tr152;
		case 32: goto st135;
		case 42: goto st133;
		case 98: goto st136;
		case 99: goto st154;
		case 100: goto st161;
		case 103: goto st168;
		case 105: goto st172;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
tr170:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st136;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
#line 3378 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr152;
		case 114: goto st137;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
	switch( (*p) ) {
		case 9: goto tr189;
		case 13: goto tr190;
		case 32: goto tr189;
		case 44: goto tr191;
		case 59: goto st138;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
tr178:
#line 68 "src/panda/protocol/http/MessageParser.rl"
	{compr = compression::GZIP | compression::DEFLATE; }
	goto st138;
tr226:
#line 64 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::DEFLATE;  }
	goto st138;
tr233:
#line 63 "src/panda/protocol/http/MessageParser.rl"
	{ compr = compression::GZIP;     }
	goto st138;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
#line 3421 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st138;
		case 13: goto tr152;
		case 32: goto st138;
		case 113: goto st139;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
	switch( (*p) ) {
		case 13: goto tr152;
		case 61: goto st140;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
	switch( (*p) ) {
		case 13: goto tr152;
		case 48: goto st141;
		case 49: goto st150;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
	switch( (*p) ) {
		case 9: goto tr196;
		case 13: goto tr197;
		case 32: goto tr196;
		case 44: goto tr198;
		case 46: goto st143;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
tr207:
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st142;
tr196:
#line 70 "src/panda/protocol/http/MessageParser.rl"
	{ compr = 0; }
#line 53 "src/panda/protocol/http/MessageParser.rl"
	{
        if (compr) {
            request->allow_compression(compr);
            compr = 0;
        }
    }
	goto st142;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
#line 3502 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st142;
		case 13: goto tr152;
		case 32: goto st142;
		case 44: goto st135;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
	switch( (*p) ) {
		case 9: goto tr196;
		case 13: goto tr197;
		case 32: goto tr196;
		case 44: goto tr198;
		case 48: goto st144;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st149;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
	switch( (*p) ) {
		case 9: goto tr196;
		case 13: goto tr197;
		case 32: goto tr196;
		case 44: goto tr198;
		case 48: goto st145;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st148;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
	switch( (*p) ) {
		case 9: goto tr196;
		case 13: goto tr197;
		case 32: goto tr196;
		case 44: goto tr198;
		case 48: goto st146;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto st147;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
	switch( (*p) ) {
		case 9: goto tr196;
		case 13: goto tr197;
		case 32: goto tr196;
		case 44: goto tr198;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
	switch( (*p) ) {
		case 9: goto tr207;
		case 13: goto tr190;
		case 32: goto tr207;
		case 44: goto tr191;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
	switch( (*p) ) {
		case 9: goto tr207;
		case 13: goto tr190;
		case 32: goto tr207;
		case 44: goto tr191;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st147;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
	switch( (*p) ) {
		case 9: goto tr207;
		case 13: goto tr190;
		case 32: goto tr207;
		case 44: goto tr191;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st148;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
	switch( (*p) ) {
		case 9: goto tr207;
		case 13: goto tr190;
		case 32: goto tr207;
		case 44: goto tr191;
		case 46: goto st151;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
	switch( (*p) ) {
		case 9: goto tr207;
		case 13: goto tr190;
		case 32: goto tr207;
		case 44: goto tr191;
		case 48: goto st152;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
	switch( (*p) ) {
		case 9: goto tr207;
		case 13: goto tr190;
		case 32: goto tr207;
		case 44: goto tr191;
		case 48: goto st153;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
	switch( (*p) ) {
		case 9: goto tr207;
		case 13: goto tr190;
		case 32: goto tr207;
		case 44: goto tr191;
		case 48: goto st147;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
tr171:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st154;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
#line 3700 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr152;
		case 111: goto st155;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
	switch( (*p) ) {
		case 13: goto tr152;
		case 109: goto st156;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
	switch( (*p) ) {
		case 13: goto tr152;
		case 112: goto st157;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
	switch( (*p) ) {
		case 13: goto tr152;
		case 114: goto st158;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
	switch( (*p) ) {
		case 13: goto tr152;
		case 101: goto st159;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
	switch( (*p) ) {
		case 13: goto tr152;
		case 115: goto st160;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st160:
	if ( ++p == pe )
		goto _test_eof160;
case 160:
	switch( (*p) ) {
		case 13: goto tr152;
		case 115: goto st137;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
tr172:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st161;
st161:
	if ( ++p == pe )
		goto _test_eof161;
case 161:
#line 3813 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr152;
		case 101: goto st162;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st162:
	if ( ++p == pe )
		goto _test_eof162;
case 162:
	switch( (*p) ) {
		case 13: goto tr152;
		case 102: goto st163;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st163:
	if ( ++p == pe )
		goto _test_eof163;
case 163:
	switch( (*p) ) {
		case 13: goto tr152;
		case 108: goto st164;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st164:
	if ( ++p == pe )
		goto _test_eof164;
case 164:
	switch( (*p) ) {
		case 13: goto tr152;
		case 97: goto st165;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st165:
	if ( ++p == pe )
		goto _test_eof165;
case 165:
	switch( (*p) ) {
		case 13: goto tr152;
		case 116: goto st166;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st166:
	if ( ++p == pe )
		goto _test_eof166;
case 166:
	switch( (*p) ) {
		case 13: goto tr152;
		case 101: goto st167;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st167:
	if ( ++p == pe )
		goto _test_eof167;
case 167:
	switch( (*p) ) {
		case 9: goto tr223;
		case 13: goto tr224;
		case 32: goto tr223;
		case 44: goto tr225;
		case 59: goto tr226;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
tr173:
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
#line 3926 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr152;
		case 122: goto st169;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st169:
	if ( ++p == pe )
		goto _test_eof169;
case 169:
	switch( (*p) ) {
		case 13: goto tr152;
		case 105: goto st170;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st170:
	if ( ++p == pe )
		goto _test_eof170;
case 170:
	switch( (*p) ) {
		case 13: goto tr152;
		case 112: goto st171;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st171:
	if ( ++p == pe )
		goto _test_eof171;
case 171:
	switch( (*p) ) {
		case 9: goto tr230;
		case 13: goto tr231;
		case 32: goto tr230;
		case 44: goto tr232;
		case 59: goto tr233;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
tr174:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st172;
st172:
	if ( ++p == pe )
		goto _test_eof172;
case 172:
#line 3994 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr152;
		case 100: goto st173;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st173:
	if ( ++p == pe )
		goto _test_eof173;
case 173:
	switch( (*p) ) {
		case 13: goto tr152;
		case 101: goto st174;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st174:
	if ( ++p == pe )
		goto _test_eof174;
case 174:
	switch( (*p) ) {
		case 13: goto tr152;
		case 110: goto st175;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st175:
	if ( ++p == pe )
		goto _test_eof175;
case 175:
	switch( (*p) ) {
		case 13: goto tr152;
		case 116: goto st176;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st176:
	if ( ++p == pe )
		goto _test_eof176;
case 176:
	switch( (*p) ) {
		case 13: goto tr152;
		case 105: goto st177;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st177:
	if ( ++p == pe )
		goto _test_eof177;
case 177:
	switch( (*p) ) {
		case 13: goto tr152;
		case 116: goto st178;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st178:
	if ( ++p == pe )
		goto _test_eof178;
case 178:
	switch( (*p) ) {
		case 13: goto tr152;
		case 121: goto st137;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
tr143:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st179;
st179:
	if ( ++p == pe )
		goto _test_eof179;
case 179:
#line 4107 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 79: goto st180;
		case 111: goto st180;
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
st180:
	if ( ++p == pe )
		goto _test_eof180;
case 180:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 78: goto st181;
		case 110: goto st181;
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
st181:
	if ( ++p == pe )
		goto _test_eof181;
case 181:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 84: goto st182;
		case 116: goto st182;
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
st182:
	if ( ++p == pe )
		goto _test_eof182;
case 182:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 69: goto st183;
		case 101: goto st183;
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
st183:
	if ( ++p == pe )
		goto _test_eof183;
case 183:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 78: goto st184;
		case 110: goto st184;
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
st184:
	if ( ++p == pe )
		goto _test_eof184;
case 184:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 84: goto st185;
		case 116: goto st185;
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
st185:
	if ( ++p == pe )
		goto _test_eof185;
case 185:
	switch( (*p) ) {
		case 33: goto st114;
		case 45: goto st186;
		case 46: goto st114;
		case 58: goto tr147;
		case 124: goto st114;
		case 126: goto st114;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st114;
		} else if ( (*p) >= 35 )
			goto st114;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st114;
		} else if ( (*p) >= 65 )
			goto st114;
	} else
		goto st114;
	goto st0;
st186:
	if ( ++p == pe )
		goto _test_eof186;
case 186:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 76: goto st187;
		case 108: goto st187;
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
st187:
	if ( ++p == pe )
		goto _test_eof187;
case 187:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 69: goto st188;
		case 101: goto st188;
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
st188:
	if ( ++p == pe )
		goto _test_eof188;
case 188:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 78: goto st189;
		case 110: goto st189;
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
st189:
	if ( ++p == pe )
		goto _test_eof189;
case 189:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 71: goto st190;
		case 103: goto st190;
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
st190:
	if ( ++p == pe )
		goto _test_eof190;
case 190:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 84: goto st191;
		case 116: goto st191;
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
st191:
	if ( ++p == pe )
		goto _test_eof191;
case 191:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 72: goto st192;
		case 104: goto st192;
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
st192:
	if ( ++p == pe )
		goto _test_eof192;
case 192:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr253;
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
tr253:
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
	goto st193;
st193:
	if ( ++p == pe )
		goto _test_eof193;
case 193:
#line 4538 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st193;
		case 13: goto tr150;
		case 32: goto st193;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr255;
	} else if ( (*p) >= 0 )
		goto st0;
	goto tr148;
tr255:
#line 38 "src/panda/protocol/http/MessageParser.rl"
	{
        if (has_content_length) {
            cs = message_parser_error;
            set_error(errc::multiple_content_length);
            {p++; cs = 194; goto _out;}
        }
        has_content_length = true;
    }
#line 81 "src/panda/protocol/http/MessageParser.rl"
	{ADD_DIGIT(content_length)}
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st194;
tr256:
#line 81 "src/panda/protocol/http/MessageParser.rl"
	{ADD_DIGIT(content_length)}
	goto st194;
st194:
	if ( ++p == pe )
		goto _test_eof194;
case 194:
#line 4577 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr152;
		case 127: goto st0;
	}
	if ( (*p) < 10 ) {
		if ( 0 <= (*p) && (*p) <= 8 )
			goto st0;
	} else if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr256;
	} else
		goto st0;
	goto st116;
tr144:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st195;
st195:
	if ( ++p == pe )
		goto _test_eof195;
case 195:
#line 4602 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 82: goto st196;
		case 114: goto st196;
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
st196:
	if ( ++p == pe )
		goto _test_eof196;
case 196:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 65: goto st197;
		case 97: goto st197;
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
		if ( (*p) < 66 ) {
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
st197:
	if ( ++p == pe )
		goto _test_eof197;
case 197:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 78: goto st198;
		case 110: goto st198;
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
st198:
	if ( ++p == pe )
		goto _test_eof198;
case 198:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 83: goto st199;
		case 115: goto st199;
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
st199:
	if ( ++p == pe )
		goto _test_eof199;
case 199:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 70: goto st200;
		case 102: goto st200;
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
st200:
	if ( ++p == pe )
		goto _test_eof200;
case 200:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 69: goto st201;
		case 101: goto st201;
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
st201:
	if ( ++p == pe )
		goto _test_eof201;
case 201:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 82: goto st202;
		case 114: goto st202;
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
st202:
	if ( ++p == pe )
		goto _test_eof202;
case 202:
	switch( (*p) ) {
		case 33: goto st114;
		case 45: goto st203;
		case 46: goto st114;
		case 58: goto tr147;
		case 124: goto st114;
		case 126: goto st114;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st114;
		} else if ( (*p) >= 35 )
			goto st114;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st114;
		} else if ( (*p) >= 65 )
			goto st114;
	} else
		goto st114;
	goto st0;
st203:
	if ( ++p == pe )
		goto _test_eof203;
case 203:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 69: goto st204;
		case 101: goto st204;
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
st204:
	if ( ++p == pe )
		goto _test_eof204;
case 204:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 78: goto st205;
		case 110: goto st205;
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
st205:
	if ( ++p == pe )
		goto _test_eof205;
case 205:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 67: goto st206;
		case 99: goto st206;
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
st206:
	if ( ++p == pe )
		goto _test_eof206;
case 206:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 79: goto st207;
		case 111: goto st207;
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
st207:
	if ( ++p == pe )
		goto _test_eof207;
case 207:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 68: goto st208;
		case 100: goto st208;
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
st208:
	if ( ++p == pe )
		goto _test_eof208;
case 208:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 73: goto st209;
		case 105: goto st209;
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
st209:
	if ( ++p == pe )
		goto _test_eof209;
case 209:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 78: goto st210;
		case 110: goto st210;
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
st210:
	if ( ++p == pe )
		goto _test_eof210;
case 210:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr147;
		case 71: goto st211;
		case 103: goto st211;
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
st211:
	if ( ++p == pe )
		goto _test_eof211;
case 211:
	switch( (*p) ) {
		case 33: goto st114;
		case 58: goto tr273;
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
tr273:
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
	goto st212;
st212:
	if ( ++p == pe )
		goto _test_eof212;
case 212:
#line 5123 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 9: goto st212;
		case 13: goto tr150;
		case 32: goto st212;
		case 67: goto tr275;
		case 99: goto tr275;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr148;
tr275:
#line 7 "src/panda/protocol/http/MessageParser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st213;
st213:
	if ( ++p == pe )
		goto _test_eof213;
case 213:
#line 5146 "src/panda/protocol/http/MessageParser.cc"
	switch( (*p) ) {
		case 13: goto tr152;
		case 72: goto st214;
		case 104: goto st214;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st214:
	if ( ++p == pe )
		goto _test_eof214;
case 214:
	switch( (*p) ) {
		case 13: goto tr152;
		case 85: goto st215;
		case 117: goto st215;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st215:
	if ( ++p == pe )
		goto _test_eof215;
case 215:
	switch( (*p) ) {
		case 13: goto tr152;
		case 78: goto st216;
		case 110: goto st216;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st216:
	if ( ++p == pe )
		goto _test_eof216;
case 216:
	switch( (*p) ) {
		case 13: goto tr152;
		case 75: goto st217;
		case 107: goto st217;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st217:
	if ( ++p == pe )
		goto _test_eof217;
case 217:
	switch( (*p) ) {
		case 13: goto tr152;
		case 69: goto st218;
		case 101: goto st218;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st218:
	if ( ++p == pe )
		goto _test_eof218;
case 218:
	switch( (*p) ) {
		case 13: goto tr152;
		case 68: goto st219;
		case 100: goto st219;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st116;
st219:
	if ( ++p == pe )
		goto _test_eof219;
case 219:
	switch( (*p) ) {
		case 9: goto tr282;
		case 13: goto tr283;
		case 32: goto tr282;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
st220:
	if ( ++p == pe )
		goto _test_eof220;
case 220:
	if ( (*p) == 13 )
		goto tr284;
	goto st0;
st221:
	if ( ++p == pe )
		goto _test_eof221;
case 221:
	if ( (*p) == 69 )
		goto st222;
	goto st0;
st222:
	if ( ++p == pe )
		goto _test_eof222;
case 222:
	if ( (*p) == 76 )
		goto st223;
	goto st0;
st223:
	if ( ++p == pe )
		goto _test_eof223;
case 223:
	if ( (*p) == 69 )
		goto st224;
	goto st0;
st224:
	if ( ++p == pe )
		goto _test_eof224;
case 224:
	if ( (*p) == 84 )
		goto st225;
	goto st0;
st225:
	if ( ++p == pe )
		goto _test_eof225;
case 225:
	if ( (*p) == 69 )
		goto st226;
	goto st0;
st226:
	if ( ++p == pe )
		goto _test_eof226;
case 226:
	if ( (*p) == 32 )
		goto tr290;
	goto st0;
st227:
	if ( ++p == pe )
		goto _test_eof227;
case 227:
	if ( (*p) == 69 )
		goto st228;
	goto st0;
st228:
	if ( ++p == pe )
		goto _test_eof228;
case 228:
	if ( (*p) == 84 )
		goto st229;
	goto st0;
st229:
	if ( ++p == pe )
		goto _test_eof229;
case 229:
	if ( (*p) == 32 )
		goto tr293;
	goto st0;
st230:
	if ( ++p == pe )
		goto _test_eof230;
case 230:
	if ( (*p) == 69 )
		goto st231;
	goto st0;
st231:
	if ( ++p == pe )
		goto _test_eof231;
case 231:
	if ( (*p) == 65 )
		goto st232;
	goto st0;
st232:
	if ( ++p == pe )
		goto _test_eof232;
case 232:
	if ( (*p) == 68 )
		goto st233;
	goto st0;
st233:
	if ( ++p == pe )
		goto _test_eof233;
case 233:
	if ( (*p) == 32 )
		goto tr297;
	goto st0;
st234:
	if ( ++p == pe )
		goto _test_eof234;
case 234:
	if ( (*p) == 80 )
		goto st235;
	goto st0;
st235:
	if ( ++p == pe )
		goto _test_eof235;
case 235:
	if ( (*p) == 84 )
		goto st236;
	goto st0;
st236:
	if ( ++p == pe )
		goto _test_eof236;
case 236:
	if ( (*p) == 73 )
		goto st237;
	goto st0;
st237:
	if ( ++p == pe )
		goto _test_eof237;
case 237:
	if ( (*p) == 79 )
		goto st238;
	goto st0;
st238:
	if ( ++p == pe )
		goto _test_eof238;
case 238:
	if ( (*p) == 78 )
		goto st239;
	goto st0;
st239:
	if ( ++p == pe )
		goto _test_eof239;
case 239:
	if ( (*p) == 83 )
		goto st240;
	goto st0;
st240:
	if ( ++p == pe )
		goto _test_eof240;
case 240:
	if ( (*p) == 32 )
		goto tr304;
	goto st0;
st241:
	if ( ++p == pe )
		goto _test_eof241;
case 241:
	switch( (*p) ) {
		case 79: goto st242;
		case 85: goto st245;
	}
	goto st0;
st242:
	if ( ++p == pe )
		goto _test_eof242;
case 242:
	if ( (*p) == 83 )
		goto st243;
	goto st0;
st243:
	if ( ++p == pe )
		goto _test_eof243;
case 243:
	if ( (*p) == 84 )
		goto st244;
	goto st0;
st244:
	if ( ++p == pe )
		goto _test_eof244;
case 244:
	if ( (*p) == 32 )
		goto tr309;
	goto st0;
st245:
	if ( ++p == pe )
		goto _test_eof245;
case 245:
	if ( (*p) == 84 )
		goto st246;
	goto st0;
st246:
	if ( ++p == pe )
		goto _test_eof246;
case 246:
	if ( (*p) == 32 )
		goto tr311;
	goto st0;
st247:
	if ( ++p == pe )
		goto _test_eof247;
case 247:
	if ( (*p) == 82 )
		goto st248;
	goto st0;
st248:
	if ( ++p == pe )
		goto _test_eof248;
case 248:
	if ( (*p) == 65 )
		goto st249;
	goto st0;
st249:
	if ( ++p == pe )
		goto _test_eof249;
case 249:
	if ( (*p) == 67 )
		goto st250;
	goto st0;
st250:
	if ( ++p == pe )
		goto _test_eof250;
case 250:
	if ( (*p) == 69 )
		goto st251;
	goto st0;
st251:
	if ( ++p == pe )
		goto _test_eof251;
case 251:
	if ( (*p) == 32 )
		goto tr316;
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
	_test_eof252: cs = 252; goto _test_eof; 
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
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof253: cs = 253; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof254: cs = 254; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof255: cs = 255; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof93: cs = 93; goto _test_eof; 
	_test_eof94: cs = 94; goto _test_eof; 
	_test_eof95: cs = 95; goto _test_eof; 
	_test_eof96: cs = 96; goto _test_eof; 
	_test_eof97: cs = 97; goto _test_eof; 
	_test_eof98: cs = 98; goto _test_eof; 
	_test_eof99: cs = 99; goto _test_eof; 
	_test_eof100: cs = 100; goto _test_eof; 
	_test_eof101: cs = 101; goto _test_eof; 
	_test_eof102: cs = 102; goto _test_eof; 
	_test_eof103: cs = 103; goto _test_eof; 
	_test_eof104: cs = 104; goto _test_eof; 
	_test_eof105: cs = 105; goto _test_eof; 
	_test_eof106: cs = 106; goto _test_eof; 
	_test_eof107: cs = 107; goto _test_eof; 
	_test_eof108: cs = 108; goto _test_eof; 
	_test_eof109: cs = 109; goto _test_eof; 
	_test_eof110: cs = 110; goto _test_eof; 
	_test_eof111: cs = 111; goto _test_eof; 
	_test_eof112: cs = 112; goto _test_eof; 
	_test_eof113: cs = 113; goto _test_eof; 
	_test_eof256: cs = 256; goto _test_eof; 
	_test_eof114: cs = 114; goto _test_eof; 
	_test_eof115: cs = 115; goto _test_eof; 
	_test_eof116: cs = 116; goto _test_eof; 
	_test_eof117: cs = 117; goto _test_eof; 
	_test_eof118: cs = 118; goto _test_eof; 
	_test_eof119: cs = 119; goto _test_eof; 
	_test_eof120: cs = 120; goto _test_eof; 
	_test_eof121: cs = 121; goto _test_eof; 
	_test_eof122: cs = 122; goto _test_eof; 
	_test_eof123: cs = 123; goto _test_eof; 
	_test_eof124: cs = 124; goto _test_eof; 
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

	_test_eof: {}
	_out: {}
	}

#line 149 "src/panda/protocol/http/MessageParser.rl"
    return p - ps;
}

#endif

}}}
