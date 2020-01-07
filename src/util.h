#ifndef _util_
#define _util_

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

// class of needed functions
class Util{
  public:

  static bool isValid(const string& line){
        int openCount = 0;
        int closeCount = 0;

        for(char c : line){
            if (c == '('){
                ++openCount;
            }
            else if (c == ')'){
                if (openCount <= closeCount){
                    return false;
                }
                ++closeCount;
                }
            }
        return openCount == closeCount;
    }

    //Unused, remove at later date
    /* 
    bool hasparen(const string& line){
        for (auto c: line){
            if (c == '(' || c == ')'){
                return true;
            }
        }
        return false;
    }*/

    // removes the () so the code can execute normally
    static string stripParens(const string& line){
       string result;
       for (auto c: line){
            if (!(c == '(' || c == ')')){
                result += c;
            }
       }
       return result;
    }

};

#endif