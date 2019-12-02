
#line 1 "src/panda/protocol/http/Parser.rl"
#include "Parser.h"


#line 211 "src/panda/protocol/http/Parser.rl"


namespace panda { namespace protocol { namespace http {


#line 13 "src/panda/protocol/http/Parser.cc"
static const int http_parser_start = 1;
static const int http_parser_first_final = 289;
static const int http_parser_error = 0;

static const int http_parser_en_first_chunk = 151;
static const int http_parser_en_chunk = 161;
static const int http_parser_en_chunk_trailer = 173;
static const int http_parser_en_request = 179;
static const int http_parser_en_response = 1;


#line 216 "src/panda/protocol/http/Parser.rl"

#ifndef PARSER_CONSTANTS

#define ADD_DIGIT(dest) \
    dest *= 10;         \
    dest += *p - '0';
    
#define ADD_XDIGIT(dest) \
    char fc = *p | 0x20; \
    dest *= 16;          \
    dest += fc >= 'a' ? (fc - 'a' + 10) : (fc - '0');

#define _SAVE(dest, mark, acc)                                  \
    if (mark != -1) dest = buffer.substr(mark, p - ps - mark);  \
    else {                                                      \
        dest = std::move(acc);                                  \
        dest.append(ps, p - ps);                                \
    }

#define SAVE(dest)    _SAVE(dest, mark, acc)
#define SUBSAVE(dest) _SAVE(dest, submark, subacc)

size_t Parser::machine_exec (const string& buffer, size_t off) {
    const char* ps = buffer.data();
    const char* p  = ps + off;
    const char* pe = ps + buffer.size();
    
#line 53 "src/panda/protocol/http/Parser.cc"
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
		case 49: goto st150;
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
#line 148 "src/panda/protocol/http/Parser.rl"
	{message->http_version = 10;}
	goto st10;
tr192:
#line 148 "src/panda/protocol/http/Parser.rl"
	{message->http_version = 11;}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 136 "src/panda/protocol/http/Parser.cc"
	if ( 49 <= (*p) && (*p) <= 57 )
		goto tr11;
	goto st0;
tr11:
#line 204 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(response->code)}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 148 "src/panda/protocol/http/Parser.cc"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr12;
	goto st0;
tr12:
#line 204 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(response->code)}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 160 "src/panda/protocol/http/Parser.cc"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr13;
	goto st0;
tr13:
#line 204 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(response->code)}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 172 "src/panda/protocol/http/Parser.cc"
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
#line 201 "src/panda/protocol/http/Parser.cc"
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
#line 205 "src/panda/protocol/http/Parser.rl"
	{SAVE(response->message)}
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr18:
#line 205 "src/panda/protocol/http/Parser.rl"
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
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr32:
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr65:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
#line 68 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._value;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr69:
#line 68 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._value;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr87:
#line 73 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._domain;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr97:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
#line 93 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._expires;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr100:
#line 93 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._expires;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr110:
#line 102 "src/panda/protocol/http/Parser.rl"
	{
        response->cookies.fields.back().value._http_only = true;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr127:
#line 78 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._path;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr137:
#line 106 "src/panda/protocol/http/Parser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Strict;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr145:
#line 110 "src/panda/protocol/http/Parser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Lax;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr150:
#line 114 "src/panda/protocol/http/Parser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::None;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr161:
#line 98 "src/panda/protocol/http/Parser.rl"
	{
        response->cookies.fields.back().value._secure = true;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st16;
tr191:
#line 173 "src/panda/protocol/http/Parser.rl"
	{message->chunked = true;}
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
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
#line 538 "src/panda/protocol/http/Parser.cc"
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
#line 124 "src/panda/protocol/http/Parser.rl"
	{
        {p++; cs = 289; goto _out;}
    }
	goto st289;
st289:
	if ( ++p == pe )
		goto _test_eof289;
case 289:
#line 593 "src/panda/protocol/http/Parser.cc"
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
#line 606 "src/panda/protocol/http/Parser.cc"
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
#line 24 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 650 "src/panda/protocol/http/Parser.cc"
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
tr190:
#line 173 "src/panda/protocol/http/Parser.rl"
	{message->chunked = true;}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 675 "src/panda/protocol/http/Parser.cc"
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
#line 697 "src/panda/protocol/http/Parser.cc"
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
#line 24 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st36;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
#line 1128 "src/panda/protocol/http/Parser.cc"
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
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        if (has_content_length) {
            cs = http_parser_error;
            set_error(errc::multiple_content_length);
            {p++; cs = 37; goto _out;}
        }
        has_content_length = true;
    }
#line 172 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(content_length)}
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st37;
tr49:
#line 172 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(content_length)}
	goto st37;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
#line 1167 "src/panda/protocol/http/Parser.cc"
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
#line 1192 "src/panda/protocol/http/Parser.cc"
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
#line 24 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st48;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
#line 1503 "src/panda/protocol/http/Parser.cc"
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
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
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
#line 1563 "src/panda/protocol/http/Parser.cc"
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
#line 62 "src/panda/protocol/http/Parser.rl"
	{
        string v;
        SUBSAVE(v);
        response->cookies.add(v, {});
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
	goto st51;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
#line 1612 "src/panda/protocol/http/Parser.cc"
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
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
	goto st52;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
#line 1637 "src/panda/protocol/http/Parser.cc"
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
tr67:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
#line 68 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._value;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
	goto st53;
tr70:
#line 68 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._value;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
	goto st53;
tr89:
#line 73 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._domain;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
	goto st53;
tr99:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
#line 93 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._expires;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
	goto st53;
tr102:
#line 93 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._expires;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
	goto st53;
tr111:
#line 102 "src/panda/protocol/http/Parser.rl"
	{
        response->cookies.fields.back().value._http_only = true;
    }
	goto st53;
tr128:
#line 78 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._path;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
	goto st53;
tr138:
#line 106 "src/panda/protocol/http/Parser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Strict;
    }
	goto st53;
tr146:
#line 110 "src/panda/protocol/http/Parser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Lax;
    }
	goto st53;
tr151:
#line 114 "src/panda/protocol/http/Parser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::None;
    }
	goto st53;
tr162:
#line 98 "src/panda/protocol/http/Parser.rl"
	{
        response->cookies.fields.back().value._secure = true;
    }
	goto st53;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
#line 1761 "src/panda/protocol/http/Parser.cc"
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
		case 68: goto st56;
		case 69: goto st64;
		case 72: goto st73;
		case 77: goto st81;
		case 80: goto st90;
		case 83: goto st96;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
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
		case 13: goto tr32;
		case 59: goto st53;
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
		case 13: goto tr32;
		case 59: goto st53;
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
		case 13: goto tr32;
		case 59: goto st53;
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
		case 13: goto tr32;
		case 59: goto st53;
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
		case 13: goto tr32;
		case 59: goto st53;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 31 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto tr86;
		} else if ( (*p) >= 0 )
			goto st0;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr86;
		} else if ( (*p) >= 65 )
			goto tr86;
	} else
		goto tr86;
	goto st55;
