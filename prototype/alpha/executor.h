#include <queue>
#include <string>
#include <vector>
#include "command.h"

using namespace std;

#ifndef _executor_H
#define _executor_H

class executor {
    public:
        void addCommand(string type, const vector<string>& cmdarg);
        void execute();
    private:
        queue<command*> cmds;
};

#endif