#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>

using namespace std;
#if 0
struct lessOp {

  bool operator () (const string& lhs, const string& rhs) {
    string a = lhs + rhs, b = rhs + lhs;
    return b < a;
  }
};

int main() {
  int n;
  while (cin >> n && !cin.eof()) {
    if (n == 0) break;
    vector<string> v;
  //  copy_n(istream_iterator<string>(cin), n, back_inserter(v));
//#if 0
    for (int i = 0; i < n; ++i) {
      string s;
      cin >> s;
      v.push_back(s);
    }
//#endif
    sort (v.begin(), v.end(), lessOp());
    string ans = accumulate(v.begin(), v.end(), string(""));
    cout << ans << endl; 
  }

}
#endif
// in c++11
int main() {
  int n;
  while (!(cin >> n).eof() && n != 0) {
    vector<string> v;
    copy_n (istream_iterator<string>(cin), n, back_inserter(v));
    sort (v.begin(), v.end(), [&] (const string& l, const string& r) { return l+r > r+l;});
    cout << accumulate (v.begin(), v.end(), string("")) << endl;
  }
  return 0;
}
