
#line 1 "src/panda/protocol/http/CookieParser.rl"
#include "Request.h"
#include "Response.h"


#line 122 "src/panda/protocol/http/CookieParser.rl"


namespace panda { namespace protocol { namespace http {


#line 14 "src/panda/protocol/http/CookieParser.cc"
static const int http_cookie_parser_start = 1;
static const int http_cookie_parser_first_final = 10;
static const int http_cookie_parser_error = 0;

static const int http_cookie_parser_en_cookie_header = 6;
static const int http_cookie_parser_en_set_cookie_header = 1;


#line 127 "src/panda/protocol/http/CookieParser.rl"

#ifndef PARSER_CONSTANTS

#define ADD_DIGIT(dest) \
    dest *= 10;         \
    dest += *p - '0';
    
#define SAVE(dest) dest = buffer.substr(mark, p - ps - mark);

void Request::parse_cookie (const string& buffer) {
    const char* ps = buffer.data();
    const char* p  = ps;
    const char* pe = ps + buffer.size();
    const char* eof = pe;
    Request* request = this;
    Response* response;
    size_t mark;
    int cs = http_cookie_parser_en_cookie_header;
    
#line 43 "src/panda/protocol/http/CookieParser.cc"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 33: goto tr0;
		case 124: goto tr0;
		case 126: goto tr0;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr0;
		} else if ( (*p) >= 35 )
			goto tr0;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr0;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr0;
		} else
			goto tr0;
	} else
		goto tr0;
	goto st0;
st0:
cs = 0;
	goto _out;
tr0:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 87 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 33: goto st2;
		case 61: goto tr3;
		case 124: goto st2;
		case 126: goto st2;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st2;
		} else if ( (*p) >= 35 )
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st2;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st2;
		} else
			goto st2;
	} else
		goto st2;
	goto st0;
tr3:
#line 27 "src/panda/protocol/http/CookieParser.rl"
	{
        string v;
        SAVE(v);
        response->cookies.add(v, {});
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 128 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 34: goto tr21;
		case 44: goto st0;
		case 59: goto tr22;
		case 92: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 32 )
		goto st0;
	goto tr20;
tr20:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 150 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 34: goto st0;
		case 44: goto st0;
		case 59: goto tr24;
		case 92: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 32 )
		goto st0;
	goto st11;
tr22:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 33 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st3;
tr24:
#line 33 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st3;
tr34:
#line 38 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._domain;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st3;
tr43:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 58 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._expires;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st3;
tr45:
#line 58 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._expires;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st3;
tr53:
#line 67 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._http_only = true;
    }
	goto st3;
tr69:
#line 43 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._path;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st3;
tr78:
#line 71 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Strict;
    }
	goto st3;
tr85:
#line 75 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Lax;
    }
	goto st3;
tr89:
#line 79 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::None;
    }
	goto st3;
