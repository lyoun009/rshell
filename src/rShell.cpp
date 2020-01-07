#include "rShell.h"
#include <iostream>
#include <string>
#include "parser.h"
#include "util.h"

using namespace std;

void rShell::run(){
    while(true){
        cout << "$";
        string userinput;
        getline(cin, userinput);

        // checks if user exited the shell
        if (userinput == "exit"){
            break;
        }

        //chk to see if () are uneven
        if (!Util::isValid(userinput)){
            cout << "Invalid input.\n";
            continue;
        }

        // breaks input into pieces and adds them to the executer so they can be executed
        auto parts = shellparse.parse(userinput);
        for (auto part : parts){
            auto type = part.connector;
            auto args = part.args;
            auto depth = part.depth;
            shellexec.addCommand(type, args, depth);
        }
        shellexec.execute();
    }
}