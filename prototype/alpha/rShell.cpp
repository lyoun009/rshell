#include "rShell.h"
#include <iostream>
#include <string>
#include "parser.h"

using namespace std;

void rShell::run(){
    while(true){
        cout << "$";
        string userinput;
        getline(cin, userinput);
        if (userinput == "exit"){
            break;
        }
        auto parts = shellparse.parse(userinput);
        for (auto part:parts){
            auto type = part.first;
            auto args = part.second;
            shellexec.addCommand(type, args);
        }
        shellexec.execute();
    }

}