tr99:
#line 63 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._secure = true;
    }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 271 "src/panda/protocol/http/CookieParser.cc"
	if ( (*p) == 32 )
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	switch( (*p) ) {
		case 59: goto st0;
		case 68: goto st13;
		case 69: goto st21;
		case 72: goto st30;
		case 77: goto st38;
		case 80: goto st47;
		case 83: goto st53;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	switch( (*p) ) {
		case 59: goto st3;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	switch( (*p) ) {
		case 59: goto st3;
		case 111: goto st14;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	switch( (*p) ) {
		case 59: goto st3;
		case 109: goto st15;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	switch( (*p) ) {
		case 59: goto st3;
		case 97: goto st16;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 59: goto st3;
		case 105: goto st17;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	switch( (*p) ) {
		case 59: goto st3;
		case 110: goto st18;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	switch( (*p) ) {
		case 59: goto st3;
		case 61: goto st19;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	switch( (*p) ) {
		case 59: goto st3;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 31 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto tr32;
		} else if ( (*p) >= 0 )
			goto st0;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr32;
		} else if ( (*p) >= 65 )
			goto tr32;
	} else
		goto tr32;
	goto st12;
tr32:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 409 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 59: goto tr34;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 31 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto st20;
		} else if ( (*p) >= 0 )
			goto st0;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto st12;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	switch( (*p) ) {
		case 59: goto st3;
		case 120: goto st22;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	switch( (*p) ) {
		case 59: goto st3;
		case 112: goto st23;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 59: goto st3;
		case 105: goto st24;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	switch( (*p) ) {
		case 59: goto st3;
		case 114: goto st25;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	switch( (*p) ) {
		case 59: goto st3;
		case 101: goto st26;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 59: goto st3;
		case 115: goto st27;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 59: goto st3;
		case 61: goto st28;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 32: goto tr42;
		case 44: goto tr42;
		case 59: goto tr43;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( 0 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr42;
		} else if ( (*p) >= 65 )
			goto tr42;
	} else
		goto tr42;
	goto st12;
tr42:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
#line 546 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 32: goto st29;
		case 44: goto st29;
		case 59: goto tr45;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( 0 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st29;
		} else if ( (*p) >= 65 )
			goto st29;
	} else
		goto st29;
	goto st12;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 59: goto st3;
		case 116: goto st31;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 59: goto st3;
		case 116: goto st32;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 59: goto st3;
		case 112: goto st33;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 59: goto st3;
		case 79: goto st34;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	switch( (*p) ) {
		case 59: goto st3;
		case 110: goto st35;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 59: goto st3;
		case 108: goto st36;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	switch( (*p) ) {
		case 59: goto st3;
		case 121: goto st37;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 59: goto tr53;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 59: goto st3;
		case 97: goto st39;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 59: goto st3;
		case 120: goto st40;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 45: goto st41;
		case 59: goto st3;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 59: goto st3;
		case 65: goto st42;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 59: goto st3;
		case 103: goto st43;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 59: goto st3;
		case 101: goto st44;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 59: goto st3;
		case 61: goto st45;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	switch( (*p) ) {
		case 59: goto st3;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto tr61;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st12;
tr61:
#line 48 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._max_age;
        v = 0;
    }
#line 53 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._max_age;
        ADD_DIGIT(v);
    }
	goto st46;
tr62:
#line 53 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._max_age;
        ADD_DIGIT(v);
    }
	goto st46;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
#line 781 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 59: goto st3;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr62;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st12;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	switch( (*p) ) {
		case 59: goto st3;
		case 97: goto st48;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	switch( (*p) ) {
		case 59: goto st3;
		case 116: goto st49;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 59: goto st3;
		case 104: goto st50;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	switch( (*p) ) {
		case 59: goto st3;
		case 61: goto st51;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 59: goto st3;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr67;
tr67:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st52;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
#line 862 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 59: goto tr69;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st52;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 59: goto st3;
		case 97: goto st54;
		case 101: goto st75;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 59: goto st3;
		case 109: goto st55;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 59: goto st3;
		case 101: goto st56;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 59: goto st3;
		case 83: goto st57;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 59: goto st3;
		case 105: goto st58;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 59: goto st3;
		case 116: goto st59;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 59: goto st3;
		case 101: goto st60;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 59: goto tr78;
		case 61: goto st61;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 59: goto st3;
		case 76: goto st62;
		case 78: goto st65;
		case 83: goto st69;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	switch( (*p) ) {
		case 59: goto st3;
		case 97: goto st63;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	switch( (*p) ) {
		case 59: goto st3;
		case 120: goto st64;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 59: goto tr85;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 59: goto st3;
		case 111: goto st66;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	switch( (*p) ) {
		case 59: goto st3;
		case 110: goto st67;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 59: goto st3;
		case 101: goto st68;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 59: goto tr89;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 59: goto st3;
		case 116: goto st70;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	switch( (*p) ) {
		case 59: goto st3;
		case 114: goto st71;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 59: goto st3;
		case 105: goto st72;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 59: goto st3;
		case 99: goto st73;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	switch( (*p) ) {
		case 59: goto st3;
		case 116: goto st74;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	switch( (*p) ) {
		case 59: goto tr78;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	switch( (*p) ) {
		case 59: goto st3;
		case 99: goto st76;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	switch( (*p) ) {
		case 59: goto st3;
		case 117: goto st77;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	switch( (*p) ) {
		case 59: goto st3;
		case 114: goto st78;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	switch( (*p) ) {
		case 59: goto st3;
		case 101: goto st79;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 59: goto tr99;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
tr21:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 1204 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 34: goto st80;
		case 44: goto st0;
		case 59: goto st0;
		case 92: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 32 )
		goto st0;
	goto st5;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	if ( (*p) == 59 )
		goto tr24;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	switch( (*p) ) {
		case 33: goto tr14;
		case 124: goto tr14;
		case 126: goto tr14;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr14;
		} else if ( (*p) >= 35 )
			goto tr14;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr14;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr14;
		} else
			goto tr14;
	} else
		goto tr14;
	goto st0;
tr14:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 1260 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 33: goto st7;
		case 61: goto tr16;
		case 124: goto st7;
		case 126: goto st7;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st7;
		} else if ( (*p) >= 35 )
			goto st7;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st7;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st7;
		} else
			goto st7;
	} else
		goto st7;
	goto st0;
tr16:
#line 16 "src/panda/protocol/http/CookieParser.rl"
	{
        string v;
        SAVE(v);
        request->cookies.add(v, {});
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st81;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
#line 1301 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 9: goto tr101;
		case 32: goto tr101;
		case 34: goto tr102;
		case 44: goto st0;
		case 59: goto tr103;
		case 92: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr100;
tr100:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st82;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
#line 1325 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 9: goto tr105;
		case 32: goto tr105;
		case 34: goto st0;
		case 44: goto st0;
		case 59: goto tr106;
		case 92: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st82;
tr101:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 22 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st83;
tr105:
#line 22 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st83;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
#line 1369 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 9: goto st83;
		case 32: goto st83;
	}
	goto st0;
tr103:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 22 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st8;
tr106:
#line 22 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 1406 "src/panda/protocol/http/CookieParser.cc"
	if ( (*p) == 32 )
		goto st6;
	goto st0;
tr102:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 1421 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 34: goto st84;
		case 44: goto st0;
		case 59: goto st0;
		case 92: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 32 )
		goto st0;
	goto st9;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 9: goto tr105;
		case 32: goto tr105;
		case 59: goto tr106;
	}
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
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
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 79: 
#line 63 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._secure = true;
    }
	break;
	case 37: 
#line 67 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._http_only = true;
    }
	break;
	case 60: 
	case 74: 
#line 71 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Strict;
    }
	break;
	case 64: 
#line 75 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Lax;
    }
	break;
	case 68: 
#line 79 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::None;
    }
	break;
	case 82: 
	case 84: 
#line 22 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 11: 
	case 80: 
#line 33 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 20: 
#line 38 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._domain;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 52: 
#line 43 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._path;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 29: 
#line 58 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._expires;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 81: 
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 22 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 10: 
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 33 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 28: 
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 58 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._expires;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
#line 1667 "src/panda/protocol/http/CookieParser.cc"
	}
	}

	_out: {}
	}

#line 146 "src/panda/protocol/http/CookieParser.rl"
}

void Response::parse_set_cookie (const string& buffer) {
    const char* ps = buffer.data();
    const char* p  = ps;
    const char* pe = ps + buffer.size();
    const char* eof = pe;
    Response* response = this;
    Request* request;
    size_t mark;
    int cs = http_cookie_parser_en_set_cookie_header;
    
#line 1687 "src/panda/protocol/http/CookieParser.cc"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 33: goto tr0;
		case 124: goto tr0;
		case 126: goto tr0;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr0;
		} else if ( (*p) >= 35 )
			goto tr0;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr0;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr0;
		} else
			goto tr0;
	} else
		goto tr0;
	goto st0;
