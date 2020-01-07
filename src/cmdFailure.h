#include "command.h"
#include <iostream>
#include <string>
#include <vector>

class cmdFailure: public command{

public:
cmdFailure(const vector<string>& arr, int depth): command(arr, depth){}

bool run(bool prev){
    if (prev){
        skipped = true;
        return true;
    }
    return internalRun();
}

};