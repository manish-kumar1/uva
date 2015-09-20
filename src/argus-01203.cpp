//
// argus-01203.cpp
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
//  Created on: Oct 21, 2013
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
#include <queue>

using namespace std;

struct foo {
  //const int qnum_;
  int qnum_;
  int period_;
  int ts_;

  explicit foo(const int q, int p) : qnum_(q), period_(p) {
    ts_ = p;
  }
  foo (const foo& f) : qnum_(f.qnum_) {
    period_ = f.period_;
    ts_ = f.ts_;
  }
  const foo& operator = (const foo& rhs) {
    if (this != &rhs) {
      qnum_ = rhs.qnum_;
      period_ = rhs.period_;
      ts_ = rhs.ts_;
    }
    return *this;
  }
  foo& operator ++ () {
    ts_ += period_;
    return *this;
  }
  bool operator < (const foo& rhs) const {
    if (ts_ == rhs.ts_) return qnum_ > rhs.qnum_;
    else return ts_ > rhs.ts_;
//    return !operator > (rhs);
  }
  bool operator > (const foo& rhs) const {
    if (ts_ == rhs.ts_) return qnum_ < rhs.qnum_;
    else return ts_ < rhs.ts_;
  }
//  bool operator () (const foo& lhs, const foo& rhs) const {
//    return lhs < rhs;
//  }
};

ostream& operator << (ostream& os, const foo& f) {
  //os << "(" << f.qnum_ << ", " << f.period_ << ", " << f.ts_ << ")";
  os << f.qnum_;
  return os;
}

int main () {

  priority_queue<int, vector<int>, greater<int> > pii;
  for (int i = 0; i < 10; ++i) pii.push(i);
  while (!pii.empty()) {
    cout << pii.top() << endl;
    pii.pop();
  }
  string cmd;
  priority_queue<foo> pq;
  int k;
  while (true) {
    cin >> cmd;
    if (cmd == "#") {
      cin >> k;
      break;
    } else {
      int q, t;
      cin >> q >> t;
      pq.push(foo(q,t));
      continue;
    }
  }

  for (int i = 0; i < k; ++i) {
    foo f = pq.top();
    cout << f << endl;
    pq.pop();
    ++f;
    pq.push(f);
  }

  return 0;
}