tr86:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
	goto st63;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
#line 1925 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr87;
		case 59: goto tr89;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 31 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto st63;
		} else if ( (*p) >= 0 )
			goto st0;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st63;
		} else if ( (*p) >= 65 )
			goto st63;
	} else
		goto st63;
	goto st55;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 120: goto st65;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 112: goto st66;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 105: goto st67;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 114: goto st68;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 101: goto st69;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 115: goto st70;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 61: goto st71;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr97;
		case 32: goto tr98;
		case 44: goto tr98;
		case 59: goto tr99;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( 0 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr98;
		} else if ( (*p) >= 65 )
			goto tr98;
	} else
		goto tr98;
	goto st55;
tr98:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
	goto st72;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
#line 2080 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr100;
		case 32: goto st72;
		case 44: goto st72;
		case 59: goto tr102;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( 0 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st72;
		} else if ( (*p) >= 65 )
			goto st72;
	} else
		goto st72;
	goto st55;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 116: goto st74;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 116: goto st75;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 112: goto st76;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 79: goto st77;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 110: goto st78;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 108: goto st79;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 121: goto st80;
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
		case 13: goto tr110;
		case 59: goto tr111;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 97: goto st82;
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
		case 13: goto tr32;
		case 59: goto st53;
		case 120: goto st83;
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
		case 13: goto tr32;
		case 45: goto st84;
		case 59: goto st53;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 65: goto st85;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 103: goto st86;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 101: goto st87;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 61: goto st88;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto tr119;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st55;
tr119:
#line 83 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._max_age;
        v = 0;
    }
#line 88 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._max_age;
        ADD_DIGIT(v);
    }
	goto st89;
tr120:
#line 88 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = response->cookies.fields.back().value._max_age;
        ADD_DIGIT(v);
    }
	goto st89;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
#line 2349 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr120;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st55;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 97: goto st91;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 116: goto st92;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 104: goto st93;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 61: goto st94;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr125;
tr125:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
	goto st95;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
#line 2442 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr127;
		case 59: goto tr128;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st95;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 97: goto st97;
		case 101: goto st118;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 109: goto st98;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 101: goto st99;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 83: goto st100;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 105: goto st101;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 116: goto st102;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 101: goto st103;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr137;
		case 59: goto tr138;
		case 61: goto st104;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 76: goto st105;
		case 78: goto st108;
		case 83: goto st112;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 97: goto st106;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 120: goto st107;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr145;
		case 59: goto tr146;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 111: goto st109;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 110: goto st110;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 101: goto st111;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr150;
		case 59: goto tr151;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 116: goto st113;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 114: goto st114;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 105: goto st115;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 99: goto st116;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 116: goto st117;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr137;
		case 59: goto tr138;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 99: goto st119;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 117: goto st120;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 114: goto st121;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 59: goto st53;
		case 101: goto st122;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr161;
		case 59: goto tr162;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st55;
tr66:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
	goto st123;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
#line 2840 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st21;
		case 13: goto tr32;
		case 32: goto st21;
		case 34: goto st124;
		case 44: goto st21;
		case 59: goto st21;
		case 92: goto st21;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st123;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
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
	goto st125;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
