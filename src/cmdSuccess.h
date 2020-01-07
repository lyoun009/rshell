#include "command.h"
#include <iostream>
#include <string>
#include <vector>


class cmdSuccess: public command{

public: 
cmdSuccess(const vector<string>& arr, int depth): command(arr, depth){}

bool run(bool prev){
    if (!prev){
        skipped = true;
        return false;
    }
    return internalRun();
}

};

