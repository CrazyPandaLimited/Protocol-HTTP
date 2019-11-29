
#line 1 "src/panda/protocol/http/Parser.rl"
#include "Parser.h"


#line 134 "src/panda/protocol/http/Parser.rl"


namespace panda { namespace protocol { namespace http {


#line 13 "src/panda/protocol/http/Parser.cc"
static const int http_parser_start = 1;
static const int http_parser_first_final = 250;
static const int http_parser_error = 0;

static const int http_parser_en_first_chunk = 112;
static const int http_parser_en_chunk = 122;
static const int http_parser_en_chunk_trailer = 134;
static const int http_parser_en_request = 140;
static const int http_parser_en_response = 1;


#line 139 "src/panda/protocol/http/Parser.rl"

#ifndef PARSER_CONSTANTS

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

size_t Parser::machine_exec (const string& buffer, size_t off) {
    const char* ps = buffer.data();
    const char* p  = ps + off;
    const char* pe = ps + buffer.size();
    
#line 50 "src/panda/protocol/http/Parser.cc"
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
		case 49: goto st111;
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
#line 70 "src/panda/protocol/http/Parser.rl"
	{message->http_version = 10;}
	goto st10;
tr131:
#line 70 "src/panda/protocol/http/Parser.rl"
	{message->http_version = 11;}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 133 "src/panda/protocol/http/Parser.cc"
	if ( 49 <= (*p) && (*p) <= 57 )
		goto tr11;
	goto st0;
tr11:
#line 127 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(response->code)}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 145 "src/panda/protocol/http/Parser.cc"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr12;
	goto st0;
tr12:
#line 127 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(response->code)}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 157 "src/panda/protocol/http/Parser.cc"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr13;
	goto st0;
tr13:
#line 127 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(response->code)}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 169 "src/panda/protocol/http/Parser.cc"
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
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 198 "src/panda/protocol/http/Parser.cc"
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
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
#line 128 "src/panda/protocol/http/Parser.rl"
	{SAVE(response->message)}
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr18:
#line 128 "src/panda/protocol/http/Parser.rl"
	{SAVE(response->message)}
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr30:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr32:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr65:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
#line 50 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 46 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr69:
#line 50 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 46 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr130:
#line 96 "src/panda/protocol/http/Parser.rl"
	{message->chunked = true;}
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 331 "src/panda/protocol/http/Parser.cc"
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
		case 83: goto tr23;
		case 84: goto tr24;
		case 99: goto tr22;
		case 115: goto tr23;
		case 116: goto tr24;
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
		goto tr25;
	goto st0;
tr25:
#line 38 "src/panda/protocol/http/Parser.rl"
	{
        {p++; cs = 250; goto _out;}
    }
	goto st250;
st250:
	if ( ++p == pe )
		goto _test_eof250;
case 250:
#line 386 "src/panda/protocol/http/Parser.cc"
	goto st0;
tr21:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 399 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
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
tr27:
#line 91 "src/panda/protocol/http/Parser.rl"
	{SAVE(field_name)}
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 436 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st20;
		case 13: goto tr30;
		case 32: goto st20;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr28;
tr28:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st21;
tr129:
#line 96 "src/panda/protocol/http/Parser.rl"
	{message->chunked = true;}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 461 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr32;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
tr22:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
#line 483 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
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
		case 58: goto tr27;
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
		case 58: goto tr27;
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
		case 58: goto tr27;
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
		case 58: goto tr27;
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
		case 58: goto tr27;
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
		case 58: goto tr27;
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
		case 58: goto tr27;
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
		case 58: goto tr27;
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
		case 58: goto tr27;
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
		case 58: goto tr27;
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
		case 58: goto tr27;
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
		case 58: goto tr27;
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
		case 58: goto tr46;
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
tr46:
#line 91 "src/panda/protocol/http/Parser.rl"
	{SAVE(field_name)}
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st36;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
#line 907 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st36;
		case 13: goto tr30;
		case 32: goto st36;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr48;
	} else if ( (*p) >= 0 )
		goto st0;
	goto tr28;
tr48:
#line 23 "src/panda/protocol/http/Parser.rl"
	{
        if (has_content_length) {
            cs = http_parser_error;
            set_error(errc::multiple_content_length);
            {p++; cs = 37; goto _out;}
        }
        has_content_length = true;
    }
#line 95 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(content_length)}
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st37;
tr49:
#line 95 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(content_length)}
	goto st37;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
#line 946 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr32;
		case 127: goto st0;
	}
	if ( (*p) < 10 ) {
		if ( 0 <= (*p) && (*p) <= 8 )
			goto st0;
	} else if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr49;
	} else
		goto st0;
	goto st21;
tr23:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st38;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
#line 971 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 69: goto st39;
		case 101: goto st39;
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
		case 58: goto tr27;
		case 84: goto st40;
		case 116: goto st40;
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
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 33: goto st19;
		case 45: goto st41;
		case 46: goto st19;
		case 58: goto tr27;
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
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 67: goto st42;
		case 99: goto st42;
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
		case 58: goto tr27;
		case 79: goto st43;
		case 111: goto st43;
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
		case 58: goto tr27;
		case 79: goto st44;
		case 111: goto st44;
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
		case 58: goto tr27;
		case 75: goto st45;
		case 107: goto st45;
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
		case 58: goto tr27;
		case 73: goto st46;
		case 105: goto st46;
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
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
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
		case 58: goto tr59;
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
tr59:
#line 91 "src/panda/protocol/http/Parser.rl"
	{SAVE(field_name)}
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st48;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
#line 1275 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st20;
		case 13: goto tr30;
		case 32: goto st49;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr28;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 9: goto st20;
		case 13: goto tr30;
		case 32: goto st20;
		case 33: goto tr61;
		case 124: goto tr61;
		case 126: goto tr61;
		case 127: goto st0;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < 35 ) {
			if ( 0 <= (*p) && (*p) <= 31 )
				goto st0;
		} else if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr61;
		} else
			goto tr61;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr61;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr61;
		} else
			goto tr61;
	} else
		goto tr61;
	goto tr28;