#line 2880 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 82: goto st126;
		case 114: goto st126;
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
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 65: goto st127;
		case 97: goto st127;
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
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 78: goto st128;
		case 110: goto st128;
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
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 83: goto st129;
		case 115: goto st129;
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
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 70: goto st130;
		case 102: goto st130;
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
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 69: goto st131;
		case 101: goto st131;
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
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 82: goto st132;
		case 114: goto st132;
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
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
	switch( (*p) ) {
		case 33: goto st19;
		case 45: goto st133;
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
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 69: goto st134;
		case 101: goto st134;
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
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 78: goto st135;
		case 110: goto st135;
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
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 67: goto st136;
		case 99: goto st136;
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
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 79: goto st137;
		case 111: goto st137;
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
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 68: goto st138;
		case 100: goto st138;
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
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 73: goto st139;
		case 105: goto st139;
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
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 78: goto st140;
		case 110: goto st140;
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
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr27;
		case 71: goto st141;
		case 103: goto st141;
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
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
	switch( (*p) ) {
		case 33: goto st19;
		case 58: goto tr181;
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
tr181:
#line 24 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st142;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
#line 3401 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st142;
		case 13: goto tr30;
		case 32: goto st142;
		case 67: goto tr183;
		case 99: goto tr183;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr28;
tr183:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st143;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
#line 3424 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr32;
		case 72: goto st144;
		case 104: goto st144;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
	switch( (*p) ) {
		case 13: goto tr32;
		case 85: goto st145;
		case 117: goto st145;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
	switch( (*p) ) {
		case 13: goto tr32;
		case 78: goto st146;
		case 110: goto st146;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
	switch( (*p) ) {
		case 13: goto tr32;
		case 75: goto st147;
		case 107: goto st147;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
	switch( (*p) ) {
		case 13: goto tr32;
		case 69: goto st148;
		case 101: goto st148;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
	switch( (*p) ) {
		case 13: goto tr32;
		case 68: goto st149;
		case 100: goto st149;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st21;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
	switch( (*p) ) {
		case 9: goto tr190;
		case 13: goto tr191;
		case 32: goto tr190;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st21;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
	if ( (*p) == 32 )
		goto tr192;
	goto st0;
case 151:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr193;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr193;
	} else
		goto tr193;
	goto st0;
tr193:
#line 177 "src/panda/protocol/http/Parser.rl"
	{chunk_length = 0;}
#line 177 "src/panda/protocol/http/Parser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st152;
tr195:
#line 177 "src/panda/protocol/http/Parser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st152;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
#line 3561 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto st153;
		case 59: goto st154;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr195;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr195;
	} else
		goto tr195;
	goto st0;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
	if ( (*p) == 10 )
		goto tr197;
	goto st0;
tr197:
#line 124 "src/panda/protocol/http/Parser.rl"
	{
        {p++; cs = 290; goto _out;}
    }
	goto st290;
st290:
	if ( ++p == pe )
		goto _test_eof290;
case 290:
#line 3592 "src/panda/protocol/http/Parser.cc"
	goto st0;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
	switch( (*p) ) {
		case 33: goto st155;
		case 124: goto st155;
		case 126: goto st155;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st155;
		} else if ( (*p) >= 35 )
			goto st155;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st155;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st155;
		} else
			goto st155;
	} else
		goto st155;
	goto st0;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
	switch( (*p) ) {
		case 13: goto st153;
		case 33: goto st155;
		case 59: goto st154;
		case 61: goto st156;
		case 124: goto st155;
		case 126: goto st155;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st155;
		} else if ( (*p) >= 35 )
			goto st155;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st155;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st155;
		} else
			goto st155;
	} else
		goto st155;
	goto st0;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
	switch( (*p) ) {
		case 34: goto st158;
		case 124: goto st157;
		case 126: goto st157;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st157;
		} else if ( (*p) >= 33 )
			goto st157;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st157;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st157;
		} else
			goto st157;
	} else
		goto st157;
	goto st0;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
	switch( (*p) ) {
		case 13: goto st153;
		case 33: goto st157;
		case 59: goto st154;
		case 124: goto st157;
		case 126: goto st157;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st157;
		} else if ( (*p) >= 35 )
			goto st157;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st157;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st157;
		} else
			goto st157;
	} else
		goto st157;
	goto st0;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
	switch( (*p) ) {
		case 34: goto st159;
		case 92: goto st160;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st158;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
	switch( (*p) ) {
		case 13: goto st153;
		case 59: goto st154;
	}
	goto st0;
st160:
	if ( ++p == pe )
		goto _test_eof160;
case 160:
	if ( (*p) == 127 )
		goto st0;
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st158;
case 161:
	if ( (*p) == 13 )
		goto st162;
	goto st0;
st162:
	if ( ++p == pe )
		goto _test_eof162;
case 162:
	if ( (*p) == 10 )
		goto st163;
	goto st0;
st163:
	if ( ++p == pe )
		goto _test_eof163;
case 163:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr206;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr206;
	} else
		goto tr206;
	goto st0;
tr206:
#line 177 "src/panda/protocol/http/Parser.rl"
	{chunk_length = 0;}
#line 177 "src/panda/protocol/http/Parser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st164;
tr208:
#line 177 "src/panda/protocol/http/Parser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto st164;
st164:
	if ( ++p == pe )
		goto _test_eof164;
case 164:
#line 3781 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto st165;
		case 59: goto st166;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr208;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr208;
	} else
		goto tr208;
	goto st0;
st165:
	if ( ++p == pe )
		goto _test_eof165;
case 165:
	if ( (*p) == 10 )
		goto tr210;
	goto st0;
tr210:
#line 124 "src/panda/protocol/http/Parser.rl"
	{
        {p++; cs = 291; goto _out;}
    }
	goto st291;
st291:
	if ( ++p == pe )
		goto _test_eof291;
case 291:
#line 3812 "src/panda/protocol/http/Parser.cc"
	goto st0;
st166:
	if ( ++p == pe )
		goto _test_eof166;
case 166:
	switch( (*p) ) {
		case 33: goto st167;
		case 124: goto st167;
		case 126: goto st167;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st167;
		} else if ( (*p) >= 35 )
			goto st167;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st167;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st167;
		} else
			goto st167;
	} else
		goto st167;
	goto st0;
st167:
	if ( ++p == pe )
		goto _test_eof167;
case 167:
	switch( (*p) ) {
		case 13: goto st165;
		case 33: goto st167;
		case 59: goto st166;
		case 61: goto st168;
		case 124: goto st167;
		case 126: goto st167;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st167;
		} else if ( (*p) >= 35 )
			goto st167;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st167;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st167;
		} else
			goto st167;
	} else
		goto st167;
	goto st0;
st168:
	if ( ++p == pe )
		goto _test_eof168;
case 168:
	switch( (*p) ) {
		case 34: goto st170;
		case 124: goto st169;
		case 126: goto st169;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st169;
		} else if ( (*p) >= 33 )
			goto st169;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st169;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st169;
		} else
			goto st169;
	} else
		goto st169;
	goto st0;
