#!/bin/bash

# build third-part lib
(cd thirdpart/mxml && ./configure && make && cp -v libmxml.a ../../lib/ && cp -v mxml.h ../)

(cd framework && make)
