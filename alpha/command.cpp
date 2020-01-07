#include "command.h"
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

command::command(const vector<string>& arr){
  args = arr;
}

bool command::internalRun(){
  pid_t pid;
  pid_t test;
  int status;

  int length = args.size();
  char** cArgs = new char*[length]; 
  for (int i = 0; i <length; ++i){
    cArgs[i] = const_cast<char*>(args[i].c_str());
  }

  pid = fork();
  if (pid == 0)
  {
    // here the child process is running as its at zero
    execvp(cArgs[0], cArgs); 

    // Should not get here ever, the weird case of fail
    // Does nothing case, bad command
    //cout << "Command failed\n";
    exit(0);
  }

  else
  {
    // parent process
    while(true)
    {
      pid_t test = wait(&status);
     
      if (test == pid){
        break;
      }
    }
  }
  
  return status == 0;
}

