//
// andyfirstdictionary-10815.cpp
// Copyright 2013, 2014 Manish Kumar (manish.iitgcse@gmail.com)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//    * Redistributions of source code must retain the above copyright 
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above 
//      copyright notice, this list of conditions and the following 
//      disclaimer in the documentation and/or other materials provided 
//      with the distribution.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this software.  If not, see <http://www.gnu.org/licenses/>.
//
//  Created on: Oct 20, 2013
//      Author: Manish Kumar
//

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