st169:
	if ( ++p == pe )
		goto _test_eof169;
case 169:
	switch( (*p) ) {
		case 13: goto st165;
		case 33: goto st169;
		case 59: goto st166;
		case 124: goto st169;
		case 126: goto st169;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st169;
		} else if ( (*p) >= 35 )
			goto st169;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st169;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st169;
		} else
			goto st169;
	} else
		goto st169;
	goto st0;
st170:
	if ( ++p == pe )
		goto _test_eof170;
case 170:
	switch( (*p) ) {
		case 34: goto st171;
		case 92: goto st172;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st170;
st171:
	if ( ++p == pe )
		goto _test_eof171;
case 171:
	switch( (*p) ) {
		case 13: goto st165;
		case 59: goto st166;
	}
	goto st0;
st172:
	if ( ++p == pe )
		goto _test_eof172;
case 172:
	if ( (*p) == 127 )
		goto st0;
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st170;
st173:
	if ( ++p == pe )
		goto _test_eof173;
case 173:
	switch( (*p) ) {
		case 13: goto st174;
		case 33: goto tr218;
		case 124: goto tr218;
		case 126: goto tr218;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr218;
		} else if ( (*p) >= 35 )
			goto tr218;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr218;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr218;
		} else
			goto tr218;
	} else
		goto tr218;
	goto st0;
st174:
	if ( ++p == pe )
		goto _test_eof174;
case 174:
	if ( (*p) == 10 )
		goto tr219;
	goto st0;
tr219:
#line 124 "src/panda/protocol/http/Parser.rl"
	{
        {p++; cs = 292; goto _out;}
    }
	goto st292;
st292:
	if ( ++p == pe )
		goto _test_eof292;
case 292:
#line 4008 "src/panda/protocol/http/Parser.cc"
	goto st0;
tr218:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st175;
st175:
	if ( ++p == pe )
		goto _test_eof175;
case 175:
#line 4021 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st175;
		case 58: goto tr221;
		case 124: goto st175;
		case 126: goto st175;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st175;
		} else if ( (*p) >= 35 )
			goto st175;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st175;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st175;
		} else
			goto st175;
	} else
		goto st175;
	goto st0;
tr221:
#line 24 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st176;
st176:
	if ( ++p == pe )
		goto _test_eof176;
case 176:
#line 4065 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st176;
		case 13: goto tr224;
		case 32: goto st176;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr222;
tr222:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st177;
st177:
	if ( ++p == pe )
		goto _test_eof177;
case 177:
#line 4086 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr226;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st177;
tr224:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st178;
tr226:
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st178;
st178:
	if ( ++p == pe )
		goto _test_eof178;
case 178:
#line 4136 "src/panda/protocol/http/Parser.cc"
	if ( (*p) == 10 )
		goto st173;
	goto st0;
case 179:
	switch( (*p) ) {
		case 67: goto st180;
		case 68: goto st258;
		case 71: goto st264;
		case 72: goto st267;
		case 79: goto st271;
		case 80: goto st278;
		case 84: goto st284;
	}
	goto st0;
st180:
	if ( ++p == pe )
		goto _test_eof180;
case 180:
	if ( (*p) == 79 )
		goto st181;
	goto st0;
st181:
	if ( ++p == pe )
		goto _test_eof181;
case 181:
	if ( (*p) == 78 )
		goto st182;
	goto st0;
st182:
	if ( ++p == pe )
		goto _test_eof182;
case 182:
	if ( (*p) == 78 )
		goto st183;
	goto st0;
st183:
	if ( ++p == pe )
		goto _test_eof183;
case 183:
	if ( (*p) == 69 )
		goto st184;
	goto st0;
st184:
	if ( ++p == pe )
		goto _test_eof184;
case 184:
	if ( (*p) == 67 )
		goto st185;
	goto st0;
st185:
	if ( ++p == pe )
		goto _test_eof185;
case 185:
	if ( (*p) == 84 )
		goto st186;
	goto st0;
st186:
	if ( ++p == pe )
		goto _test_eof186;
case 186:
	if ( (*p) == 32 )
		goto tr241;
	goto st0;
tr241:
#line 194 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::CONNECT; }
	goto st187;
tr340:
#line 192 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::DELETE; }
	goto st187;
tr343:
#line 188 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::GET; }
	goto st187;
tr347:
#line 189 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::HEAD; }
	goto st187;
tr354:
#line 187 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::OPTIONS; }
	goto st187;
tr359:
#line 190 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::POST; }
	goto st187;
tr361:
#line 191 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::PUT; }
	goto st187;
tr366:
#line 193 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::TRACE; }
	goto st187;
st187:
	if ( ++p == pe )
		goto _test_eof187;
case 187:
#line 4236 "src/panda/protocol/http/Parser.cc"
	if ( 33 <= (*p) && (*p) <= 126 )
		goto tr242;
	goto st0;
tr242:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st188;
st188:
	if ( ++p == pe )
		goto _test_eof188;
case 188:
#line 4251 "src/panda/protocol/http/Parser.cc"
	if ( (*p) == 32 )
		goto tr243;
	if ( 33 <= (*p) && (*p) <= 126 )
		goto st188;
	goto st0;
