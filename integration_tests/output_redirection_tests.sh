#!/bin/sh


echo hello!! > outputs.txt
echo hey  >> outputs.txt
cat outputs.txt
echo adding stuff... >> stuff.txt && echo "almost done" >> stuff.txt
echo bye > stuff.txt
exit