tr61:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st50;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
#line 1334 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr32;
		case 33: goto st50;
		case 61: goto tr63;
		case 124: goto st50;
		case 126: goto st50;
		case 127: goto st0;
	}
	if ( (*p) < 42 ) {
		if ( (*p) < 10 ) {
			if ( 0 <= (*p) && (*p) <= 8 )
				goto st0;
		} else if ( (*p) > 31 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st50;
		} else
			goto st0;
	} else if ( (*p) > 43 ) {
		if ( (*p) < 48 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto st50;
		} else if ( (*p) > 57 ) {
			if ( (*p) > 90 ) {
				if ( 94 <= (*p) && (*p) <= 122 )
					goto st50;
			} else if ( (*p) >= 65 )
				goto st50;
		} else
			goto st50;
	} else
		goto st50;
	goto st21;
tr63:
#line 50 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 46 "src/panda/protocol/http/Parser.rl"
	{
        
    }
	goto st51;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
#line 1381 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr65;
		case 32: goto st21;
		case 34: goto tr66;
		case 44: goto st21;
		case 59: goto tr67;
		case 92: goto st21;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr64;
tr64:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
	goto st52;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
#line 1405 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 32: goto st21;
		case 34: goto st21;
		case 44: goto st21;
		case 59: goto tr70;
		case 92: goto st21;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st52;
tr70:
#line 50 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 46 "src/panda/protocol/http/Parser.rl"
	{
        
    }
	goto st53;
tr67:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
#line 50 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 46 "src/panda/protocol/http/Parser.rl"
	{
        
    }
	goto st53;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
#line 1447 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr32;
		case 32: goto st54;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st21;
		case 68: goto tr73;
		case 69: goto tr74;
		case 77: goto tr75;
		case 80: goto tr76;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr72;
tr72:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
	goto st55;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
#line 1486 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
tr73:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
	goto st56;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
#line 1506 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 111: goto st57;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 109: goto st58;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 97: goto st59;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 105: goto st60;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 110: goto st61;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 61: goto st62;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 31 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto tr72;
		} else if ( (*p) >= 0 )
			goto st0;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr72;
		} else if ( (*p) >= 65 )
			goto tr72;
	} else
		goto tr72;
	goto st55;
tr74:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
	goto st63;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
#line 1622 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 120: goto st64;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 112: goto st65;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 105: goto st66;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 114: goto st67;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 101: goto st68;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 115: goto st69;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 61: goto st70;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 32: goto tr72;
		case 44: goto tr72;
		case 59: goto tr70;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( 0 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr72;
		} else if ( (*p) >= 65 )
			goto tr72;
	} else
		goto tr72;
	goto st55;
tr75:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
	goto st71;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
#line 1751 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 97: goto st72;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 120: goto st73;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 45: goto st74;
		case 59: goto tr70;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 65: goto st75;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 103: goto st76;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 101: goto st77;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 61: goto st78;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto tr72;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st55;
tr76:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
	goto st79;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
#line 1872 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 97: goto st80;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 116: goto st81;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 104: goto st82;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 61: goto st83;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr69;
		case 59: goto tr70;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr72;
tr66:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
	goto st84;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