tr243:
#line 118 "src/panda/protocol/http/Parser.rl"
	{
        string target;
        SAVE(target);
        request->uri = new URI(target);
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st189;
st189:
	if ( ++p == pe )
		goto _test_eof189;
case 189:
#line 4273 "src/panda/protocol/http/Parser.cc"
	if ( (*p) == 72 )
		goto st190;
	goto st0;
st190:
	if ( ++p == pe )
		goto _test_eof190;
case 190:
	if ( (*p) == 84 )
		goto st191;
	goto st0;
st191:
	if ( ++p == pe )
		goto _test_eof191;
case 191:
	if ( (*p) == 84 )
		goto st192;
	goto st0;
st192:
	if ( ++p == pe )
		goto _test_eof192;
case 192:
	if ( (*p) == 80 )
		goto st193;
	goto st0;
st193:
	if ( ++p == pe )
		goto _test_eof193;
case 193:
	if ( (*p) == 47 )
		goto st194;
	goto st0;
st194:
	if ( ++p == pe )
		goto _test_eof194;
case 194:
	if ( (*p) == 49 )
		goto st195;
	goto st0;
st195:
	if ( ++p == pe )
		goto _test_eof195;
case 195:
	if ( (*p) == 46 )
		goto st196;
	goto st0;
st196:
	if ( ++p == pe )
		goto _test_eof196;
case 196:
	switch( (*p) ) {
		case 48: goto st197;
		case 49: goto st257;
	}
	goto st0;
st197:
	if ( ++p == pe )
		goto _test_eof197;
case 197:
	if ( (*p) == 13 )
		goto tr254;
	goto st0;
tr254:
#line 148 "src/panda/protocol/http/Parser.rl"
	{message->http_version = 10;}
	goto st198;
tr265:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st198;
tr267:
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st198;
tr333:
#line 173 "src/panda/protocol/http/Parser.rl"
	{message->chunked = true;}
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st198;
tr334:
#line 148 "src/panda/protocol/http/Parser.rl"
	{message->http_version = 11;}
	goto st198;
tr296:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
#line 57 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st198;
tr301:
#line 57 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
#line 33 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string& value = message->headers.fields.back().value;
            SAVE(value);
            if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st198;
st198:
	if ( ++p == pe )
		goto _test_eof198;
case 198:
#line 4452 "src/panda/protocol/http/Parser.cc"
	if ( (*p) == 10 )
		goto st199;
	goto st0;
st199:
	if ( ++p == pe )
		goto _test_eof199;
case 199:
	switch( (*p) ) {
		case 13: goto st200;
		case 33: goto tr257;
		case 67: goto tr258;
		case 84: goto tr259;
		case 99: goto tr258;
		case 116: goto tr259;
		case 124: goto tr257;
		case 126: goto tr257;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr257;
		} else if ( (*p) >= 35 )
			goto tr257;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr257;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr257;
		} else
			goto tr257;
	} else
		goto tr257;
	goto st0;
st200:
	if ( ++p == pe )
		goto _test_eof200;
case 200:
	if ( (*p) == 10 )
		goto tr260;
	goto st0;
tr260:
#line 124 "src/panda/protocol/http/Parser.rl"
	{
        {p++; cs = 293; goto _out;}
    }
	goto st293;
st293:
	if ( ++p == pe )
		goto _test_eof293;
case 293:
#line 4505 "src/panda/protocol/http/Parser.cc"
	goto st0;
tr257:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st201;
st201:
	if ( ++p == pe )
		goto _test_eof201;
case 201:
#line 4518 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
tr262:
#line 24 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st202;
st202:
	if ( ++p == pe )
		goto _test_eof202;
case 202:
#line 4562 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st202;
		case 13: goto tr265;
		case 32: goto st202;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr263;
tr263:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st203;
tr332:
#line 173 "src/panda/protocol/http/Parser.rl"
	{message->chunked = true;}
	goto st203;
tr295:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
#line 57 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
	goto st203;
tr300:
#line 57 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
	goto st203;
st203:
	if ( ++p == pe )
		goto _test_eof203;
case 203:
#line 4614 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr267;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st203;
tr258:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st204;
st204:
	if ( ++p == pe )
		goto _test_eof204;
case 204:
#line 4636 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 79: goto st205;
		case 111: goto st205;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st205:
	if ( ++p == pe )
		goto _test_eof205;
case 205:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 78: goto st206;
		case 79: goto st220;
		case 110: goto st206;
		case 111: goto st220;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st206:
	if ( ++p == pe )
		goto _test_eof206;
case 206:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 84: goto st207;
		case 116: goto st207;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st207:
	if ( ++p == pe )
		goto _test_eof207;
case 207:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 69: goto st208;
		case 101: goto st208;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st208:
	if ( ++p == pe )
		goto _test_eof208;
case 208:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 78: goto st209;
		case 110: goto st209;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st209:
	if ( ++p == pe )
		goto _test_eof209;
case 209:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 84: goto st210;
		case 116: goto st210;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st210:
	if ( ++p == pe )
		goto _test_eof210;
case 210:
	switch( (*p) ) {
		case 33: goto st201;
		case 45: goto st211;
		case 46: goto st201;
		case 58: goto tr262;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else if ( (*p) >= 65 )
			goto st201;
	} else
		goto st201;
	goto st0;
st211:
	if ( ++p == pe )
		goto _test_eof211;
case 211:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 76: goto st212;
		case 108: goto st212;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st212:
	if ( ++p == pe )
		goto _test_eof212;
case 212:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 69: goto st213;
		case 101: goto st213;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st213:
	if ( ++p == pe )
		goto _test_eof213;
case 213:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 78: goto st214;
		case 110: goto st214;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st214:
	if ( ++p == pe )
		goto _test_eof214;
case 214:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 71: goto st215;
		case 103: goto st215;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st215:
	if ( ++p == pe )
		goto _test_eof215;
case 215:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 84: goto st216;
		case 116: goto st216;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st216:
	if ( ++p == pe )
		goto _test_eof216;
case 216:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 72: goto st217;
		case 104: goto st217;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st217:
	if ( ++p == pe )
		goto _test_eof217;
case 217:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr282;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
tr282:
#line 24 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st218;
st218:
	if ( ++p == pe )
		goto _test_eof218;
case 218:
#line 5069 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st218;
		case 13: goto tr265;
		case 32: goto st218;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr284;
	} else if ( (*p) >= 0 )
		goto st0;
	goto tr263;
