#!/bin/bash

echo ls && test -d src
echo
echo hi && test -d src && echo exists
echo
echo test && test -e ../src1/ || echo failed
echo
echo test && test -f src/parser.h || echo not a file
echo
exit