#line 1948 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 32: goto st21;
		case 34: goto st85;
		case 44: goto st21;
		case 59: goto st21;
		case 92: goto st21;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st84;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	switch( (*p) ) {
		case 13: goto tr69;
		case 59: goto tr70;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
tr24:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st86;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
#line 1988 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 82: goto st87;
		case 114: goto st87;
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
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 65: goto st88;
		case 97: goto st88;
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
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 78: goto st89;
		case 110: goto st89;
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
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 83: goto st90;
		case 115: goto st90;
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
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 70: goto st91;
		case 102: goto st91;
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
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 69: goto st92;
		case 101: goto st92;
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
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 82: goto st93;
		case 114: goto st93;
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
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	switch( (*p) ) {
		case 33: goto st19;
		case 45: goto st94;
		case 46: goto st19;
		case 58: goto tr27;
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
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 69: goto st95;
		case 101: goto st95;
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
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 78: goto st96;
		case 110: goto st96;
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
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 67: goto st97;
		case 99: goto st97;
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
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 79: goto st98;
		case 111: goto st98;
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
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 68: goto st99;
		case 100: goto st99;
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
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 73: goto st100;
		case 105: goto st100;
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
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 78: goto st101;
		case 110: goto st101;
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
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 71: goto st102;
		case 103: goto st102;
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
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr120;
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
tr120:
#line 91 "src/panda/protocol/http/Parser.rl"
	{SAVE(field_name)}
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st103;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
#line 2502 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st103;
		case 13: goto tr30;
		case 32: goto st103;
		case 67: goto tr122;
		case 99: goto tr122;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr28;
tr122:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st104;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
#line 2525 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr32;
		case 72: goto st105;
		case 104: goto st105;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
	switch( (*p) ) {
		case 13: goto tr32;
		case 85: goto st106;
		case 117: goto st106;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
	switch( (*p) ) {
		case 13: goto tr32;
		case 78: goto st107;
		case 110: goto st107;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
	switch( (*p) ) {
		case 13: goto tr32;
		case 75: goto st108;
		case 107: goto st108;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	switch( (*p) ) {
		case 13: goto tr32;
		case 69: goto st109;
		case 101: goto st109;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
	switch( (*p) ) {
		case 13: goto tr32;
		case 68: goto st110;
		case 100: goto st110;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
	switch( (*p) ) {
		case 9: goto tr129;
		case 13: goto tr130;
		case 32: goto tr129;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st21;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	if ( (*p) == 32 )
		goto tr131;
	goto st0;
case 112:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr132;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr132;
	} else
		goto tr132;
	goto st0;
tr132:
#line 100 "src/panda/protocol/http/Parser.rl"
	{chunk_length = 0;}
#line 100 "src/panda/protocol/http/Parser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st113;
tr134:
#line 100 "src/panda/protocol/http/Parser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st113;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
#line 2662 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto st114;
		case 59: goto st115;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr134;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr134;
	} else
		goto tr134;
	goto st0;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	if ( (*p) == 10 )
		goto tr136;
	goto st0;
tr136:
#line 38 "src/panda/protocol/http/Parser.rl"
	{
        {p++; cs = 251; goto _out;}
    }
	goto st251;
st251:
	if ( ++p == pe )
		goto _test_eof251;
case 251:
#line 2693 "src/panda/protocol/http/Parser.cc"
	goto st0;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
	switch( (*p) ) {
		case 33: goto st116;
		case 124: goto st116;
		case 126: goto st116;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st116;
		} else if ( (*p) >= 35 )
			goto st116;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st116;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st116;
		} else
			goto st116;
	} else
		goto st116;
	goto st0;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
	switch( (*p) ) {
		case 13: goto st114;
		case 33: goto st116;
		case 59: goto st115;
		case 61: goto st117;
		case 124: goto st116;
		case 126: goto st116;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st116;
		} else if ( (*p) >= 35 )
			goto st116;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st116;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st116;
		} else
			goto st116;
	} else
		goto st116;
	goto st0;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
	switch( (*p) ) {
		case 34: goto st119;
		case 124: goto st118;
		case 126: goto st118;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st118;
		} else if ( (*p) >= 33 )
			goto st118;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st118;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st118;
		} else
			goto st118;
	} else
		goto st118;
	goto st0;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
	switch( (*p) ) {
		case 13: goto st114;
		case 33: goto st118;
		case 59: goto st115;
		case 124: goto st118;
		case 126: goto st118;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st118;
		} else if ( (*p) >= 35 )
			goto st118;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st118;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st118;
		} else
			goto st118;
	} else
		goto st118;
	goto st0;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
	switch( (*p) ) {
		case 34: goto st120;
		case 92: goto st121;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st119;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
	switch( (*p) ) {
		case 13: goto st114;
		case 59: goto st115;
	}
	goto st0;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
	if ( (*p) == 127 )
		goto st0;
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st119;
case 122:
	if ( (*p) == 13 )
		goto st123;
	goto st0;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
	if ( (*p) == 10 )
		goto st124;
	goto st0;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr145;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr145;
	} else
		goto tr145;
	goto st0;
tr145:
#line 100 "src/panda/protocol/http/Parser.rl"
	{chunk_length = 0;}
#line 100 "src/panda/protocol/http/Parser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st125;
tr147:
#line 100 "src/panda/protocol/http/Parser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st125;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
#line 2882 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto st126;
		case 59: goto st127;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr147;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr147;
	} else
		goto tr147;
	goto st0;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
	if ( (*p) == 10 )
		goto tr149;
	goto st0;
tr149:
#line 38 "src/panda/protocol/http/Parser.rl"
	{
        {p++; cs = 252; goto _out;}
    }
	goto st252;
st252:
	if ( ++p == pe )
		goto _test_eof252;
