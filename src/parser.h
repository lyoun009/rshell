#include <string>
#include <vector>

#ifndef _parser_H
#define _parser_H

using namespace std;

struct element{
  element (const string& c, const vector<string>& a, int d){
    connector = c;
    args = a;
    depth = d;
  }
  
  string connector;
  vector<string> args;
  int depth = 0;
};

class parser{
  private:
    vector<string> innerParse(const string& input);

  public:
    vector<element> parse(const string& input);
    //vector<element> finalparse(const string& input);

};

#endif

