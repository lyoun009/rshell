#!/bin/sh
echo test: && [ -e src/command.cpp ]
echo
echo test: && [ -f src/command.cpp ]
echo
echo test: && [ -d src ]
echo
echo test: && [ -e src ]
echo
echo test: && [ -f CMakeLists1.txt ]
echo
echo test: && [ -d unit_tests ]
echo
exit