case 252:
#line 2913 "src/panda/protocol/http/Parser.cc"
	goto st0;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
	switch( (*p) ) {
		case 33: goto st128;
		case 124: goto st128;
		case 126: goto st128;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st128;
		} else if ( (*p) >= 35 )
			goto st128;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st128;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st128;
		} else
			goto st128;
	} else
		goto st128;
	goto st0;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
	switch( (*p) ) {
		case 13: goto st126;
		case 33: goto st128;
		case 59: goto st127;
		case 61: goto st129;
		case 124: goto st128;
		case 126: goto st128;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st128;
		} else if ( (*p) >= 35 )
			goto st128;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st128;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st128;
		} else
			goto st128;
	} else
		goto st128;
	goto st0;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
	switch( (*p) ) {
		case 34: goto st131;
		case 124: goto st130;
		case 126: goto st130;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st130;
		} else if ( (*p) >= 33 )
			goto st130;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st130;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st130;
		} else
			goto st130;
	} else
		goto st130;
	goto st0;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
	switch( (*p) ) {
		case 13: goto st126;
		case 33: goto st130;
		case 59: goto st127;
		case 124: goto st130;
		case 126: goto st130;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st130;
		} else if ( (*p) >= 35 )
			goto st130;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st130;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st130;
		} else
			goto st130;
	} else
		goto st130;
	goto st0;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
	switch( (*p) ) {
		case 34: goto st132;
		case 92: goto st133;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st131;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
	switch( (*p) ) {
		case 13: goto st126;
		case 59: goto st127;
	}
	goto st0;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
	if ( (*p) == 127 )
		goto st0;
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st131;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
	switch( (*p) ) {
		case 13: goto st135;
		case 33: goto tr157;
		case 124: goto tr157;
		case 126: goto tr157;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr157;
		} else if ( (*p) >= 35 )
			goto tr157;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr157;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr157;
		} else
			goto tr157;
	} else
		goto tr157;
	goto st0;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
	if ( (*p) == 10 )
		goto tr158;
	goto st0;
tr158:
#line 38 "src/panda/protocol/http/Parser.rl"
	{
        {p++; cs = 253; goto _out;}
    }
	goto st253;
st253:
	if ( ++p == pe )
		goto _test_eof253;
case 253:
#line 3109 "src/panda/protocol/http/Parser.cc"
	goto st0;
tr157:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st136;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
#line 3122 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st136;
		case 58: goto tr160;
		case 124: goto st136;
		case 126: goto st136;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st136;
		} else if ( (*p) >= 35 )
			goto st136;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st136;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st136;
		} else
			goto st136;
	} else
		goto st136;
	goto st0;
tr160:
#line 91 "src/panda/protocol/http/Parser.rl"
	{SAVE(field_name)}
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st137;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
#line 3159 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st137;
		case 13: goto tr163;
		case 32: goto st137;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr161;
tr161:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st138;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
#line 3180 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr165;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st138;
tr163:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st139;
tr165:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st139;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
#line 3228 "src/panda/protocol/http/Parser.cc"
	if ( (*p) == 10 )
		goto st134;
	goto st0;
case 140:
	switch( (*p) ) {
		case 67: goto st141;
		case 68: goto st219;
		case 71: goto st225;
		case 72: goto st228;
		case 79: goto st232;
		case 80: goto st239;
		case 84: goto st245;
	}
	goto st0;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
	if ( (*p) == 79 )
		goto st142;
	goto st0;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
	if ( (*p) == 78 )
		goto st143;
	goto st0;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
	if ( (*p) == 78 )
		goto st144;
	goto st0;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
	if ( (*p) == 69 )
		goto st145;
	goto st0;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
	if ( (*p) == 67 )
		goto st146;
	goto st0;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
	if ( (*p) == 84 )
		goto st147;
	goto st0;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
	if ( (*p) == 32 )
		goto tr180;
	goto st0;
tr180:
#line 117 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::CONNECT; }
	goto st148;
tr279:
#line 115 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::DELETE; }
	goto st148;
tr282:
#line 111 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::GET; }
	goto st148;
tr286:
#line 112 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::HEAD; }
	goto st148;
tr293:
#line 110 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::OPTIONS; }
	goto st148;
tr298:
#line 113 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::POST; }
	goto st148;
tr300:
#line 114 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::PUT; }
	goto st148;
tr305:
#line 116 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::TRACE; }
	goto st148;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
#line 3328 "src/panda/protocol/http/Parser.cc"
	if ( 33 <= (*p) && (*p) <= 126 )
		goto tr181;
	goto st0;
tr181:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st149;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
#line 3343 "src/panda/protocol/http/Parser.cc"
	if ( (*p) == 32 )
		goto tr182;
	if ( 33 <= (*p) && (*p) <= 126 )
		goto st149;
	goto st0;
