#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <vector>
#include <functional>
#include <utility>
#include <cstdio>
#include <string>
#include <sstream>
#include <cmath>
#include <istream>
#include <ostream>
#include <cctype>

using namespace std;

class ignoreCase_charTraits : public std::char_traits<char> {
  public:
  static void assign (char_type& l, const char_type& r) {
    if (isalpha(r)) l = std::tolower(r);
    else if (r == '-') l = '-';
    else if (isprint(r)) l = ' ';
    else l = r;

  }
};

int main () {
  string oneLine, line;
  set<basic_string<char, ignoreCase_charTraits> > words;
  basic_string<char, ignoreCase_charTraits> w;

  while (!cin.eof() && getline(cin, oneLine)) {
    if (oneLine.empty()) continue;
    do {
      if (oneLine.empty()) break;
      if (oneLine.at(oneLine.length()-1) == '-') {
        //copy(oneLine.begin(), oneLine.end()-1, back_inserter(line));
        copy(oneLine.begin(), oneLine.end()-1, back_inserter(w));
      } else {
        copy(oneLine.begin(), oneLine.end(), back_inserter(w));
        break;
      }
    } while (!cin.eof() && getline(cin, oneLine));


//    printf("%s\n", w.c_str());
    basic_stringstream<char, ignoreCase_charTraits> iss (w);
    basic_string<char, ignoreCase_charTraits> ww;

    while (iss >> ww) {
      words.insert(ww);
    }
    w.clear();
  }

  for (set<basic_string<char, ignoreCase_charTraits> >::const_iterator it = words.begin();
      it != words.end();
      ++it) {
    printf("%s\n", it->c_str());
  }
  return 0;
}