st0:
cs = 0;
	goto _out;
tr0:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 1731 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 33: goto st2;
		case 61: goto tr3;
		case 124: goto st2;
		case 126: goto st2;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st2;
		} else if ( (*p) >= 35 )
			goto st2;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st2;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st2;
		} else
			goto st2;
	} else
		goto st2;
	goto st0;
tr3:
#line 27 "src/panda/protocol/http/CookieParser.rl"
	{
        string v;
        SAVE(v);
        response->cookies.add(v, {});
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 1772 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 34: goto tr21;
		case 44: goto st0;
		case 59: goto tr22;
		case 92: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 32 )
		goto st0;
	goto tr20;
tr20:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 1794 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 34: goto st0;
		case 44: goto st0;
		case 59: goto tr24;
		case 92: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 32 )
		goto st0;
	goto st11;
tr22:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 33 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st3;
tr24:
#line 33 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st3;
tr34:
#line 38 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._domain;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st3;
tr43:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 58 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._expires;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st3;
tr45:
#line 58 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._expires;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st3;
tr53:
#line 67 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._http_only = true;
    }
	goto st3;
tr69:
#line 43 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._path;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st3;
tr78:
#line 71 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Strict;
    }
	goto st3;
tr85:
#line 75 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Lax;
    }
	goto st3;
tr89:
#line 79 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::None;
    }
	goto st3;
