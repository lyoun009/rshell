#include <string>
#include <vector>

using namespace std;

class parser
{
  vector<string> innerParse(const string& input);

public:
  vector<pair<string, vector<string> > > parse(const string& input);

};