tr284:
#line 42 "src/panda/protocol/http/Parser.rl"
	{
        if (has_content_length) {
            cs = http_parser_error;
            set_error(errc::multiple_content_length);
            {p++; cs = 219; goto _out;}
        }
        has_content_length = true;
    }
#line 172 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(content_length)}
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st219;
tr285:
#line 172 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(content_length)}
	goto st219;
st219:
	if ( ++p == pe )
		goto _test_eof219;
case 219:
#line 5108 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr267;
		case 127: goto st0;
	}
	if ( (*p) < 10 ) {
		if ( 0 <= (*p) && (*p) <= 8 )
			goto st0;
	} else if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr285;
	} else
		goto st0;
	goto st203;
st220:
	if ( ++p == pe )
		goto _test_eof220;
case 220:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 75: goto st221;
		case 107: goto st221;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st221:
	if ( ++p == pe )
		goto _test_eof221;
case 221:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 73: goto st222;
		case 105: goto st222;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st222:
	if ( ++p == pe )
		goto _test_eof222;
case 222:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 69: goto st223;
		case 101: goto st223;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st223:
	if ( ++p == pe )
		goto _test_eof223;
case 223:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr289;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
tr289:
#line 24 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st224;
st224:
	if ( ++p == pe )
		goto _test_eof224;
case 224:
#line 5259 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st224;
		case 13: goto tr265;
		case 32: goto st224;
		case 33: goto tr291;
		case 124: goto tr291;
		case 126: goto tr291;
		case 127: goto st0;
	}
	if ( (*p) < 45 ) {
		if ( (*p) < 35 ) {
			if ( 0 <= (*p) && (*p) <= 31 )
				goto st0;
		} else if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr291;
		} else
			goto tr291;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr291;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr291;
		} else
			goto tr291;
	} else
		goto tr291;
	goto tr263;
tr291:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st225;
tr304:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
	goto st225;
st225:
	if ( ++p == pe )
		goto _test_eof225;
case 225:
#line 5313 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr267;
		case 33: goto st225;
		case 61: goto tr293;
		case 124: goto st225;
		case 126: goto st225;
		case 127: goto st0;
	}
	if ( (*p) < 42 ) {
		if ( (*p) < 10 ) {
			if ( 0 <= (*p) && (*p) <= 8 )
				goto st0;
		} else if ( (*p) > 31 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto st225;
		} else
			goto st0;
	} else if ( (*p) > 43 ) {
		if ( (*p) < 48 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto st225;
		} else if ( (*p) > 57 ) {
			if ( (*p) > 90 ) {
				if ( 94 <= (*p) && (*p) <= 122 )
					goto st225;
			} else if ( (*p) >= 65 )
				goto st225;
		} else
			goto st225;
	} else
		goto st225;
	goto st203;
tr293:
#line 51 "src/panda/protocol/http/Parser.rl"
	{
        string v;
        SUBSAVE(v);
        request->cookies.add(v, {});
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
	goto st226;
st226:
	if ( ++p == pe )
		goto _test_eof226;
case 226:
#line 5362 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto tr295;
		case 13: goto tr296;
		case 32: goto tr295;
		case 34: goto tr297;
		case 44: goto st203;
		case 59: goto tr298;
		case 92: goto st203;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr294;
tr294:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
	goto st227;
st227:
	if ( ++p == pe )
		goto _test_eof227;
case 227:
#line 5387 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto tr300;
		case 13: goto tr301;
		case 32: goto tr300;
		case 34: goto st203;
		case 44: goto st203;
		case 59: goto tr302;
		case 92: goto st203;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st227;
tr298:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
#line 57 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
	goto st228;
tr302:
#line 57 "src/panda/protocol/http/Parser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SUBSAVE(v);
    }
#line 20 "src/panda/protocol/http/Parser.rl"
	{
        submarked = false;
    }
	goto st228;
st228:
	if ( ++p == pe )
		goto _test_eof228;
case 228:
#line 5432 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr267;
		case 32: goto st229;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st203;
st229:
	if ( ++p == pe )
		goto _test_eof229;
case 229:
	switch( (*p) ) {
		case 13: goto tr267;
		case 33: goto tr304;
		case 124: goto tr304;
		case 126: goto tr304;
		case 127: goto st0;
	}
	if ( (*p) < 42 ) {
		if ( (*p) < 10 ) {
			if ( 0 <= (*p) && (*p) <= 8 )
				goto st0;
		} else if ( (*p) > 31 ) {
			if ( 35 <= (*p) && (*p) <= 39 )
				goto tr304;
		} else
			goto st0;
	} else if ( (*p) > 43 ) {
		if ( (*p) < 48 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto tr304;
		} else if ( (*p) > 57 ) {
			if ( (*p) > 90 ) {
				if ( 94 <= (*p) && (*p) <= 122 )
					goto tr304;
			} else if ( (*p) >= 65 )
				goto tr304;
		} else
			goto tr304;
	} else
		goto tr304;
	goto st203;
tr297:
#line 15 "src/panda/protocol/http/Parser.rl"
	{
        submark   = p - ps;
        submarked = true;
    }
	goto st230;
st230:
	if ( ++p == pe )
		goto _test_eof230;
case 230:
#line 5490 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st203;
		case 13: goto tr267;
		case 32: goto st203;
		case 34: goto st231;
		case 44: goto st203;
		case 59: goto st203;
		case 92: goto st203;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st230;
st231:
	if ( ++p == pe )
		goto _test_eof231;
