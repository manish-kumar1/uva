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
#include <string>
using namespace std;

class ignoreCase_charTraits : public std::char_traits<char> {
  public:
  static void assign (char_type& l, const char_type& r) {
    if (isalpha(r)) l = std::tolower(r);
    else if (isprint(r)) l = ' ';
    else l = r;

  }
  static bool eq(const char_type& l, const char_type& r) {
    return std::tolower(l) == std::tolower(r);
  }
  static bool lt(const char_type& l, const char_type& r) {
    return std::tolower(l) < std::tolower(r);
  }
  static char_type* move(char_type* s1, const char_type* s2, size_t n) {
    char_type* ret = s1;
    while (n > 0) {
      if (isalpha(*s2)) {
        *s1++ = *s2;
      }
      ++s2;
      --n;
    }
    return ret;
  }

  static int compare (const char* l, const char* r, size_t len) {
    for (int i = 0; i < len; ++i) {
      if (lt(l[i], r[i])) return -1;
      if (lt(r[i], l[i])) return +1;
    }
    return 0;
  }
};

int main () {

//  basic_string<char, ignoreCase_charTraits> line;
//  set<basic_string<char, ignoreCase_charTraits> > words;
//
//  while (!cin.eof() && getline(std::basic_istream<char, ignoreCase_charTraits>(cin), line)) {
//    basic_stringstream<char, ignoreCase_charTraits> iss(line);
//    basic_string<char, ignoreCase_charTraits> w;
//    while (iss >> w) words.insert(w);
//  }

  string line;
  set<basic_string<char, ignoreCase_charTraits> > words;

  while (!cin.eof() && getline(cin, line)) {
    if (line.empty()) continue;
    basic_string<char, ignoreCase_charTraits> w (line.begin(), line.end());
//    printf("%s\n", w.c_str());
    basic_stringstream<char, ignoreCase_charTraits> iss (w);
    basic_string<char, ignoreCase_charTraits> ww;

    while (iss >> ww) {
      words.insert(ww);
    }
  }

//  copy (words.begin(), words.end(), ostream_iterator<basic_string<char, ignoreCase_charTraits> >(std::cout, "\n"));
  for (set<basic_string<char, ignoreCase_charTraits> >::const_iterator it = words.begin();
      it != words.end();
      ++it) {
    printf("%s\n", it->c_str());
  }
  return 0;
}
