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
