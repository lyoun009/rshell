#include <iostream>
#include <string>
#include <vector>
#include "util.h"

using namespace std;

#ifndef _command_H
#define _command_H

class command{
    public:
        virtual bool run(bool prev) = 0; // run the command depending on if the prev command succeeded of failed 
        command(const vector<string>& arr, int depth);
        int getDepth();
        bool wasSkipped();
        
    protected:
        bool internalRun();
        bool skipped;
        bool runredir(int& old);
        bool doubleredir = false;
        bool singleright = false;
        bool singleleft = false;
        int posleft = 0;
        int posright = 0;
        vector<int> pipepos;
        bool redirpos();
        bool hasPipe();
        bool internalRunPipe();
        pid_t runPipe(int oldIn, int oldOut, int pIn, int pOut, char** cmd);

    private:
        vector<string> args;
        int depth;

        bool istest();
        bool runtest();
        bool ecase(int pos);
        bool fcase();
        bool dcase();
};

#endif