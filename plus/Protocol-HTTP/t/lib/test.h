#pragma once

#include <catch.hpp>

#ifdef seed
#undef seed
    #include <set>
    #include <cstring>
    #include <fstream>
    #include <dirent.h>
    #include <sys/types.h>
    #define seed() Perl_seed(aTHX)
#else
    #include <set>
    #include <cstring>
    #include <fstream>
    #include <dirent.h>
    #include <fstream>
    #include <sys/types.h>
#endif

#include <panda/refcnt.h>
#include <panda/uri/URI.h>
#include <panda/protocol/http/ParserError.h>
#include <panda/protocol/http/Request.h>
#include <panda/protocol/http/Response.h>
#include <panda/protocol/http/RequestParser.h>
#include <panda/protocol/http/ResponseParser.h>

//#define _DEBUG 1
#ifdef _DEBUG
#define _DBG(x) do { std::cerr << "[test-parser]" << x << std::endl; } while (0)
#else
#define _DBG(x)
#endif

using namespace panda;
using namespace protocol;

using State = http::RequestParser::State;
using Method = http::Request::Method;

const std::string TEST_ROOT = "t/src/";

using Directory = std::set<std::string>;

inline Directory read_directory(const std::string& name = ".") {
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    Directory v;
    while ((dp = readdir(dirp)) != NULL) {
        if (!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")) continue;
            v.insert(dp->d_name);
    }
    closedir(dirp);
    return v;
}
