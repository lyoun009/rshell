#include "command.h"
#include <iostream>
#include <string>
#include <vector>

class cmdAlways: public command{

public:
cmdAlways(const vector<string>& arr): command(arr){}

bool run(bool prev){
    return internalRun();
}

};