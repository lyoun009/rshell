#!/bin/sh

#testing exit function

echo Testing exit_function_1

echo testing exit_function_2  || exit #this should not exit

echo testing exit_function_3 && exit #this should not exit

exit; echo should not print anything: testing exit_function_4 #this should exit before the echo