tr182:
#line 32 "src/panda/protocol/http/Parser.rl"
	{
        string target;
        SAVE(target);
        request->uri = new URI(target);
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st150;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
#line 3365 "src/panda/protocol/http/Parser.cc"
	if ( (*p) == 72 )
		goto st151;
	goto st0;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
	if ( (*p) == 84 )
		goto st152;
	goto st0;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
	if ( (*p) == 84 )
		goto st153;
	goto st0;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
	if ( (*p) == 80 )
		goto st154;
	goto st0;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
	if ( (*p) == 47 )
		goto st155;
	goto st0;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
	if ( (*p) == 49 )
		goto st156;
	goto st0;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
	if ( (*p) == 46 )
		goto st157;
	goto st0;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
	switch( (*p) ) {
		case 48: goto st158;
		case 49: goto st218;
	}
	goto st0;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
	if ( (*p) == 13 )
		goto tr193;
	goto st0;
tr193:
#line 70 "src/panda/protocol/http/Parser.rl"
	{message->http_version = 10;}
	goto st159;
tr204:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st159;
tr206:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st159;
tr235:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
#line 50 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 46 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st159;
tr240:
#line 50 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 46 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st159;
tr272:
#line 96 "src/panda/protocol/http/Parser.rl"
	{message->chunked = true;}
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st159;
tr273:
#line 70 "src/panda/protocol/http/Parser.rl"
	{message->http_version = 11;}
	goto st159;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
#line 3536 "src/panda/protocol/http/Parser.cc"
	if ( (*p) == 10 )
		goto st160;
	goto st0;
st160:
	if ( ++p == pe )
		goto _test_eof160;
case 160:
	switch( (*p) ) {
		case 13: goto st161;
		case 33: goto tr196;
		case 67: goto tr197;
		case 84: goto tr198;
		case 99: goto tr197;
		case 116: goto tr198;
		case 124: goto tr196;
		case 126: goto tr196;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr196;
		} else if ( (*p) >= 35 )
			goto tr196;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr196;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr196;
		} else
			goto tr196;
	} else
		goto tr196;
	goto st0;
st161:
	if ( ++p == pe )
		goto _test_eof161;
case 161:
	if ( (*p) == 10 )
		goto tr199;
	goto st0;
tr199:
#line 38 "src/panda/protocol/http/Parser.rl"
	{
        {p++; cs = 254; goto _out;}
    }
	goto st254;
st254:
	if ( ++p == pe )
		goto _test_eof254;
case 254:
#line 3589 "src/panda/protocol/http/Parser.cc"
	goto st0;
tr196:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st162;
st162:
	if ( ++p == pe )
		goto _test_eof162;
case 162:
#line 3602 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
tr201:
#line 91 "src/panda/protocol/http/Parser.rl"
	{SAVE(field_name)}
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st163;
st163:
	if ( ++p == pe )
		goto _test_eof163;
case 163:
#line 3639 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st163;
		case 13: goto tr204;
		case 32: goto st163;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr202;
tr202:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st164;
tr239:
#line 50 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 46 "src/panda/protocol/http/Parser.rl"
	{
        
    }
	goto st164;
tr234:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
#line 50 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 46 "src/panda/protocol/http/Parser.rl"
	{
        
    }
	goto st164;
tr271:
#line 96 "src/panda/protocol/http/Parser.rl"
	{message->chunked = true;}
	goto st164;
st164:
	if ( ++p == pe )
		goto _test_eof164;
case 164:
#line 3688 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr206;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st164;
tr197:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st165;
st165:
	if ( ++p == pe )
		goto _test_eof165;
case 165:
#line 3710 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 79: goto st166;
		case 111: goto st166;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st166:
	if ( ++p == pe )
		goto _test_eof166;
case 166:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 78: goto st167;
		case 79: goto st181;
		case 110: goto st167;
		case 111: goto st181;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st167:
	if ( ++p == pe )
		goto _test_eof167;
case 167:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 84: goto st168;
		case 116: goto st168;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st168:
	if ( ++p == pe )
		goto _test_eof168;
case 168:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 69: goto st169;
		case 101: goto st169;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st169:
	if ( ++p == pe )
		goto _test_eof169;
case 169:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 78: goto st170;
		case 110: goto st170;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st170:
	if ( ++p == pe )
		goto _test_eof170;
case 170:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 84: goto st171;
		case 116: goto st171;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st171:
	if ( ++p == pe )
		goto _test_eof171;
case 171:
	switch( (*p) ) {
		case 33: goto st162;
		case 45: goto st172;
		case 46: goto st162;
		case 58: goto tr201;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else if ( (*p) >= 65 )
			goto st162;
	} else
		goto st162;
	goto st0;
st172:
	if ( ++p == pe )
		goto _test_eof172;
case 172:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 76: goto st173;
		case 108: goto st173;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st173:
	if ( ++p == pe )
		goto _test_eof173;
case 173:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 69: goto st174;
		case 101: goto st174;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st174:
	if ( ++p == pe )
		goto _test_eof174;
case 174:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 78: goto st175;
		case 110: goto st175;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st175:
	if ( ++p == pe )
		goto _test_eof175;
case 175:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 71: goto st176;
		case 103: goto st176;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st176:
	if ( ++p == pe )
		goto _test_eof176;
case 176:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 84: goto st177;
		case 116: goto st177;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st177:
	if ( ++p == pe )
		goto _test_eof177;
case 177:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 72: goto st178;
		case 104: goto st178;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st178:
	if ( ++p == pe )
		goto _test_eof178;
case 178:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr221;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
tr221:
#line 91 "src/panda/protocol/http/Parser.rl"
	{SAVE(field_name)}
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st179;
st179:
	if ( ++p == pe )
		goto _test_eof179;
case 179:
#line 4136 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st179;
		case 13: goto tr204;
		case 32: goto st179;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr223;
	} else if ( (*p) >= 0 )
		goto st0;
	goto tr202;
tr223:
#line 23 "src/panda/protocol/http/Parser.rl"
	{
        if (has_content_length) {
            cs = http_parser_error;
            set_error(errc::multiple_content_length);
            {p++; cs = 180; goto _out;}
        }
        has_content_length = true;
    }
