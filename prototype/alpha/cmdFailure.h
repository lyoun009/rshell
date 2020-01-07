#include "command.h"
#include <iostream>
#include <string>
#include <vector>

class cmdFailure: public command{

public:
cmdFailure(const vector<string>& arr): command(arr){}

bool run(bool prev){
    if (prev){
        return true;
    }
    return internalRun();
}

};