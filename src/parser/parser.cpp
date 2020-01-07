#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "parser.h"

using namespace std;

vector<string> parser::innerParse(const string& input)
{
  vector<string> results;
  
  if (input.empty()){
    return results;
  }
  
  string work = input;// Copy of input string

  // Pattern
  regex pattern(" *(?:([^\" ]+)|(\"[^\"]+\")).*");

  // Chip each match off the input string until all parts are seperated.
  smatch match;
  while (!work.empty())
  {
    auto chk = regex_match(work, match, pattern);
    if (!chk)
      break; // no more matches
  
    // Two possible match positions
    string part; 
    if (match[1].matched)
      part = match[1];
    else
      part = match[2];
 
    // add part to output vector
    results.push_back(part);
 
    // erase part from front of work string
    work.erase(0, part.size()+1);
  }
  
  return results;
}


vector<pair<string, vector<string> > > parser::parse(const string& input){

  vector<pair<string, vector<string> > > results;

  if (input.empty()){
    return results;
  }

  int start = 0;
  int charLen = (int)input.size();

  for (int i = 0; i < charLen; ++i){
    char c = input.at(i);
    char c2 = (i < charLen-1) ? input.at(i+1) : 0;

    if (c == ';'){
      string s = input.substr(start, i-start);
      //cout << s << "\n"; //debugging test
      auto v = innerParse(s);
      pair<string, vector<string> > match = {";", v};
      results.push_back(match);
      start = i + 1;
      i = start;
    }
    else if (c == '&' && c2 == '&'){
      string s2 = input.substr(start, i-start-1);
      //cout << s << "\n"; //debugging test
      auto v2 = innerParse(s2);
      pair<string, vector<string> > match2 = {"&&", v2};
      results.push_back(match2);
      start = i + 2;
      i = start;
    }
    else if (c == '|' && c2 == '|'){
      string s3 = input.substr(start, i-start-1);
      //cout << s << "\n"; //debugging test
      auto v3 = innerParse(s3);
      pair<string, vector<string> > match3 = {"||", v3};
      results.push_back(match3);
      start = i + 2;
      i = start;
    }
  }

  return results;
}

