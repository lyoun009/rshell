#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef _command_H
#define _command_H

class command{
    public:
        virtual bool run(bool prev) = 0;
        command(const vector<string>& arr);
    
    protected:
        bool internalRun();

    private:
        vector<string> args;
    


};

#endif