#!/bin/sh

#testing multiple commands

echo "* Test 1: echo 30 || echo 20 || echo 40 *"
echo; echo 30 || echo 20 || echo 40
echo 
echo "* Test 2: echo 30; echo 20; echo 40 *"
echo; echo 30; echo 20; echo 40
echo
echo "* Test 3: echo 30 && echo 20 && echo 40 *"
echo; echo 30 && echo 20 && echo 40
echo
echo "* Test 4: echo 20 && echo 30; echo 50 || echo 60 && echo 50 *"
echo; echo 20 && echo 30; echo 50 || echo 60 && echo 50
echo 
exit
