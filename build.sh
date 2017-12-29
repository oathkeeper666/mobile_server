#!/bin/bash

echo "create log, lib"
(mkdir -pv log && mkdir -pv lib)

echo "build third-part lib"
(cd thirdpart/mxml && ./configure && make && cp -v libmxml.a ../../lib/ && cp -v mxml.h ../../include/)
(cd thirdpart/LuaJIT/ && make && \
	cp -v src/lua.h ../../include/ && \
	cp -v src/lauxlib.h ../../include/ && \
	cp -v src/luaconf.h ../../include/ && \
	cp -v src/lualib.h ../../include/ && \
	cp -v src/libluajit.a ../../lib/)

(cd server && make clean && make)

