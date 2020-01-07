#include "command.h"
#include <iostream>
#include <string>
#include <vector>


class cmdSuccess: public command{

public: 
cmdSuccess(const vector<string>& arr): command(arr){}

bool run(bool prev){
    if (!prev){
        return false;
    }
    return internalRun();
}

};

