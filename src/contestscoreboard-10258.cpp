//
// football-10194.cpp
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
//	This software is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this software.  If not, see <http://www.gnu.org/licenses/>.
//
//  Created on: Nov 30, 2013
//      Author: Manish Kumar
//

#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <list>
#include <vector>
#include <bitset>
#include <functional>
#include <utility>
#include <cstdio>
#include <string>
#include <sstream>
#include <cmath>
#include <memory>
#include <limits>

using namespace std;

struct foo {
  int numSolved_;
  int time_;
  int id_;
  bool submitted_;
  vector<pair<bool, int> > problems;

  explicit foo(int id) {
    id_ = id;
    time_ = 0;
    numSolved_ = 0;
    problems.resize(11);
    submitted_ = false;
  }

  bool operator < (const foo& rhs) const {
    if (numSolved_ < rhs.numSolved_) return true;
    else if (numSolved_ > rhs.numSolved_) return false;
    else {
      return time_ < rhs.time_;
    }
  }

  bool operator > (const foo& rhs) const {
//    return !(this->operator < (rhs));
    if (numSolved_ > rhs.numSolved_) return true;
    else if (numSolved_ < rhs.numSolved_) return false;
    else if (time_ < rhs.time_) return true;
    else if (time_ > rhs.time_) return false;
    else return id_ < rhs.id_;
  }

  void operator << (ostream& out) const {
    out << numSolved_ << " " << time_;

  }

  friend ostream& operator << (ostream& out, const foo& f);
};

ostream& operator << (ostream& out, const foo& f) {
      //out << f.numSolved_ << " " << f.time_;
      f.operator <<(out);
      return out;
}


int main () {

  int t;
  cin >> t >> ws;

  while (t--) {
    string line;
    vector<foo> vec;
    vec.reserve(101);

    for (int i = 0; i <= 100; ++i) vec.push_back(foo(i));

    while (!cin.eof() && getline(cin, line) && !line.empty()) {
      stringstream ss(line);
      int team, problem, time;
      char L;
      ss >> team >> problem >> time >> L;

      vec[team].submitted_ = true;

      switch (L) {
        case 'I' : if (!vec[team].problems[problem].first) vec[team].problems[problem].second++; break;
        case 'C' : {
          if (!vec[team].problems[problem].first) {
            vec[team].problems[problem].first = true;
            vec[team].numSolved_ += 1;
            vec[team].time_ += (time + 20*vec[team].problems[problem].second);
          }
        }
        default  :break;
      }
    }

    sort(vec.begin(), vec.end(), greater<foo>());

    for (size_t i = 0; i < 101; ++i) {
      if (vec[i].submitted_) cout << vec[i].id_ << " " << vec[i].numSolved_ << " " << vec[i].time_ << endl;
    }

    if (t) cout << endl;
  }

  return 0;
}

