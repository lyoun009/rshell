#include "command.h"
#include <iostream>
#include <string>
#include <vector>

class cmdAlways: public command{

public:
cmdAlways(const vector<string>& arr, int depth): command(arr, depth){}

bool run(bool prev){
    return internalRun();
}

};