#!/bin/bash

(echo A && echo B) || (echo C && echo D)
(echo hello world)
(echo hello world && ls -a)
(echo A) || (echo B)
((echo A && echo B) || (echo C)) && ls
exit

