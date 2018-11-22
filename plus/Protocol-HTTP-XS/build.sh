#!/bin/bash
cd ./src/panda/protocol/http
rm RequestParserGenerated.cc ResponseParserGenerated.cc 

# get ragel here http://www.colm.net/open-source/ragel/
./ragel -C -G1 RequestParser.rl -o RequestParserGenerated.cc
./ragel -C -G1 ResponseParser.rl -o ResponseParserGenerated.cc

cd -
perl Makefile.PL
make -j 

