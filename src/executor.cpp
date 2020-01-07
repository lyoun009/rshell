#include "executor.h"
#include <queue>
#include <string>
#include <vector>
#include "command.h"
#include "cmdAlways.h"
#include "cmdFailure.h"
#include "cmdSuccess.h"

// creates commands based off of the connector type
void executor::addCommand(string type, const vector<string>& cmdarg, int depth){
    if (type == "&&"){
        command* pCmd = new cmdSuccess(cmdarg, depth);
        cmds.push(pCmd);
    }
    else if (type == "||"){
        command* pCmd = new cmdFailure(cmdarg, depth);
        cmds.push(pCmd);
    }
    else if (type == ";"){
        command* pCmd = new cmdAlways(cmdarg, depth);
        cmds.push(pCmd);
    }
}

bool executor::execute(){
    bool prev = true;
    bool allgood = true;
    int currentDepth = 0;
    bool lastSkipped = false;

    while (!cmds.empty()){
        command* pcmd = cmds.front();
        cmds.pop();
        
        if (lastSkipped && currentDepth > 0 && pcmd->getDepth() >= currentDepth){
          delete pcmd;
          continue;
        }

        prev = pcmd->run(prev);
        lastSkipped = pcmd->wasSkipped(); // for () cases
        currentDepth = pcmd->getDepth(); // for () cases

        if (!prev){
            allgood = false;
        }
        delete pcmd;
    }
    return allgood;
}