#line 95 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(content_length)}
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st180;
tr224:
#line 95 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(content_length)}
	goto st180;
st180:
	if ( ++p == pe )
		goto _test_eof180;
case 180:
#line 4175 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr206;
		case 127: goto st0;
	}
	if ( (*p) < 10 ) {
		if ( 0 <= (*p) && (*p) <= 8 )
			goto st0;
	} else if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr224;
	} else
		goto st0;
	goto st164;
st181:
	if ( ++p == pe )
		goto _test_eof181;
case 181:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 75: goto st182;
		case 107: goto st182;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st182:
	if ( ++p == pe )
		goto _test_eof182;
case 182:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 73: goto st183;
		case 105: goto st183;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st183:
	if ( ++p == pe )
		goto _test_eof183;
case 183:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 69: goto st184;
		case 101: goto st184;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st184:
	if ( ++p == pe )
		goto _test_eof184;
case 184:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr228;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
tr228:
#line 91 "src/panda/protocol/http/Parser.rl"
	{SAVE(field_name)}
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st185;
st185:
	if ( ++p == pe )
		goto _test_eof185;
case 185:
#line 4319 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st185;
		case 13: goto tr204;
		case 32: goto st185;
		case 33: goto tr230;
		case 124: goto tr230;
		case 126: goto tr230;
		case 127: goto st0;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < 35 ) {
			if ( 0 <= (*p) && (*p) <= 31 )
				goto st0;
		} else if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr230;
		} else
			goto tr230;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr230;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr230;
		} else
			goto tr230;
	} else
		goto tr230;
	goto tr202;
tr230:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st186;
tr243:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
	goto st186;
st186:
	if ( ++p == pe )
		goto _test_eof186;
case 186:
#line 4371 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr206;
		case 33: goto st186;
		case 61: goto tr232;
		case 124: goto st186;
		case 126: goto st186;
		case 127: goto st0;
	}
	if ( (*p) < 42 ) {
		if ( (*p) < 10 ) {
			if ( 0 <= (*p) && (*p) <= 8 )
				goto st0;
		} else if ( (*p) > 31 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st186;
		} else
			goto st0;
	} else if ( (*p) > 43 ) {
		if ( (*p) < 48 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto st186;
		} else if ( (*p) > 57 ) {
			if ( (*p) > 90 ) {
				if ( 94 <= (*p) && (*p) <= 122 )
					goto st186;
			} else if ( (*p) >= 65 )
				goto st186;
		} else
			goto st186;
	} else
		goto st186;
	goto st164;
tr232:
#line 50 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 46 "src/panda/protocol/http/Parser.rl"
	{
        
    }
	goto st187;
st187:
	if ( ++p == pe )
		goto _test_eof187;
case 187:
#line 4418 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto tr234;
		case 13: goto tr235;
		case 32: goto tr234;
		case 34: goto tr236;
		case 44: goto st164;
		case 59: goto tr237;
		case 92: goto st164;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr233;
tr233:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
	goto st188;
st188:
	if ( ++p == pe )
		goto _test_eof188;
case 188:
#line 4442 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto tr239;
		case 13: goto tr240;
		case 32: goto tr239;
		case 34: goto st164;
		case 44: goto st164;
		case 59: goto tr241;
		case 92: goto st164;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st188;
tr241:
#line 50 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 46 "src/panda/protocol/http/Parser.rl"
	{
        
    }
	goto st189;
tr237:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
#line 50 "src/panda/protocol/http/Parser.rl"
	{
        
    }
#line 46 "src/panda/protocol/http/Parser.rl"
	{
        
    }
	goto st189;
st189:
	if ( ++p == pe )
		goto _test_eof189;
case 189:
#line 4484 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr206;
		case 32: goto st190;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st164;
st190:
	if ( ++p == pe )
		goto _test_eof190;
case 190:
	switch( (*p) ) {
		case 13: goto tr206;
		case 33: goto tr243;
		case 124: goto tr243;
		case 126: goto tr243;
		case 127: goto st0;
	}
	if ( (*p) < 42 ) {
		if ( (*p) < 10 ) {
			if ( 0 <= (*p) && (*p) <= 8 )
				goto st0;
		} else if ( (*p) > 31 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto tr243;
		} else
			goto st0;
	} else if ( (*p) > 43 ) {
		if ( (*p) < 48 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto tr243;
		} else if ( (*p) > 57 ) {
			if ( (*p) > 90 ) {
				if ( 94 <= (*p) && (*p) <= 122 )
					goto tr243;
			} else if ( (*p) >= 65 )
				goto tr243;
		} else
			goto tr243;
	} else
		goto tr243;
	goto st164;
tr236:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        printf("asdfsdf\n");
    }
	goto st191;
st191:
	if ( ++p == pe )
		goto _test_eof191;
case 191:
#line 4541 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st164;
		case 13: goto tr206;
		case 32: goto st164;
		case 34: goto st192;
		case 44: goto st164;
		case 59: goto st164;
		case 92: goto st164;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st191;
st192:
	if ( ++p == pe )
		goto _test_eof192;
