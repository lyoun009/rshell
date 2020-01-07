#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unistd.h>
#include <fcntl.h> 
#include "parser.h"
#include "util.h"

using namespace std;

vector<string> parser::innerParse(const string& input){
  vector<string> results;
  
  if (input.empty()){
    return results;
  }
  
  string work = input; // Copy of input string

  // Pattern to chk for quotes and turn them into a chunk together
  regex pattern(" *(?:([^\" ]+)|\"([^\"]+)\").*");

  // Chip each match off the input string until all parts are seperated.
  smatch match;
  while (!work.empty()){
    auto chk = regex_match(work, match, pattern);
    if (!chk){
      break; // no more matches
    }

    // assume there are no matches until we find any
    bool quoteMatch = false;

    // Two possible match positions
    string part;

    if (match[1].matched){
      part = match[1];
    }
    else{
      quoteMatch = true;
      part = match[2];
    }
 
    // add part to output vector
    results.push_back(part);
 
    // erase part from front of work string
    work.erase(0, part.size() + ((quoteMatch) ? 3 : 1));
  }
  
  // return the chunks
  return results;
}


vector<element> parser::parse(const string& parseinput){

  vector<element> results;

  // Tests if any input was given
  if (parseinput.empty()){
    return results;
  }

  string input = parseinput;

  int start = 0;
  int charLen = (int)input.size();
  bool inQuote = false;
  string currentconnect = ";";

  int depth = 0;

  for (int i = 0; i < charLen; ++i){
    // the character we are looking at
    char c = input.at(i);

    // the character one past the current character we are looking at
    char c2 = 0; // This assumes that we are at the very end of the input, otherwise we reset it
    if (i < charLen-1){
      c2 = input.at(i+1); 
    } 

    // Test if we are in quotes, bool assumes no at start
    if (c == '\"'){
      if (inQuote == true){
        inQuote = false;
      }
      else{
        inQuote = true;
      }
    }

    if (inQuote == false){
      
      // checks the depth if we are in () so we know if we need to skip any values
      if (c == '('){
        ++depth;
      }

      //Checks and breaks up based on the known 'connector' characters
      // () break the code so we remove them so the commands can execute normally
      // Start moves to break off a piece and give where the new piece starts 
      if (c == ';' || c2 == 0){
        
        // extra offset if not ;
        int offset = 1;
        if (c == ';'){
          offset = 0;
        }
          
        string s = Util::stripParens(input.substr(start, i-start + offset));
        //cout << s << "\n"; //debugging test
        auto v = innerParse(s);
        element match{currentconnect, v, depth};
        currentconnect = ";";
        results.push_back(match);
        start = i + 1;
        i = start;
      }

      else if (c == '&' && c2 == '&'){
        string s2 = Util::stripParens(input.substr(start, i-start));
        //cout << s << "\n"; //debugging test
        auto v2 = innerParse(s2);
        element match2{currentconnect, v2, depth};
        currentconnect = "&&";
        results.push_back(match2);
        start = i + 2;
        i = start;
      }

      else if (c == '|' && c2 == '|'){
        string s3 = Util::stripParens(input.substr(start, i-start));
        //cout << s << "\n"; //debugging test
        auto v3 = innerParse(s3);
        element match3{currentconnect, v3, depth};
        currentconnect = "||";
        results.push_back(match3);
        start = i + 2;
        i = start;
      }
      // fixes the depth if an ending () is found
      if (c == ')'){
        --depth;
      }
    } // quote chk if
  }

  // returns the pieces in a vector
  return results;
}