case 231:
	switch( (*p) ) {
		case 9: goto tr300;
		case 13: goto tr301;
		case 32: goto tr300;
		case 59: goto tr302;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st203;
tr259:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st232;
st232:
	if ( ++p == pe )
		goto _test_eof232;
case 232:
#line 5529 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 82: goto st233;
		case 114: goto st233;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st233:
	if ( ++p == pe )
		goto _test_eof233;
case 233:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 65: goto st234;
		case 97: goto st234;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 66 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st234:
	if ( ++p == pe )
		goto _test_eof234;
case 234:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 78: goto st235;
		case 110: goto st235;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st235:
	if ( ++p == pe )
		goto _test_eof235;
case 235:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 83: goto st236;
		case 115: goto st236;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st236:
	if ( ++p == pe )
		goto _test_eof236;
case 236:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 70: goto st237;
		case 102: goto st237;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st237:
	if ( ++p == pe )
		goto _test_eof237;
case 237:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 69: goto st238;
		case 101: goto st238;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st238:
	if ( ++p == pe )
		goto _test_eof238;
case 238:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 82: goto st239;
		case 114: goto st239;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st239:
	if ( ++p == pe )
		goto _test_eof239;
case 239:
	switch( (*p) ) {
		case 33: goto st201;
		case 45: goto st240;
		case 46: goto st201;
		case 58: goto tr262;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else if ( (*p) >= 65 )
			goto st201;
	} else
		goto st201;
	goto st0;
st240:
	if ( ++p == pe )
		goto _test_eof240;
case 240:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 69: goto st241;
		case 101: goto st241;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st241:
	if ( ++p == pe )
		goto _test_eof241;
case 241:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 78: goto st242;
		case 110: goto st242;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st242:
	if ( ++p == pe )
		goto _test_eof242;
case 242:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 67: goto st243;
		case 99: goto st243;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st243:
	if ( ++p == pe )
		goto _test_eof243;
case 243:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 79: goto st244;
		case 111: goto st244;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st244:
	if ( ++p == pe )
		goto _test_eof244;
case 244:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 68: goto st245;
		case 100: goto st245;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st245:
	if ( ++p == pe )
		goto _test_eof245;
case 245:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 73: goto st246;
		case 105: goto st246;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st246:
	if ( ++p == pe )
		goto _test_eof246;
case 246:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 78: goto st247;
		case 110: goto st247;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st247:
	if ( ++p == pe )
		goto _test_eof247;
case 247:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr262;
		case 71: goto st248;
		case 103: goto st248;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
st248:
	if ( ++p == pe )
		goto _test_eof248;
case 248:
	switch( (*p) ) {
		case 33: goto st201;
		case 58: goto tr323;
		case 124: goto st201;
		case 126: goto st201;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st201;
		} else if ( (*p) >= 35 )
			goto st201;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st201;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st201;
		} else
			goto st201;
	} else
		goto st201;
	goto st0;
tr323:
#line 24 "src/panda/protocol/http/Parser.rl"
	{
        if (!headers_finished) {
            string value;
            SAVE(value);
            message->headers.add(value, {});
        }
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 11 "src/panda/protocol/http/Parser.rl"
	{
        marked = false;
    }
	goto st249;
st249:
	if ( ++p == pe )
		goto _test_eof249;
case 249:
#line 6050 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 9: goto st249;
		case 13: goto tr265;
		case 32: goto st249;
		case 67: goto tr325;
		case 99: goto tr325;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr263;
tr325:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark   = p - ps;
        marked = true;
    }
	goto st250;
st250:
	if ( ++p == pe )
		goto _test_eof250;
