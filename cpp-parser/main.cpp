// reading a text file
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace std;
using namespace boost;

// trim from start
static inline std::string &ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
		return ltrim(rtrim(s));
}

int main (int argc, char * argv[]) {
  if (argc < 2) {
	cout << "Usage: ./exec <file_name>";
	return 1;
  }
  std::stringstream ss;
  vector <string> fields;
  string line;
  size_t idx = 0;
  ifstream myfile (argv[1]);
  string chunk;
  const char * separator = "";

  ss << "[";

  if (myfile.is_open())
  {
		while ( getline (myfile,line) )
		{
			  idx++;
			  if (idx == 1) continue;
			  split(fields, line, is_any_of("\t"), token_compress_on);

			  // Easy find module
			  /*size_t emailPos = 0;
			  bool okLine = false;
			  for (size_t n = 0; n < fields.size(); n++) {
			  	if (fields[n].size() > 0) {
			  		chunk = fields[n];
			  		chunk = trim(chunk);
			  		if (chunk.find("Москва")!= string::npos) okLine = true;
			  		if (chunk.find('@')!= string::npos) emailPos = n;
			  	}
			  }
			  if (okLine) ss << fields[emailPos] << "\n";
			  */
			  for (size_t n = 0; n < fields.size(); n++) {
			  	if (n <= fields.size() && fields[n].size()>0) {
						chunk = fields[n];
						// This will not compile on standards-conforming implementations
						// because of the locale-taking overloads of std::isspace.
						// You'll need to use ::isspace or perform some unreadable
						// machinations with std::bind2nd. Isn't generic code beautiful?

						//chunk.erase(remove_if(chunk.begin(), chunk.end(), ::isspace), chunk.end());
						ss << separator << "\"" << trim(chunk)  << "\"";
						separator = ",";
			   		// ss << trim(chunk) << "\t";
					}
				}
		}

		myfile.close();

	 	ss << "]";
		cout << ss.str();
	} else cout << "Unable to open file";

  return 0;
}
