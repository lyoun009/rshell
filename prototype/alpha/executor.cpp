#include "executor.h"
#include <queue>
#include <string>
#include <vector>
#include "command.h"
#include "cmdAlways.h"
#include "cmdFailure.h"
#include "cmdSuccess.h"

void executor::addCommand(string type, const vector<string>& cmdarg){
    if (type == "&&"){
        command* pCmd = new cmdSuccess(cmdarg);
        cmds.push(pCmd);
    }
    else if (type == "||"){
        command* pCmd = new cmdFailure(cmdarg);
        cmds.push(pCmd);
    }
    else if (type == ";"){
        command* pCmd = new cmdAlways(cmdarg);
        cmds.push(pCmd);
    }
}

void executor::execute(){
    bool prev = true;
    while (!cmds.empty()){
        command* pcmd = cmds.front();
        cmds.pop();
        prev = pcmd->run(prev);
        delete pcmd;
    }
}