case 250:
#line 6073 "src/panda/protocol/http/Parser.cc"
	switch( (*p) ) {
		case 13: goto tr267;
		case 72: goto st251;
		case 104: goto st251;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st203;
st251:
	if ( ++p == pe )
		goto _test_eof251;
case 251:
	switch( (*p) ) {
		case 13: goto tr267;
		case 85: goto st252;
		case 117: goto st252;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st203;
st252:
	if ( ++p == pe )
		goto _test_eof252;
case 252:
	switch( (*p) ) {
		case 13: goto tr267;
		case 78: goto st253;
		case 110: goto st253;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st203;
st253:
	if ( ++p == pe )
		goto _test_eof253;
case 253:
	switch( (*p) ) {
		case 13: goto tr267;
		case 75: goto st254;
		case 107: goto st254;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st203;
st254:
	if ( ++p == pe )
		goto _test_eof254;
case 254:
	switch( (*p) ) {
		case 13: goto tr267;
		case 69: goto st255;
		case 101: goto st255;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st203;
st255:
	if ( ++p == pe )
		goto _test_eof255;
case 255:
	switch( (*p) ) {
		case 13: goto tr267;
		case 68: goto st256;
		case 100: goto st256;
		case 127: goto st0;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st203;
st256:
	if ( ++p == pe )
		goto _test_eof256;
case 256:
	switch( (*p) ) {
		case 9: goto tr332;
		case 13: goto tr333;
		case 32: goto tr332;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st203;
st257:
	if ( ++p == pe )
		goto _test_eof257;
case 257:
	if ( (*p) == 13 )
		goto tr334;
	goto st0;
st258:
	if ( ++p == pe )
		goto _test_eof258;
case 258:
	if ( (*p) == 69 )
		goto st259;
	goto st0;
st259:
	if ( ++p == pe )
		goto _test_eof259;
case 259:
	if ( (*p) == 76 )
		goto st260;
	goto st0;
st260:
	if ( ++p == pe )
		goto _test_eof260;
case 260:
	if ( (*p) == 69 )
		goto st261;
	goto st0;
st261:
	if ( ++p == pe )
		goto _test_eof261;
case 261:
	if ( (*p) == 84 )
		goto st262;
	goto st0;
st262:
	if ( ++p == pe )
		goto _test_eof262;
case 262:
	if ( (*p) == 69 )
		goto st263;
	goto st0;
st263:
	if ( ++p == pe )
		goto _test_eof263;
case 263:
	if ( (*p) == 32 )
		goto tr340;
	goto st0;
st264:
	if ( ++p == pe )
		goto _test_eof264;
case 264:
	if ( (*p) == 69 )
		goto st265;
	goto st0;
st265:
	if ( ++p == pe )
		goto _test_eof265;
case 265:
	if ( (*p) == 84 )
		goto st266;
	goto st0;
st266:
	if ( ++p == pe )
		goto _test_eof266;
case 266:
	if ( (*p) == 32 )
		goto tr343;
	goto st0;
st267:
	if ( ++p == pe )
		goto _test_eof267;
case 267:
	if ( (*p) == 69 )
		goto st268;
	goto st0;
st268:
	if ( ++p == pe )
		goto _test_eof268;
case 268:
	if ( (*p) == 65 )
		goto st269;
	goto st0;
st269:
	if ( ++p == pe )
		goto _test_eof269;
case 269:
	if ( (*p) == 68 )
		goto st270;
	goto st0;
st270:
	if ( ++p == pe )
		goto _test_eof270;
case 270:
	if ( (*p) == 32 )
		goto tr347;
	goto st0;
st271:
	if ( ++p == pe )
		goto _test_eof271;
case 271:
	if ( (*p) == 80 )
		goto st272;
	goto st0;
st272:
	if ( ++p == pe )
		goto _test_eof272;
case 272:
	if ( (*p) == 84 )
		goto st273;
	goto st0;
st273:
	if ( ++p == pe )
		goto _test_eof273;
case 273:
	if ( (*p) == 73 )
		goto st274;
	goto st0;
st274:
	if ( ++p == pe )
		goto _test_eof274;
case 274:
	if ( (*p) == 79 )
		goto st275;
	goto st0;
st275:
	if ( ++p == pe )
		goto _test_eof275;
case 275:
	if ( (*p) == 78 )
		goto st276;
	goto st0;
st276:
	if ( ++p == pe )
		goto _test_eof276;
case 276:
	if ( (*p) == 83 )
		goto st277;
	goto st0;
st277:
	if ( ++p == pe )
		goto _test_eof277;
case 277:
	if ( (*p) == 32 )
		goto tr354;
	goto st0;
st278:
	if ( ++p == pe )
		goto _test_eof278;
case 278:
	switch( (*p) ) {
		case 79: goto st279;
		case 85: goto st282;
	}
	goto st0;
st279:
	if ( ++p == pe )
		goto _test_eof279;
case 279:
	if ( (*p) == 83 )
		goto st280;
	goto st0;
st280:
	if ( ++p == pe )
		goto _test_eof280;
case 280:
	if ( (*p) == 84 )
		goto st281;
	goto st0;
st281:
	if ( ++p == pe )
		goto _test_eof281;
case 281:
	if ( (*p) == 32 )
		goto tr359;
	goto st0;
st282:
	if ( ++p == pe )
		goto _test_eof282;
case 282:
	if ( (*p) == 84 )
		goto st283;
	goto st0;
st283:
	if ( ++p == pe )
		goto _test_eof283;
case 283:
	if ( (*p) == 32 )
		goto tr361;
	goto st0;
st284:
	if ( ++p == pe )
		goto _test_eof284;
case 284:
	if ( (*p) == 82 )
		goto st285;
	goto st0;
st285:
	if ( ++p == pe )
		goto _test_eof285;
case 285:
	if ( (*p) == 65 )
		goto st286;
	goto st0;
st286:
	if ( ++p == pe )
		goto _test_eof286;
case 286:
	if ( (*p) == 67 )
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
	if ( (*p) == 32 )
		goto tr366;
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
	_test_eof289: cs = 289; goto _test_eof; 
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
	_test_eof112: cs = 112; goto _test_eof; 
	_test_eof113: cs = 113; goto _test_eof; 
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
	_test_eof152: cs = 152; goto _test_eof; 
	_test_eof153: cs = 153; goto _test_eof; 
	_test_eof290: cs = 290; goto _test_eof; 
	_test_eof154: cs = 154; goto _test_eof; 
	_test_eof155: cs = 155; goto _test_eof; 
	_test_eof156: cs = 156; goto _test_eof; 
	_test_eof157: cs = 157; goto _test_eof; 
	_test_eof158: cs = 158; goto _test_eof; 
	_test_eof159: cs = 159; goto _test_eof; 
	_test_eof160: cs = 160; goto _test_eof; 
	_test_eof162: cs = 162; goto _test_eof; 
	_test_eof163: cs = 163; goto _test_eof; 
	_test_eof164: cs = 164; goto _test_eof; 
	_test_eof165: cs = 165; goto _test_eof; 
	_test_eof291: cs = 291; goto _test_eof; 
	_test_eof166: cs = 166; goto _test_eof; 
	_test_eof167: cs = 167; goto _test_eof; 
	_test_eof168: cs = 168; goto _test_eof; 
	_test_eof169: cs = 169; goto _test_eof; 
	_test_eof170: cs = 170; goto _test_eof; 
	_test_eof171: cs = 171; goto _test_eof; 
	_test_eof172: cs = 172; goto _test_eof; 
	_test_eof173: cs = 173; goto _test_eof; 
	_test_eof174: cs = 174; goto _test_eof; 
	_test_eof292: cs = 292; goto _test_eof; 
	_test_eof175: cs = 175; goto _test_eof; 
	_test_eof176: cs = 176; goto _test_eof; 
	_test_eof177: cs = 177; goto _test_eof; 
	_test_eof178: cs = 178; goto _test_eof; 
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
	_test_eof293: cs = 293; goto _test_eof; 
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

	_test_eof: {}
	_out: {}
	}

#line 243 "src/panda/protocol/http/Parser.rl"
    return p - ps;
}

#endif

}}}