case 192:
	switch( (*p) ) {
		case 9: goto tr239;
		case 13: goto tr240;
		case 32: goto tr239;
		case 59: goto tr241;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st164;
tr198:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st193;
st193:
	if ( ++p == pe )
		goto _test_eof193;
case 193:
#line 4580 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 82: goto st194;
		case 114: goto st194;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st194:
	if ( ++p == pe )
		goto _test_eof194;
case 194:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 65: goto st195;
		case 97: goto st195;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 66 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st195:
	if ( ++p == pe )
		goto _test_eof195;
case 195:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 78: goto st196;
		case 110: goto st196;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st196:
	if ( ++p == pe )
		goto _test_eof196;
case 196:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 83: goto st197;
		case 115: goto st197;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st197:
	if ( ++p == pe )
		goto _test_eof197;
case 197:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 70: goto st198;
		case 102: goto st198;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st198:
	if ( ++p == pe )
		goto _test_eof198;
case 198:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 69: goto st199;
		case 101: goto st199;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st199:
	if ( ++p == pe )
		goto _test_eof199;
case 199:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 82: goto st200;
		case 114: goto st200;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st200:
	if ( ++p == pe )
		goto _test_eof200;
case 200:
	switch( (*p) ) {
		case 33: goto st162;
		case 45: goto st201;
		case 46: goto st162;
		case 58: goto tr201;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else if ( (*p) >= 65 )
			goto st162;
	} else
		goto st162;
	goto st0;
st201:
	if ( ++p == pe )
		goto _test_eof201;
case 201:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 69: goto st202;
		case 101: goto st202;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st202:
	if ( ++p == pe )
		goto _test_eof202;
case 202:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 78: goto st203;
		case 110: goto st203;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st203:
	if ( ++p == pe )
		goto _test_eof203;
case 203:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 67: goto st204;
		case 99: goto st204;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st204:
	if ( ++p == pe )
		goto _test_eof204;
case 204:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 79: goto st205;
		case 111: goto st205;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st205:
	if ( ++p == pe )
		goto _test_eof205;
case 205:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 68: goto st206;
		case 100: goto st206;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st206:
	if ( ++p == pe )
		goto _test_eof206;
case 206:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 73: goto st207;
		case 105: goto st207;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st207:
	if ( ++p == pe )
		goto _test_eof207;
case 207:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 78: goto st208;
		case 110: goto st208;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st208:
	if ( ++p == pe )
		goto _test_eof208;
case 208:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr201;
		case 71: goto st209;
		case 103: goto st209;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
st209:
	if ( ++p == pe )
		goto _test_eof209;
case 209:
	switch( (*p) ) {
		case 33: goto st162;
		case 58: goto tr262;
		case 124: goto st162;
		case 126: goto st162;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st162;
		} else if ( (*p) >= 35 )
			goto st162;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st162;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st162;
		} else
			goto st162;
	} else
		goto st162;
	goto st0;
tr262:
#line 91 "src/panda/protocol/http/Parser.rl"
	{SAVE(field_name)}
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st210;
st210:
	if ( ++p == pe )
		goto _test_eof210;
case 210:
#line 5094 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st210;
		case 13: goto tr204;
		case 32: goto st210;
		case 67: goto tr264;
		case 99: goto tr264;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr202;
tr264:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st211;
st211:
	if ( ++p == pe )
		goto _test_eof211;
case 211:
#line 5117 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr206;
		case 72: goto st212;
		case 104: goto st212;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st164;
st212:
	if ( ++p == pe )
		goto _test_eof212;
