#!/bin/bash

echo test: && tail < commented_command_tests.sh
echo test: && wc < test_symbolic_tests.sh
echo test: && tail < precedence_tests.sh || ls -a
echo test && wc < commented_command_tests.sh
exit 

