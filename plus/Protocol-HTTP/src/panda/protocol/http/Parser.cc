
#line 1 "src/panda/protocol/http/Parser.rl"
#include "Parser.h"


#line 93 "src/panda/protocol/http/Parser.rl"


namespace panda { namespace protocol { namespace http {


#line 13 "src/panda/protocol/http/Parser.cc"
static const int http_parser_start = 1;
static const int http_parser_first_final = 190;
static const int http_parser_error = 0;

static const int http_parser_en_first_chunk = 64;
static const int http_parser_en_chunk = 74;
static const int http_parser_en_chunk_trailer = 86;
static const int http_parser_en_request = 92;
static const int http_parser_en_response = 1;


#line 98 "src/panda/protocol/http/Parser.rl"

#ifndef PARSER_CONSTANTS

#define ADD_DIGIT(dest) \
    dest *= 10;         \
    dest += *p - '0';
    
#define ADD_XDIGIT(dest) \
    dest *= 16;          \
    dest += (*p | 0x20) >= 'a' ? (*p - 'a' + 10) : (*p - '0');

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
    
#line 49 "src/panda/protocol/http/Parser.cc"
	{
	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	switch ( cs ) {
case 1:
	if ( (*p) == 72 )
		goto tr0;
	goto tr1;
case 0:
	goto _out;
case 2:
	if ( (*p) == 84 )
		goto tr2;
	goto tr1;
case 3:
	if ( (*p) == 84 )
		goto tr3;
	goto tr1;
case 4:
	if ( (*p) == 80 )
		goto tr4;
	goto tr1;
case 5:
	if ( (*p) == 47 )
		goto tr5;
	goto tr1;
case 6:
	if ( (*p) == 49 )
		goto tr6;
	goto tr1;
case 7:
	if ( (*p) == 46 )
		goto tr7;
	goto tr1;
case 8:
	switch( (*p) ) {
		case 48: goto tr8;
		case 49: goto tr9;
	}
	goto tr1;
case 9:
	if ( (*p) == 32 )
		goto tr10;
	goto tr1;
case 10:
	if ( 49 <= (*p) && (*p) <= 57 )
		goto tr11;
	goto tr1;
case 11:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr12;
	goto tr1;
case 12:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr13;
	goto tr1;
case 13:
	if ( (*p) == 32 )
		goto tr14;
	goto tr1;
case 14:
	switch( (*p) ) {
		case 13: goto tr16;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr15;
case 15:
	switch( (*p) ) {
		case 13: goto tr18;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr17;
case 16:
	if ( (*p) == 10 )
		goto tr19;
	goto tr1;
case 17:
	switch( (*p) ) {
		case 13: goto tr20;
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
	goto tr1;
case 18:
	if ( (*p) == 10 )
		goto tr24;
	goto tr1;
case 190:
	goto tr1;
case 19:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 20:
	switch( (*p) ) {
		case 9: goto tr28;
		case 13: goto tr29;
		case 32: goto tr28;
		case 127: goto tr1;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto tr1;
	goto tr27;
case 21:
	switch( (*p) ) {
		case 13: goto tr31;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr30;
case 22:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 79: goto tr32;
		case 111: goto tr32;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 23:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 78: goto tr33;
		case 110: goto tr33;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 24:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 84: goto tr34;
		case 116: goto tr34;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 25:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 69: goto tr35;
		case 101: goto tr35;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 26:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 78: goto tr36;
		case 110: goto tr36;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 27:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 84: goto tr37;
		case 116: goto tr37;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 28:
	switch( (*p) ) {
		case 33: goto tr25;
		case 45: goto tr38;
		case 46: goto tr25;
		case 58: goto tr26;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else if ( (*p) >= 65 )
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 29:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 76: goto tr39;
		case 108: goto tr39;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 30:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 69: goto tr40;
		case 101: goto tr40;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 31:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 78: goto tr41;
		case 110: goto tr41;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 32:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 71: goto tr42;
		case 103: goto tr42;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 33:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 84: goto tr43;
		case 116: goto tr43;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 34:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 72: goto tr44;
		case 104: goto tr44;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 35:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr45;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 36:
	switch( (*p) ) {
		case 9: goto tr46;
		case 13: goto tr29;
		case 32: goto tr46;
		case 127: goto tr1;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr47;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr27;
case 37:
	switch( (*p) ) {
		case 13: goto tr31;
		case 127: goto tr1;
	}
	if ( (*p) < 10 ) {
		if ( 0 <= (*p) && (*p) <= 8 )
			goto tr1;
	} else if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr48;
	} else
		goto tr1;
	goto tr30;
case 38:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 82: goto tr49;
		case 114: goto tr49;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 39:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 65: goto tr50;
		case 97: goto tr50;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 66 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 40:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 78: goto tr51;
		case 110: goto tr51;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 41:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 83: goto tr52;
		case 115: goto tr52;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 42:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 70: goto tr53;
		case 102: goto tr53;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 43:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 69: goto tr54;
		case 101: goto tr54;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 44:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 82: goto tr55;
		case 114: goto tr55;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 45:
	switch( (*p) ) {
		case 33: goto tr25;
		case 45: goto tr56;
		case 46: goto tr25;
		case 58: goto tr26;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else if ( (*p) >= 65 )
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 46:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 69: goto tr57;
		case 101: goto tr57;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 47:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 78: goto tr58;
		case 110: goto tr58;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 48:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 67: goto tr59;
		case 99: goto tr59;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 49:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 79: goto tr60;
		case 111: goto tr60;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 50:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 68: goto tr61;
		case 100: goto tr61;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 51:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 73: goto tr62;
		case 105: goto tr62;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 52:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 78: goto tr63;
		case 110: goto tr63;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 53:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr26;
		case 71: goto tr64;
		case 103: goto tr64;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 54:
	switch( (*p) ) {
		case 33: goto tr25;
		case 58: goto tr65;
		case 124: goto tr25;
		case 126: goto tr25;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr25;
		} else if ( (*p) >= 35 )
			goto tr25;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr25;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr25;
		} else
			goto tr25;
	} else
		goto tr25;
	goto tr1;
case 55:
	switch( (*p) ) {
		case 9: goto tr66;
		case 13: goto tr29;
		case 32: goto tr66;
		case 67: goto tr67;
		case 99: goto tr67;
		case 127: goto tr1;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto tr1;
	goto tr27;
case 56:
	switch( (*p) ) {
		case 13: goto tr31;
		case 72: goto tr68;
		case 104: goto tr68;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr30;
case 57:
	switch( (*p) ) {
		case 13: goto tr31;
		case 85: goto tr69;
		case 117: goto tr69;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr30;
case 58:
	switch( (*p) ) {
		case 13: goto tr31;
		case 78: goto tr70;
		case 110: goto tr70;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr30;
case 59:
	switch( (*p) ) {
		case 13: goto tr31;
		case 75: goto tr71;
		case 107: goto tr71;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr30;
case 60:
	switch( (*p) ) {
		case 13: goto tr31;
		case 69: goto tr72;
		case 101: goto tr72;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr30;
case 61:
	switch( (*p) ) {
		case 13: goto tr31;
		case 68: goto tr73;
		case 100: goto tr73;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr30;
case 62:
	switch( (*p) ) {
		case 9: goto tr74;
		case 13: goto tr75;
		case 32: goto tr74;
		case 127: goto tr1;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto tr1;
	goto tr30;
case 63:
	if ( (*p) == 32 )
		goto tr76;
	goto tr1;
case 64:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr77;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr77;
	} else
		goto tr77;
	goto tr1;
case 65:
	switch( (*p) ) {
		case 13: goto tr78;
		case 59: goto tr80;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr79;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr79;
	} else
		goto tr79;
	goto tr1;
case 66:
	if ( (*p) == 10 )
		goto tr81;
	goto tr1;
case 191:
	goto tr1;
case 67:
	switch( (*p) ) {
		case 33: goto tr82;
		case 124: goto tr82;
		case 126: goto tr82;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr82;
		} else if ( (*p) >= 35 )
			goto tr82;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr82;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr82;
		} else
			goto tr82;
	} else
		goto tr82;
	goto tr1;
case 68:
	switch( (*p) ) {
		case 13: goto tr78;
		case 33: goto tr82;
		case 59: goto tr80;
		case 61: goto tr83;
		case 124: goto tr82;
		case 126: goto tr82;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr82;
		} else if ( (*p) >= 35 )
			goto tr82;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr82;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr82;
		} else
			goto tr82;
	} else
		goto tr82;
	goto tr1;
case 69:
	switch( (*p) ) {
		case 34: goto tr85;
		case 124: goto tr84;
		case 126: goto tr84;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr84;
		} else if ( (*p) >= 33 )
			goto tr84;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr84;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr84;
		} else
			goto tr84;
	} else
		goto tr84;
	goto tr1;
case 70:
	switch( (*p) ) {
		case 13: goto tr78;
		case 33: goto tr84;
		case 59: goto tr80;
		case 124: goto tr84;
		case 126: goto tr84;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr84;
		} else if ( (*p) >= 35 )
			goto tr84;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr84;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr84;
		} else
			goto tr84;
	} else
		goto tr84;
	goto tr1;
case 71:
	switch( (*p) ) {
		case 34: goto tr86;
		case 92: goto tr87;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr85;
case 72:
	switch( (*p) ) {
		case 13: goto tr78;
		case 59: goto tr80;
	}
	goto tr1;
case 73:
	if ( (*p) == 127 )
		goto tr1;
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr85;
case 74:
	if ( (*p) == 13 )
		goto tr88;
	goto tr1;
case 75:
	if ( (*p) == 10 )
		goto tr89;
	goto tr1;
case 76:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr90;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr90;
	} else
		goto tr90;
	goto tr1;
case 77:
	switch( (*p) ) {
		case 13: goto tr91;
		case 59: goto tr93;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr92;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr92;
	} else
		goto tr92;
	goto tr1;
case 78:
	if ( (*p) == 10 )
		goto tr94;
	goto tr1;
case 192:
	goto tr1;
case 79:
	switch( (*p) ) {
		case 33: goto tr95;
		case 124: goto tr95;
		case 126: goto tr95;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr95;
		} else if ( (*p) >= 35 )
			goto tr95;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr95;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr95;
		} else
			goto tr95;
	} else
		goto tr95;
	goto tr1;
case 80:
	switch( (*p) ) {
		case 13: goto tr91;
		case 33: goto tr95;
		case 59: goto tr93;
		case 61: goto tr96;
		case 124: goto tr95;
		case 126: goto tr95;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr95;
		} else if ( (*p) >= 35 )
			goto tr95;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr95;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr95;
		} else
			goto tr95;
	} else
		goto tr95;
	goto tr1;
case 81:
	switch( (*p) ) {
		case 34: goto tr98;
		case 124: goto tr97;
		case 126: goto tr97;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr97;
		} else if ( (*p) >= 33 )
			goto tr97;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr97;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr97;
		} else
			goto tr97;
	} else
		goto tr97;
	goto tr1;
case 82:
	switch( (*p) ) {
		case 13: goto tr91;
		case 33: goto tr97;
		case 59: goto tr93;
		case 124: goto tr97;
		case 126: goto tr97;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr97;
		} else if ( (*p) >= 35 )
			goto tr97;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr97;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr97;
		} else
			goto tr97;
	} else
		goto tr97;
	goto tr1;
case 83:
	switch( (*p) ) {
		case 34: goto tr99;
		case 92: goto tr100;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr98;
case 84:
	switch( (*p) ) {
		case 13: goto tr91;
		case 59: goto tr93;
	}
	goto tr1;
case 85:
	if ( (*p) == 127 )
		goto tr1;
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr98;
case 86:
	switch( (*p) ) {
		case 13: goto tr101;
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
	goto tr1;
case 87:
	if ( (*p) == 10 )
		goto tr103;
	goto tr1;
case 193:
	goto tr1;
case 88:
	switch( (*p) ) {
		case 33: goto tr104;
		case 58: goto tr105;
		case 124: goto tr104;
		case 126: goto tr104;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr104;
		} else if ( (*p) >= 35 )
			goto tr104;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr104;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr104;
		} else
			goto tr104;
	} else
		goto tr104;
	goto tr1;
case 89:
	switch( (*p) ) {
		case 9: goto tr107;
		case 13: goto tr108;
		case 32: goto tr107;
		case 127: goto tr1;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto tr1;
	goto tr106;
case 90:
	switch( (*p) ) {
		case 13: goto tr110;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr109;
case 91:
	if ( (*p) == 10 )
		goto tr111;
	goto tr1;
case 92:
	switch( (*p) ) {
		case 67: goto tr112;
		case 68: goto tr113;
		case 71: goto tr114;
		case 72: goto tr115;
		case 79: goto tr116;
		case 80: goto tr117;
		case 84: goto tr118;
	}
	goto tr1;
case 93:
	if ( (*p) == 79 )
		goto tr119;
	goto tr1;
case 94:
	if ( (*p) == 78 )
		goto tr120;
	goto tr1;
case 95:
	if ( (*p) == 78 )
		goto tr121;
	goto tr1;
case 96:
	if ( (*p) == 69 )
		goto tr122;
	goto tr1;
case 97:
	if ( (*p) == 67 )
		goto tr123;
	goto tr1;
case 98:
	if ( (*p) == 84 )
		goto tr124;
	goto tr1;
case 99:
	if ( (*p) == 32 )
		goto tr125;
	goto tr1;
case 100:
	if ( 33 <= (*p) && (*p) <= 126 )
		goto tr126;
	goto tr1;
case 101:
	if ( (*p) == 32 )
		goto tr127;
	if ( 33 <= (*p) && (*p) <= 126 )
		goto tr128;
	goto tr1;
case 102:
	if ( (*p) == 72 )
		goto tr129;
	goto tr1;
case 103:
	if ( (*p) == 84 )
		goto tr130;
	goto tr1;
case 104:
	if ( (*p) == 84 )
		goto tr131;
	goto tr1;
case 105:
	if ( (*p) == 80 )
		goto tr132;
	goto tr1;
case 106:
	if ( (*p) == 47 )
		goto tr133;
	goto tr1;
case 107:
	if ( (*p) == 49 )
		goto tr134;
	goto tr1;
case 108:
	if ( (*p) == 46 )
		goto tr135;
	goto tr1;
case 109:
	switch( (*p) ) {
		case 48: goto tr136;
		case 49: goto tr137;
	}
	goto tr1;
case 110:
	if ( (*p) == 13 )
		goto tr138;
	goto tr1;
case 111:
	if ( (*p) == 10 )
		goto tr139;
	goto tr1;
case 112:
	switch( (*p) ) {
		case 13: goto tr140;
		case 33: goto tr141;
		case 67: goto tr142;
		case 84: goto tr143;
		case 99: goto tr142;
		case 116: goto tr143;
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
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr141;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr141;
		} else
			goto tr141;
	} else
		goto tr141;
	goto tr1;
case 113:
	if ( (*p) == 10 )
		goto tr144;
	goto tr1;
case 194:
	goto tr1;
case 114:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 115:
	switch( (*p) ) {
		case 9: goto tr148;
		case 13: goto tr149;
		case 32: goto tr148;
		case 127: goto tr1;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto tr1;
	goto tr147;
case 116:
	switch( (*p) ) {
		case 13: goto tr151;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr150;
case 117:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 79: goto tr152;
		case 111: goto tr152;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 118:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 78: goto tr153;
		case 110: goto tr153;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 119:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 84: goto tr154;
		case 116: goto tr154;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 120:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 69: goto tr155;
		case 101: goto tr155;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 121:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 78: goto tr156;
		case 110: goto tr156;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 122:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 84: goto tr157;
		case 116: goto tr157;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 123:
	switch( (*p) ) {
		case 33: goto tr145;
		case 45: goto tr158;
		case 46: goto tr145;
		case 58: goto tr146;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else if ( (*p) >= 65 )
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 124:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 76: goto tr159;
		case 108: goto tr159;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 125:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 69: goto tr160;
		case 101: goto tr160;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 126:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 78: goto tr161;
		case 110: goto tr161;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 127:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 71: goto tr162;
		case 103: goto tr162;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 128:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 84: goto tr163;
		case 116: goto tr163;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 129:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 72: goto tr164;
		case 104: goto tr164;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 130:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr165;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 131:
	switch( (*p) ) {
		case 9: goto tr166;
		case 13: goto tr149;
		case 32: goto tr166;
		case 127: goto tr1;
	}
	if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr167;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr147;
case 132:
	switch( (*p) ) {
		case 13: goto tr151;
		case 127: goto tr1;
	}
	if ( (*p) < 10 ) {
		if ( 0 <= (*p) && (*p) <= 8 )
			goto tr1;
	} else if ( (*p) > 31 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr168;
	} else
		goto tr1;
	goto tr150;
case 133:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 82: goto tr169;
		case 114: goto tr169;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 134:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 65: goto tr170;
		case 97: goto tr170;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 66 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 135:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 78: goto tr171;
		case 110: goto tr171;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 136:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 83: goto tr172;
		case 115: goto tr172;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 137:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 70: goto tr173;
		case 102: goto tr173;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 138:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 69: goto tr174;
		case 101: goto tr174;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 139:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 82: goto tr175;
		case 114: goto tr175;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 140:
	switch( (*p) ) {
		case 33: goto tr145;
		case 45: goto tr176;
		case 46: goto tr145;
		case 58: goto tr146;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else if ( (*p) >= 65 )
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 141:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 69: goto tr177;
		case 101: goto tr177;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 142:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 78: goto tr178;
		case 110: goto tr178;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 143:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 67: goto tr179;
		case 99: goto tr179;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 144:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 79: goto tr180;
		case 111: goto tr180;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 145:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 68: goto tr181;
		case 100: goto tr181;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 146:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 73: goto tr182;
		case 105: goto tr182;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 147:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 78: goto tr183;
		case 110: goto tr183;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 148:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr146;
		case 71: goto tr184;
		case 103: goto tr184;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 149:
	switch( (*p) ) {
		case 33: goto tr145;
		case 58: goto tr185;
		case 124: goto tr145;
		case 126: goto tr145;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr145;
		} else if ( (*p) >= 35 )
			goto tr145;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr145;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr145;
		} else
			goto tr145;
	} else
		goto tr145;
	goto tr1;
case 150:
	switch( (*p) ) {
		case 9: goto tr186;
		case 13: goto tr149;
		case 32: goto tr186;
		case 67: goto tr187;
		case 99: goto tr187;
		case 127: goto tr1;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto tr1;
	goto tr147;
case 151:
	switch( (*p) ) {
		case 13: goto tr151;
		case 72: goto tr188;
		case 104: goto tr188;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr150;
case 152:
	switch( (*p) ) {
		case 13: goto tr151;
		case 85: goto tr189;
		case 117: goto tr189;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr150;
case 153:
	switch( (*p) ) {
		case 13: goto tr151;
		case 78: goto tr190;
		case 110: goto tr190;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr150;
case 154:
	switch( (*p) ) {
		case 13: goto tr151;
		case 75: goto tr191;
		case 107: goto tr191;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr150;
case 155:
	switch( (*p) ) {
		case 13: goto tr151;
		case 69: goto tr192;
		case 101: goto tr192;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr150;
case 156:
	switch( (*p) ) {
		case 13: goto tr151;
		case 68: goto tr193;
		case 100: goto tr193;
		case 127: goto tr1;
	}
	if ( (*p) > 8 ) {
		if ( 10 <= (*p) && (*p) <= 31 )
			goto tr1;
	} else if ( (*p) >= 0 )
		goto tr1;
	goto tr150;
case 157:
	switch( (*p) ) {
		case 9: goto tr194;
		case 13: goto tr195;
		case 32: goto tr194;
		case 127: goto tr1;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto tr1;
	goto tr150;
case 158:
	if ( (*p) == 13 )
		goto tr196;
	goto tr1;
case 159:
	if ( (*p) == 69 )
		goto tr197;
	goto tr1;
case 160:
	if ( (*p) == 76 )
		goto tr198;
	goto tr1;
case 161:
	if ( (*p) == 69 )
		goto tr199;
	goto tr1;
case 162:
	if ( (*p) == 84 )
		goto tr200;
	goto tr1;
case 163:
	if ( (*p) == 69 )
		goto tr201;
	goto tr1;
case 164:
	if ( (*p) == 32 )
		goto tr202;
	goto tr1;
case 165:
	if ( (*p) == 69 )
		goto tr203;
	goto tr1;
case 166:
	if ( (*p) == 84 )
		goto tr204;
	goto tr1;
case 167:
	if ( (*p) == 32 )
		goto tr205;
	goto tr1;
case 168:
	if ( (*p) == 69 )
		goto tr206;
	goto tr1;
case 169:
	if ( (*p) == 65 )
		goto tr207;
	goto tr1;
case 170:
	if ( (*p) == 68 )
		goto tr208;
	goto tr1;
case 171:
	if ( (*p) == 32 )
		goto tr209;
	goto tr1;
case 172:
	if ( (*p) == 80 )
		goto tr210;
	goto tr1;
case 173:
	if ( (*p) == 84 )
		goto tr211;
	goto tr1;
case 174:
	if ( (*p) == 73 )
		goto tr212;
	goto tr1;
case 175:
	if ( (*p) == 79 )
		goto tr213;
	goto tr1;
case 176:
	if ( (*p) == 78 )
		goto tr214;
	goto tr1;
case 177:
	if ( (*p) == 83 )
		goto tr215;
	goto tr1;
case 178:
	if ( (*p) == 32 )
		goto tr216;
	goto tr1;
case 179:
	switch( (*p) ) {
		case 79: goto tr217;
		case 85: goto tr218;
	}
	goto tr1;
case 180:
	if ( (*p) == 83 )
		goto tr219;
	goto tr1;
case 181:
	if ( (*p) == 84 )
		goto tr220;
	goto tr1;
case 182:
	if ( (*p) == 32 )
		goto tr221;
	goto tr1;
case 183:
	if ( (*p) == 84 )
		goto tr222;
	goto tr1;
case 184:
	if ( (*p) == 32 )
		goto tr223;
	goto tr1;
case 185:
	if ( (*p) == 82 )
		goto tr224;
	goto tr1;
case 186:
	if ( (*p) == 65 )
		goto tr225;
	goto tr1;
case 187:
	if ( (*p) == 67 )
		goto tr226;
	goto tr1;
case 188:
	if ( (*p) == 69 )
		goto tr227;
	goto tr1;
case 189:
	if ( (*p) == 32 )
		goto tr228;
	goto tr1;
	}

	tr1: cs = 0; goto _again;
	tr0: cs = 2; goto _again;
	tr2: cs = 3; goto _again;
	tr3: cs = 4; goto _again;
	tr4: cs = 5; goto _again;
	tr5: cs = 6; goto _again;
	tr6: cs = 7; goto _again;
	tr7: cs = 8; goto _again;
	tr8: cs = 9; goto _again;
	tr10: cs = 10; goto f0;
	tr76: cs = 10; goto f12;
	tr11: cs = 11; goto _again;
	tr12: cs = 12; goto f1;
	tr13: cs = 13; goto f1;
	tr14: cs = 14; goto _again;
	tr17: cs = 15; goto _again;
	tr15: cs = 15; goto f2;
	tr16: cs = 16; goto f3;
	tr18: cs = 16; goto f4;
	tr29: cs = 16; goto f6;
	tr31: cs = 16; goto f7;
	tr75: cs = 16; goto f11;
	tr19: cs = 17; goto _again;
	tr20: cs = 18; goto _again;
	tr25: cs = 19; goto _again;
	tr21: cs = 19; goto f2;
	tr28: cs = 20; goto _again;
	tr26: cs = 20; goto f5;
	tr30: cs = 21; goto _again;
	tr27: cs = 21; goto f2;
	tr74: cs = 21; goto f10;
	tr22: cs = 22; goto f2;
	tr32: cs = 23; goto _again;
	tr33: cs = 24; goto _again;
	tr34: cs = 25; goto _again;
	tr35: cs = 26; goto _again;
	tr36: cs = 27; goto _again;
	tr37: cs = 28; goto _again;
	tr38: cs = 29; goto _again;
	tr39: cs = 30; goto _again;
	tr40: cs = 31; goto _again;
	tr41: cs = 32; goto _again;
	tr42: cs = 33; goto _again;
	tr43: cs = 34; goto _again;
	tr44: cs = 35; goto _again;
	tr46: cs = 36; goto _again;
	tr45: cs = 36; goto f5;
	tr47: cs = 37; goto f8;
	tr48: cs = 37; goto f9;
	tr23: cs = 38; goto f2;
	tr49: cs = 39; goto _again;
	tr50: cs = 40; goto _again;
	tr51: cs = 41; goto _again;
	tr52: cs = 42; goto _again;
	tr53: cs = 43; goto _again;
	tr54: cs = 44; goto _again;
	tr55: cs = 45; goto _again;
	tr56: cs = 46; goto _again;
	tr57: cs = 47; goto _again;
	tr58: cs = 48; goto _again;
	tr59: cs = 49; goto _again;
	tr60: cs = 50; goto _again;
	tr61: cs = 51; goto _again;
	tr62: cs = 52; goto _again;
	tr63: cs = 53; goto _again;
	tr64: cs = 54; goto _again;
	tr66: cs = 55; goto _again;
	tr65: cs = 55; goto f5;
	tr67: cs = 56; goto f2;
	tr68: cs = 57; goto _again;
	tr69: cs = 58; goto _again;
	tr70: cs = 59; goto _again;
	tr71: cs = 60; goto _again;
	tr72: cs = 61; goto _again;
	tr73: cs = 62; goto _again;
	tr9: cs = 63; goto _again;
	tr77: cs = 65; goto f13;
	tr79: cs = 65; goto f14;
	tr78: cs = 66; goto _again;
	tr80: cs = 67; goto _again;
	tr82: cs = 68; goto _again;
	tr83: cs = 69; goto _again;
	tr84: cs = 70; goto _again;
	tr85: cs = 71; goto _again;
	tr86: cs = 72; goto _again;
	tr87: cs = 73; goto _again;
	tr88: cs = 75; goto _again;
	tr89: cs = 76; goto _again;
	tr90: cs = 77; goto f13;
	tr92: cs = 77; goto f14;
	tr91: cs = 78; goto _again;
	tr93: cs = 79; goto _again;
	tr95: cs = 80; goto _again;
	tr96: cs = 81; goto _again;
	tr97: cs = 82; goto _again;
	tr98: cs = 83; goto _again;
	tr99: cs = 84; goto _again;
	tr100: cs = 85; goto _again;
	tr111: cs = 86; goto _again;
	tr101: cs = 87; goto _again;
	tr104: cs = 88; goto _again;
	tr102: cs = 88; goto f2;
	tr107: cs = 89; goto _again;
	tr105: cs = 89; goto f5;
	tr109: cs = 90; goto _again;
	tr106: cs = 90; goto f2;
	tr108: cs = 91; goto f6;
	tr110: cs = 91; goto f7;
	tr112: cs = 93; goto _again;
	tr119: cs = 94; goto _again;
	tr120: cs = 95; goto _again;
	tr121: cs = 96; goto _again;
	tr122: cs = 97; goto _again;
	tr123: cs = 98; goto _again;
	tr124: cs = 99; goto _again;
	tr125: cs = 100; goto f15;
	tr202: cs = 100; goto f17;
	tr205: cs = 100; goto f18;
	tr209: cs = 100; goto f19;
	tr216: cs = 100; goto f20;
	tr221: cs = 100; goto f21;
	tr223: cs = 100; goto f22;
	tr228: cs = 100; goto f23;
	tr128: cs = 101; goto _again;
	tr126: cs = 101; goto f2;
	tr127: cs = 102; goto f16;
	tr129: cs = 103; goto _again;
	tr130: cs = 104; goto _again;
	tr131: cs = 105; goto _again;
	tr132: cs = 106; goto _again;
	tr133: cs = 107; goto _again;
	tr134: cs = 108; goto _again;
	tr135: cs = 109; goto _again;
	tr136: cs = 110; goto _again;
	tr138: cs = 111; goto f0;
	tr149: cs = 111; goto f6;
	tr151: cs = 111; goto f7;
	tr195: cs = 111; goto f11;
	tr196: cs = 111; goto f12;
	tr139: cs = 112; goto _again;
	tr140: cs = 113; goto _again;
	tr145: cs = 114; goto _again;
	tr141: cs = 114; goto f2;
	tr148: cs = 115; goto _again;
	tr146: cs = 115; goto f5;
	tr150: cs = 116; goto _again;
	tr147: cs = 116; goto f2;
	tr194: cs = 116; goto f10;
	tr142: cs = 117; goto f2;
	tr152: cs = 118; goto _again;
	tr153: cs = 119; goto _again;
	tr154: cs = 120; goto _again;
	tr155: cs = 121; goto _again;
	tr156: cs = 122; goto _again;
	tr157: cs = 123; goto _again;
	tr158: cs = 124; goto _again;
	tr159: cs = 125; goto _again;
	tr160: cs = 126; goto _again;
	tr161: cs = 127; goto _again;
	tr162: cs = 128; goto _again;
	tr163: cs = 129; goto _again;
	tr164: cs = 130; goto _again;
	tr166: cs = 131; goto _again;
	tr165: cs = 131; goto f5;
	tr167: cs = 132; goto f8;
	tr168: cs = 132; goto f9;
	tr143: cs = 133; goto f2;
	tr169: cs = 134; goto _again;
	tr170: cs = 135; goto _again;
	tr171: cs = 136; goto _again;
	tr172: cs = 137; goto _again;
	tr173: cs = 138; goto _again;
	tr174: cs = 139; goto _again;
	tr175: cs = 140; goto _again;
	tr176: cs = 141; goto _again;
	tr177: cs = 142; goto _again;
	tr178: cs = 143; goto _again;
	tr179: cs = 144; goto _again;
	tr180: cs = 145; goto _again;
	tr181: cs = 146; goto _again;
	tr182: cs = 147; goto _again;
	tr183: cs = 148; goto _again;
	tr184: cs = 149; goto _again;
	tr186: cs = 150; goto _again;
	tr185: cs = 150; goto f5;
	tr187: cs = 151; goto f2;
	tr188: cs = 152; goto _again;
	tr189: cs = 153; goto _again;
	tr190: cs = 154; goto _again;
	tr191: cs = 155; goto _again;
	tr192: cs = 156; goto _again;
	tr193: cs = 157; goto _again;
	tr137: cs = 158; goto _again;
	tr113: cs = 159; goto _again;
	tr197: cs = 160; goto _again;
	tr198: cs = 161; goto _again;
	tr199: cs = 162; goto _again;
	tr200: cs = 163; goto _again;
	tr201: cs = 164; goto _again;
	tr114: cs = 165; goto _again;
	tr203: cs = 166; goto _again;
	tr204: cs = 167; goto _again;
	tr115: cs = 168; goto _again;
	tr206: cs = 169; goto _again;
	tr207: cs = 170; goto _again;
	tr208: cs = 171; goto _again;
	tr116: cs = 172; goto _again;
	tr210: cs = 173; goto _again;
	tr211: cs = 174; goto _again;
	tr212: cs = 175; goto _again;
	tr213: cs = 176; goto _again;
	tr214: cs = 177; goto _again;
	tr215: cs = 178; goto _again;
	tr117: cs = 179; goto _again;
	tr217: cs = 180; goto _again;
	tr219: cs = 181; goto _again;
	tr220: cs = 182; goto _again;
	tr218: cs = 183; goto _again;
	tr222: cs = 184; goto _again;
	tr118: cs = 185; goto _again;
	tr224: cs = 186; goto _again;
	tr225: cs = 187; goto _again;
	tr226: cs = 188; goto _again;
	tr227: cs = 189; goto _again;
	tr24: cs = 190; goto _again;
	tr81: cs = 191; goto _again;
	tr94: cs = 192; goto _again;
	tr103: cs = 193; goto _again;
	tr144: cs = 194; goto _again;

f2:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark = p - ps;
    }
	goto _again;
f0:
#line 52 "src/panda/protocol/http/Parser.rl"
	{message->http_version = 10;}
	goto _again;
f12:
#line 52 "src/panda/protocol/http/Parser.rl"
	{message->http_version = 11;}
	goto _again;
f9:
#line 59 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(content_length)}
	goto _again;
f10:
#line 60 "src/panda/protocol/http/Parser.rl"
	{message->chunked = true;}
	goto _again;
f14:
#line 65 "src/panda/protocol/http/Parser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto _again;
f20:
#line 75 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::OPTIONS; }
	goto _again;
f18:
#line 76 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::GET; }
	goto _again;
f19:
#line 77 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::HEAD; }
	goto _again;
f21:
#line 78 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::POST; }
	goto _again;
f22:
#line 79 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::PUT; }
	goto _again;
f17:
#line 80 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::DELETE; }
	goto _again;
f23:
#line 81 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::TRACE; }
	goto _again;
f15:
#line 82 "src/panda/protocol/http/Parser.rl"
	{request->method = Request::Method::CONNECT; }
	goto _again;
f1:
#line 89 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(response->code)}
	goto _again;
f7:
#line 14 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 10 "src/panda/protocol/http/Parser.rl"
	{
        mark = -1;
    }
	goto _again;
f16:
#line 30 "src/panda/protocol/http/Parser.rl"
	{
        string target;
        SAVE(target);
        request->uri = new URI(target);
    }
#line 10 "src/panda/protocol/http/Parser.rl"
	{
        mark = -1;
    }
	goto _again;
f5:
#line 55 "src/panda/protocol/http/Parser.rl"
	{SAVE(field_name)}
#line 10 "src/panda/protocol/http/Parser.rl"
	{
        mark = -1;
    }
	goto _again;
f13:
#line 65 "src/panda/protocol/http/Parser.rl"
	{chunk_length = 0;}
#line 65 "src/panda/protocol/http/Parser.rl"
	{ADD_XDIGIT(chunk_length)}
	goto _again;
f4:
#line 90 "src/panda/protocol/http/Parser.rl"
	{SAVE(response->message)}
#line 10 "src/panda/protocol/http/Parser.rl"
	{
        mark = -1;
    }
	goto _again;
f6:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark = p - ps;
    }
#line 14 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 10 "src/panda/protocol/http/Parser.rl"
	{
        mark = -1;
    }
	goto _again;
f3:
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark = p - ps;
    }
#line 90 "src/panda/protocol/http/Parser.rl"
	{SAVE(response->message)}
#line 10 "src/panda/protocol/http/Parser.rl"
	{
        mark = -1;
    }
	goto _again;
f8:
#line 22 "src/panda/protocol/http/Parser.rl"
	{
        if (has_content_length) {
            cs = http_parser_error;
            {p++; goto _out; }
        }
        has_content_length = true;
    }
#line 59 "src/panda/protocol/http/Parser.rl"
	{ADD_DIGIT(content_length)}
#line 6 "src/panda/protocol/http/Parser.rl"
	{
        mark = p - ps;
    }
	goto _again;
f11:
#line 60 "src/panda/protocol/http/Parser.rl"
	{message->chunked = true;}
#line 14 "src/panda/protocol/http/Parser.rl"
	{
        string value;
        SAVE(value);
        if (value && value.back() <= 0x20) value.offset(0, value.find_last_not_of(" \t") + 1);
        if (!headers_finished) message->headers.add(field_name, value);
        else {} // trailing header after chunks, currently we just ignore them
    }
#line 10 "src/panda/protocol/http/Parser.rl"
	{
        mark = -1;
    }
	goto _again;

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 121 "src/panda/protocol/http/Parser.rl"
    return p - ps;
}

#endif

}}}
