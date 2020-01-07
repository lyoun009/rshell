#include <iostream>
#include <vector>
#include <string>
#include <regex>

#include "parser.h"

using namespace std;

int main(){
  parser p;
  
  string testing = "cmd0 \"arg1 gak\" arg2;cmd1 arg1;";
  auto r = p.parse(testing);

/*
  for (auto element: r){
      cout << "Token: " << element.first << "\n";
      for (auto ele: element.second){
          cout << ele << "\n";
      }
  }

  cout << "====================\n";
*/
  testing = "cmd0 \"arg1 gak\" arg2&& cmd1 arg1;";
  r = p.parse(testing);
  for (auto element: r){
      cout << "Token: " << element.first << "\n";
      for (auto ele: element.second){
          cout << ele << "\n";
      }
  }

  cout << "====================\n";

  testing = "cmd0 \"arg1 gak\" arg2 || cmd1 arg1;";
  r = p.parse(testing);
  for (auto element: r){
      cout << "Token: " << element.first << "\n";
      for (auto ele: element.second){
          cout << ele << "\n";
      }
  }

  cout << "====================\n";

  testing = "cmd0; \"arg1 gak\"; arg2;cmd1 arg1;";
  r = p.parse(testing);
  for (auto element: r){
      cout << "Token: " << element.first << "\n";
      for (auto ele: element.second){
          cout << ele << "\n";
      }
  }

  cout << "====================\n";

  testing = "cmd0 && \"arg1 gak\" && arg2 && cmd1 arg1;";
  r = p.parse(testing);
  for (auto element: r){
      cout << "Token: " << element.first << "\n";
      for (auto ele: element.second){
          cout << ele << "\n";
      }
  }

  cout << "====================\n";

  testing = "cmd0 || \"arg1 gak\" || arg2 || cmd1 arg1;";
  r = p.parse(testing);
  for (auto element: r){
      cout << "Token: " << element.first << "\n";
      for (auto ele: element.second){
          cout << ele << "\n";
      }
  }

  cout << "====================\n";

  return 0;
}
