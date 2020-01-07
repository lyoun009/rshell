#include <string>
#include <vector>

#ifndef _parser_H
#define _parser_H

using namespace std;

class parser
{
  vector<string> innerParse(const string& input);

public:
  vector<pair<string, vector<string>>> parse(const string& input);

};

#endif