tr99:
#line 63 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._secure = true;
    }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 1915 "src/panda/protocol/http/CookieParser.cc"
	if ( (*p) == 32 )
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	switch( (*p) ) {
		case 59: goto st0;
		case 68: goto st13;
		case 69: goto st21;
		case 72: goto st30;
		case 77: goto st38;
		case 80: goto st47;
		case 83: goto st53;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	switch( (*p) ) {
		case 59: goto st3;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	switch( (*p) ) {
		case 59: goto st3;
		case 111: goto st14;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	switch( (*p) ) {
		case 59: goto st3;
		case 109: goto st15;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	switch( (*p) ) {
		case 59: goto st3;
		case 97: goto st16;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 59: goto st3;
		case 105: goto st17;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	switch( (*p) ) {
		case 59: goto st3;
		case 110: goto st18;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	switch( (*p) ) {
		case 59: goto st3;
		case 61: goto st19;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	switch( (*p) ) {
		case 59: goto st3;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 31 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto tr32;
		} else if ( (*p) >= 0 )
			goto st0;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr32;
		} else if ( (*p) >= 65 )
			goto tr32;
	} else
		goto tr32;
	goto st12;
tr32:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 2053 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 59: goto tr34;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 31 ) {
			if ( 45 <= (*p) && (*p) <= 46 )
				goto st20;
		} else if ( (*p) >= 0 )
			goto st0;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st20;
		} else if ( (*p) >= 65 )
			goto st20;
	} else
		goto st20;
	goto st12;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	switch( (*p) ) {
		case 59: goto st3;
		case 120: goto st22;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	switch( (*p) ) {
		case 59: goto st3;
		case 112: goto st23;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 59: goto st3;
		case 105: goto st24;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	switch( (*p) ) {
		case 59: goto st3;
		case 114: goto st25;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	switch( (*p) ) {
		case 59: goto st3;
		case 101: goto st26;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 59: goto st3;
		case 115: goto st27;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 59: goto st3;
		case 61: goto st28;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 32: goto tr42;
		case 44: goto tr42;
		case 59: goto tr43;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( 0 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr42;
		} else if ( (*p) >= 65 )
			goto tr42;
	} else
		goto tr42;
	goto st12;
tr42:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
#line 2190 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 32: goto st29;
		case 44: goto st29;
		case 59: goto tr45;
		case 127: goto st0;
	}
	if ( (*p) < 48 ) {
		if ( 0 <= (*p) && (*p) <= 31 )
			goto st0;
	} else if ( (*p) > 58 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st29;
		} else if ( (*p) >= 65 )
			goto st29;
	} else
		goto st29;
	goto st12;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
	switch( (*p) ) {
		case 59: goto st3;
		case 116: goto st31;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
	switch( (*p) ) {
		case 59: goto st3;
		case 116: goto st32;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 59: goto st3;
		case 112: goto st33;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 59: goto st3;
		case 79: goto st34;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	switch( (*p) ) {
		case 59: goto st3;
		case 110: goto st35;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 59: goto st3;
		case 108: goto st36;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	switch( (*p) ) {
		case 59: goto st3;
		case 121: goto st37;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 59: goto tr53;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 59: goto st3;
		case 97: goto st39;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 59: goto st3;
		case 120: goto st40;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 45: goto st41;
		case 59: goto st3;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 59: goto st3;
		case 65: goto st42;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 59: goto st3;
		case 103: goto st43;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 59: goto st3;
		case 101: goto st44;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 59: goto st3;
		case 61: goto st45;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	switch( (*p) ) {
		case 59: goto st3;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 49 <= (*p) && (*p) <= 57 )
			goto tr61;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st12;
tr61:
#line 48 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._max_age;
        v = 0;
    }
#line 53 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._max_age;
        ADD_DIGIT(v);
    }
	goto st46;
tr62:
#line 53 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._max_age;
        ADD_DIGIT(v);
    }
	goto st46;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
#line 2425 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 59: goto st3;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr62;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st12;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	switch( (*p) ) {
		case 59: goto st3;
		case 97: goto st48;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	switch( (*p) ) {
		case 59: goto st3;
		case 116: goto st49;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 59: goto st3;
		case 104: goto st50;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	switch( (*p) ) {
		case 59: goto st3;
		case 61: goto st51;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 59: goto st3;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr67;
tr67:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st52;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
#line 2506 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 59: goto tr69;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st52;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 59: goto st3;
		case 97: goto st54;
		case 101: goto st75;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 59: goto st3;
		case 109: goto st55;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 59: goto st3;
		case 101: goto st56;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 59: goto st3;
		case 83: goto st57;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
	switch( (*p) ) {
		case 59: goto st3;
		case 105: goto st58;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 59: goto st3;
		case 116: goto st59;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 59: goto st3;
		case 101: goto st60;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 59: goto tr78;
		case 61: goto st61;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 59: goto st3;
		case 76: goto st62;
		case 78: goto st65;
		case 83: goto st69;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	switch( (*p) ) {
		case 59: goto st3;
		case 97: goto st63;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	switch( (*p) ) {
		case 59: goto st3;
		case 120: goto st64;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 59: goto tr85;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 59: goto st3;
		case 111: goto st66;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	switch( (*p) ) {
		case 59: goto st3;
		case 110: goto st67;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 59: goto st3;
		case 101: goto st68;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 59: goto tr89;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	switch( (*p) ) {
		case 59: goto st3;
		case 116: goto st70;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	switch( (*p) ) {
		case 59: goto st3;
		case 114: goto st71;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 59: goto st3;
		case 105: goto st72;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 59: goto st3;
		case 99: goto st73;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	switch( (*p) ) {
		case 59: goto st3;
		case 116: goto st74;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	switch( (*p) ) {
		case 59: goto tr78;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	switch( (*p) ) {
		case 59: goto st3;
		case 99: goto st76;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	switch( (*p) ) {
		case 59: goto st3;
		case 117: goto st77;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	switch( (*p) ) {
		case 59: goto st3;
		case 114: goto st78;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	switch( (*p) ) {
		case 59: goto st3;
		case 101: goto st79;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 59: goto tr99;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st12;
tr21:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 2848 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 34: goto st80;
		case 44: goto st0;
		case 59: goto st0;
		case 92: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 32 )
		goto st0;
	goto st5;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	if ( (*p) == 59 )
		goto tr24;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	switch( (*p) ) {
		case 33: goto tr14;
		case 124: goto tr14;
		case 126: goto tr14;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr14;
		} else if ( (*p) >= 35 )
			goto tr14;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr14;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr14;
		} else
			goto tr14;
	} else
		goto tr14;
	goto st0;
tr14:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 2904 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 33: goto st7;
		case 61: goto tr16;
		case 124: goto st7;
		case 126: goto st7;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st7;
		} else if ( (*p) >= 35 )
			goto st7;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st7;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st7;
		} else
			goto st7;
	} else
		goto st7;
	goto st0;
tr16:
#line 16 "src/panda/protocol/http/CookieParser.rl"
	{
        string v;
        SAVE(v);
        request->cookies.add(v, {});
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st81;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
#line 2945 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 9: goto tr101;
		case 32: goto tr101;
		case 34: goto tr102;
		case 44: goto st0;
		case 59: goto tr103;
		case 92: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr100;
tr100:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st82;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
#line 2969 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 9: goto tr105;
		case 32: goto tr105;
		case 34: goto st0;
		case 44: goto st0;
		case 59: goto tr106;
		case 92: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st82;
tr101:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 22 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st83;
tr105:
#line 22 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st83;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
#line 3013 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 9: goto st83;
		case 32: goto st83;
	}
	goto st0;
tr103:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 22 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st8;
tr106:
#line 22 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 3050 "src/panda/protocol/http/CookieParser.cc"
	if ( (*p) == 32 )
		goto st6;
	goto st0;
tr102:
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 3065 "src/panda/protocol/http/CookieParser.cc"
	switch( (*p) ) {
		case 34: goto st84;
		case 44: goto st0;
		case 59: goto st0;
		case 92: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 32 )
		goto st0;
	goto st9;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 9: goto tr105;
		case 32: goto tr105;
		case 59: goto tr106;
	}
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
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
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 79: 
#line 63 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._secure = true;
    }
	break;
	case 37: 
#line 67 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._http_only = true;
    }
	break;
	case 60: 
	case 74: 
#line 71 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Strict;
    }
	break;
	case 64: 
#line 75 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::Lax;
    }
	break;
	case 68: 
#line 79 "src/panda/protocol/http/CookieParser.rl"
	{
        response->cookies.fields.back().value._same_site = Response::Cookie::SameSite::None;
    }
	break;
	case 82: 
	case 84: 
#line 22 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 11: 
	case 80: 
#line 33 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 20: 
#line 38 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._domain;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 52: 
#line 43 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._path;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 29: 
#line 58 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._expires;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 81: 
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 22 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = request->cookies.fields.back().value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 10: 
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 33 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._value;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
	case 28: 
#line 7 "src/panda/protocol/http/CookieParser.rl"
	{
        mark   = p - ps;
        //marked = true;
    }
#line 58 "src/panda/protocol/http/CookieParser.rl"
	{
        auto& v = response->cookies.fields.back().value._expires;
        SAVE(v);
    }
#line 12 "src/panda/protocol/http/CookieParser.rl"
	{
        //marked = false;
    }
	break;
#line 3311 "src/panda/protocol/http/CookieParser.cc"
	}
	}

	_out: {}
	}

#line 158 "src/panda/protocol/http/CookieParser.rl"
}

#endif

}}}
