#include "command.h"
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h> 
#include <fcntl.h> 
#include <regex>
#include "util.h"

using namespace std;

command::command(const vector<string>& arr, int d){
  args = arr;
  depth = d;
  skipped = false;
}

int command::getDepth(){
  return depth;
}

bool command::wasSkipped(){
  return skipped;
}

bool command::internalRun(){
  if (istest()){
    return runtest();
  }

  if (hasPipe()){
    return internalRunPipe();
  }

  int old = -1; //not a valid case
  runredir(old);

  pid_t pid;
  pid_t test;
  int status;

  int length = args.size();

  char** cArgs = new char*[length + 1]; 
  for (int i = 0; i <length; ++i){
    cArgs[i] = const_cast<char*>(args[i].c_str());
  }
  cArgs[length] = nullptr; // don't forget null at end!!!!

  pid = fork();
  if (pid == 0){
    // here the child process is running as its at zero
    execvp(cArgs[0], cArgs); 

    // Should not get here ever, the weird case of fail
    // Does nothing case, bad command
    exit(0);
  }

  else{
    // parent process
    while(true){
      pid_t test = wait(&status);
     
      if (test == pid){
        break;
      }
    }
  }
  
  if (old != -1){
    if (singleright || doubleredir){
      dup2(old, 1);
    }
    if (singleleft) { // left case
      dup2(old, 0);
    }
    close(old); //close everything either way
  }

  return status == 0;
}

// checks if the test functionality is being input
bool command::istest(){
  if (args.at(0) == "test" || args.at(0) == "["){
    return true;
  }

  return false;
}

// runs the test functionality
bool command::runtest(){
  bool hasswitch = false;
  if (args.at(1) == "-e" || args.at(1) == "-f" || args.at(1) == "-d"){
    hasswitch = true;
  }

  if (hasswitch){
    if (args.at(1) == "-e"){
      return ecase(2);
    }
    else if (args.at(1) == "-f"){
      return fcase();
    }
    else if (args.at(1) == "-d"){
      return dcase();
    }
  }
  else {
    return ecase(1);
  }
}

// the cases for the test functionality specifications
bool command::ecase(int pos){
  struct stat file;
  string inputPath = args.at(pos);

  if(stat(inputPath.c_str(), &file) != 0){
    cout << "(False)\n";
    return false;
  }
  
  cout << "(True)\n";
  return true;
}

bool command::dcase(){
  struct stat file;
  string inputPath = args.at(2);

  if(stat(inputPath.c_str(), &file) != 0){
    cout << "(False)\n";
    return false;
  }
  else if(file.st_mode & S_IFDIR ){
    cout << "(True)\n";
    return true;
  }
  
  cout << "(False)\n";
  return false;
}

bool command::fcase(){
  struct stat file;
  string inputPath = args.at(2);

  if (stat(inputPath.c_str(), &file) == 0 && S_ISREG(file.st_mode)){
    cout << "(True)\n";
    return true;
  }

  cout << "(False)\n";
  return false;
}


bool command::runredir(int& old){
  if (redirpos()) {
    if (singleright || doubleredir){ // "> case"
    int openfile = 0;
      args.erase(args.begin() + posright); // erase >
      if (posleft > posright){
        --posleft;
      }
      string filename = args.at(posright);
      args.erase(args.begin() + posright); // erase filename
      if (posleft > posright){
        --posleft;
      }
      if (singleright){
        openfile = open(filename.c_str(), O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
      }
      else{
        openfile = open(filename.c_str(), O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR); //Add to file case
      }
      if (openfile == -1){
        return false;
      }
      old = dup(1);
      dup2(openfile, 1);
      close(openfile);
      //return true;
    }
    if (singleleft){ // "< case"
      args.erase(args.begin() + posleft); // erase <
      if (posleft < posright){
        --posright;
      }
      string filename = args.at(posleft);
      args.erase(args.begin() + posleft); // erase filename
      if (posleft < posright){
        --posright;
      }
      int openfile = open(filename.c_str(), O_RDONLY, S_IRUSR | S_IWUSR); //read only case
      if (openfile == -1){
        return false;
      }
      old = dup(0);
      dup2(openfile, 0);
      close(openfile);
      return true;
    }
  }
  // Fully closes within internal run function
  return false;
}

bool command::redirpos(){
//Check to see if there is a redirection character
  bool overall = false;
  int i = 0;
  while (i < args.size()){
      if ((args.at(i).compare("<")) == 0){
        if (i >= args.size() - 1){
          return false; //bad input
        }
        posleft = i;
        singleleft = true;
        overall = true;
      }
      else if (args.at(i).compare(">>") == 0){
        if (i >= args.size() - 1){
          return false; //bad input
        }
        posright = i;
        doubleredir = true;
        overall = true;
      }
      else if (args.at(i).compare(">") == 0){
        if (i >= args.size() - 1){
          return false; //bad input
        }
        posright = i;
        singleright = true;
        overall = true;
      }
      ++i;
  }
  return overall;
}

  //Function to find a pipe command, may need to be changed, if needed.
  bool command::hasPipe(){
    bool overall = false;
    pipepos.clear();
    for (int i = 0; i < args.size(); ++ i){
        if(args.at(i) == "|"){
          pipepos.push_back(i); //Will give the positionn within args that the pipe command is at
          overall = true;
      }
    }
    return overall;
  }

  bool command::internalRunPipe(){
    int pi[2]{};
    int length = args.size();
    int pos = 0;
    int cpos = 0;
    int partCount = 0;
    char** cArgs = new char*[length + 1];
    int inOld = 0;
    int outOld = 0;

    pipe(pi);
    int input = pi[0];
    int output = pi[1];
    
    int firstPipePos = pipepos.at(0);
    int lastPipePos = pipepos.at(pipepos.size() - 1);

    while(pos < length){
      string& sArg = args.at(pos);

      if (sArg == "|" || pos == length-1){
        // at end?
        if (pos == length-1){
          cArgs[cpos] = (char*)sArg.c_str();
          ++cpos;
        }

        if (pos != firstPipePos && pos != length-1){
            pipe(pi);
            input = pi[0];
            output = pi[1];
        }
        if (pos == length-1){
          input = 0;
          output = 0;
        }
     
        cArgs[cpos] = nullptr; // don't forget null at end!!!! 
        runPipe(inOld, outOld, input, output, cArgs);
        if (pos != length-1){
          inOld = input;
          outOld = output;
        }
        ++partCount; //How many chuncks are there, how many processes are running
        cpos = 0; //reset the array once a chunck is 'removed'
      }
      else{
        cArgs[cpos] = (char*)sArg.c_str();
        ++cpos;
      }
      ++pos;
    }

    close(inOld); //So it doesn't run forever
    close (outOld);

    int status = 0;
    bool failed = false;
    for(int i = 0; i < partCount; ++i){
      wait(&status);
      if (status != 0){
        failed = true;
      }
    }

    return !failed;
  }

  pid_t command::runPipe(int oldIn, int oldOut, int newIn, int newOut, char** cmd){

    pid_t child_pid=0;

    child_pid = fork();

    if(child_pid == 0){
      if (oldIn){
        dup2(oldIn, 0);
        close(oldIn);
        close(oldOut);
      }

      if (newIn)
      {
        close(newIn);
        dup2(newOut, 1);
        close(newOut);
      }
      execvp(cmd[0], (char* const*)cmd);
      perror("ERROR!!!!\n");
        
      exit(1);
    }
    else
    {
      if (oldIn){
        close(oldIn);
        close(oldOut);
      }
    }
    
    return child_pid;
  }

