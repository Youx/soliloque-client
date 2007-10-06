#!/bin/sh
aclocal -I ./
autoconf
automake -a
echo "==== autogen.sh done ===="
echo "You can now compile freespeak with ./configure && make"
