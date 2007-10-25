#!/bin/sh
echo "Generate aclocal.m4..."
aclocal -I ./
echo "Generate configure..."
autoconf
echo "Generate Makefiles"
automake -a
echo "You can now compile freespeak with ./configure && make"