case 212:
	switch( (*p) ) {
		case 13: goto tr206;
		case 85: goto st213;
		case 117: goto st213;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st164;
st213:
	if ( ++p == pe )
		goto _test_eof213;
case 213:
	switch( (*p) ) {
		case 13: goto tr206;
		case 78: goto st214;
		case 110: goto st214;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st164;
st214:
	if ( ++p == pe )
		goto _test_eof214;
case 214:
	switch( (*p) ) {
		case 13: goto tr206;
		case 75: goto st215;
		case 107: goto st215;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st164;
st215:
	if ( ++p == pe )
		goto _test_eof215;
case 215:
	switch( (*p) ) {
		case 13: goto tr206;
		case 69: goto st216;
		case 101: goto st216;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st164;
st216:
	if ( ++p == pe )
		goto _test_eof216;
case 216:
	switch( (*p) ) {
		case 13: goto tr206;
		case 68: goto st217;
		case 100: goto st217;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st164;
st217:
	if ( ++p == pe )
		goto _test_eof217;
case 217:
	switch( (*p) ) {
		case 9: goto tr271;
		case 13: goto tr272;
		case 32: goto tr271;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st164;
st218:
	if ( ++p == pe )
		goto _test_eof218;
case 218:
	if ( (*p) == 13 )
		goto tr273;
	goto st0;
st219:
	if ( ++p == pe )
		goto _test_eof219;
case 219:
	if ( (*p) == 69 )
		goto st220;
	goto st0;
st220:
	if ( ++p == pe )
		goto _test_eof220;
case 220:
	if ( (*p) == 76 )
		goto st221;
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
	if ( (*p) == 84 )
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
	if ( (*p) == 32 )
		goto tr279;
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
	if ( (*p) == 84 )
		goto st227;
	goto st0;
st227:
	if ( ++p == pe )
		goto _test_eof227;
case 227:
	if ( (*p) == 32 )
		goto tr282;
	goto st0;
st228:
	if ( ++p == pe )
		goto _test_eof228;
case 228:
	if ( (*p) == 69 )
		goto st229;
	goto st0;
st229:
	if ( ++p == pe )
		goto _test_eof229;
case 229:
	if ( (*p) == 65 )
		goto st230;
	goto st0;
st230:
	if ( ++p == pe )
		goto _test_eof230;
case 230:
	if ( (*p) == 68 )
		goto st231;
	goto st0;
st231:
	if ( ++p == pe )
		goto _test_eof231;
case 231:
	if ( (*p) == 32 )
		goto tr286;
	goto st0;
st232:
	if ( ++p == pe )
		goto _test_eof232;
case 232:
	if ( (*p) == 80 )
		goto st233;
	goto st0;
st233:
	if ( ++p == pe )
		goto _test_eof233;
case 233:
	if ( (*p) == 84 )
		goto st234;
	goto st0;
st234:
	if ( ++p == pe )
		goto _test_eof234;
case 234:
	if ( (*p) == 73 )
		goto st235;
	goto st0;
st235:
	if ( ++p == pe )
		goto _test_eof235;
case 235:
	if ( (*p) == 79 )
		goto st236;
	goto st0;
st236:
	if ( ++p == pe )
		goto _test_eof236;
case 236:
	if ( (*p) == 78 )
		goto st237;
	goto st0;
st237:
	if ( ++p == pe )
		goto _test_eof237;
case 237:
	if ( (*p) == 83 )
		goto st238;
	goto st0;
st238:
	if ( ++p == pe )
		goto _test_eof238;
case 238:
	if ( (*p) == 32 )
		goto tr293;
	goto st0;
st239:
	if ( ++p == pe )
		goto _test_eof239;
case 239:
	switch( (*p) ) {
		case 79: goto st240;
		case 85: goto st243;
	}
	goto st0;
st240:
	if ( ++p == pe )
		goto _test_eof240;
case 240:
	if ( (*p) == 83 )
		goto st241;
	goto st0;
st241:
	if ( ++p == pe )
		goto _test_eof241;
case 241:
	if ( (*p) == 84 )
		goto st242;
	goto st0;
st242:
	if ( ++p == pe )
		goto _test_eof242;
case 242:
	if ( (*p) == 32 )
		goto tr298;
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
		goto tr300;
	goto st0;
st245:
	if ( ++p == pe )
		goto _test_eof245;
case 245:
	if ( (*p) == 82 )
		goto st246;
	goto st0;
st246:
	if ( ++p == pe )
		goto _test_eof246;
case 246:
	if ( (*p) == 65 )
		goto st247;
	goto st0;
st247:
	if ( ++p == pe )
		goto _test_eof247;
case 247:
	if ( (*p) == 67 )
		goto st248;
	goto st0;
st248:
	if ( ++p == pe )
		goto _test_eof248;
case 248:
	if ( (*p) == 69 )
		goto st249;
	goto st0;
st249:
	if ( ++p == pe )
		goto _test_eof249;
case 249:
	if ( (*p) == 32 )
		goto tr305;
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
	_test_eof250: cs = 250; goto _test_eof; 
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
	_test_eof113: cs = 113; goto _test_eof; 
	_test_eof114: cs = 114; goto _test_eof; 
	_test_eof251: cs = 251; goto _test_eof; 
	_test_eof115: cs = 115; goto _test_eof; 
	_test_eof116: cs = 116; goto _test_eof; 
	_test_eof117: cs = 117; goto _test_eof; 
	_test_eof118: cs = 118; goto _test_eof; 
	_test_eof119: cs = 119; goto _test_eof; 
	_test_eof120: cs = 120; goto _test_eof; 
	_test_eof121: cs = 121; goto _test_eof; 
	_test_eof123: cs = 123; goto _test_eof; 
	_test_eof124: cs = 124; goto _test_eof; 
	_test_eof125: cs = 125; goto _test_eof; 
	_test_eof126: cs = 126; goto _test_eof; 
	_test_eof252: cs = 252; goto _test_eof; 
	_test_eof127: cs = 127; goto _test_eof; 
	_test_eof128: cs = 128; goto _test_eof; 
	_test_eof129: cs = 129; goto _test_eof; 
	_test_eof130: cs = 130; goto _test_eof; 
	_test_eof131: cs = 131; goto _test_eof; 
	_test_eof132: cs = 132; goto _test_eof; 
	_test_eof133: cs = 133; goto _test_eof; 
	_test_eof134: cs = 134; goto _test_eof; 
	_test_eof135: cs = 135; goto _test_eof; 
	_test_eof253: cs = 253; goto _test_eof; 
	_test_eof136: cs = 136; goto _test_eof; 
	_test_eof137: cs = 137; goto _test_eof; 
	_test_eof138: cs = 138; goto _test_eof; 
	_test_eof139: cs = 139; goto _test_eof; 
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
	_test_eof254: cs = 254; goto _test_eof; 
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

	_test_eof: {}
	_out: {}
	}

#line 163 "src/panda/protocol/http/Parser.rl"
    return p - ps;
}

#endif

}}}
