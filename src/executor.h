#include <queue>
#include <string>
#include <vector>
#include "command.h"
#include "parser.h"

using namespace std;

#ifndef _executor_H
#define _executor_H

class executor {
    public:
        void addCommand(string type, const vector<string>& cmdarg, int depth);
        bool execute();
    private:
        queue<command*> cmds;
};

#endif