#!/bin/sh

#testing single commands
echo TESTING: connectors
echo one || nothing     #shouldnt give an error bc of ||
echo two && echo three
echo four; echo five
echo ------------------------------------------------------------------; echo

#testing ls and ls -l
echo TESTING: ls and ls -l
echo Showing ls:
ls;                     #should print all files in current directory
echo          #should print newline
echo Showing ls -l:
ls -l
echo ------------------------------------------------------------------; echo

#testing mkdir
echo; echo TESTING: mkdir
mkdir temp_test_dir/
echo Made new directory called:   temp_test_dir/
echo
ls;     #should include all files plus "temp_test_dir/"
echo ------------------------------------------------------------------; echo

#testing rm
echo TESTING: rm and rm -rf
echo Try to remove with rm, should not work:
rm temp_test_dir    #should not remove yet??
echo
echo Should still show temp_test_dir in ls:
ls;
echo
echo Try to remove with rm -rf, should work:
rm -rf temp_test_dir
ls
echo ------------------------------------------------------------------; echo

#testing touch
echo TESTING: touch
echo Creating new file called new_test_file :
touch new_test_file    
echo
echo Should show new_test_file in ls:
ls; rm -f new_test_file
echo ------------------------------------------------------------------; echo

#testing git status
echo TESTING: git status
echo Creating new file called new_test_file2 :
touch new_test_file2    
echo
echo Showing status : 
git status
rm -f new_test_file2
echo ------------------------------------------------------------------; echo


echo end of testing
exit
