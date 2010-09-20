#include "filetostrings.hpp"
#include <fstream>

std::list<std::string> FileToStrings(std::string filename)
{
  using namespace std;
  ifstream inp;
  inp.open(filename.c_str(),ios::in);
  
  list<string> lines;
  while (!inp.eof())
    {
      string line;
      getline(inp,line);
      if(line.compare("")==0)
	continue;
      lines.push_back(line);
    }
  return lines;
}
