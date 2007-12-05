#!/bin/sh
echo "Generate aclocal.m4..."
aclocal -I ./ -I /usr/local/share/aclocal/ -I /sw/share/aclocal/
echo "Generate configure..."
autoconf
echo "Generate Makefiles"
automake -a
echo "You can now compile freespeak with ./configure && make"
