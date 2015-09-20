#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <limits>

using namespace std;

int main() {
  string s;
  while (cin >> s && !cin.eof()) {
    string username = s, ans;
    for (int i = 0; i < 10; ++i) prev_permutation(s.begin(), s.end());

    int m = numeric_limits<int>::min();
    for (int i = 0; i < 21; ++i) {
      //cout << s << endl;
      int d = numeric_limits<int>::max();
      for (int i = 1; i < s.size(); ++i) {
        int distance = ::abs(static_cast<int>(s[i-1] - s[i]));
        if (distance < d) d = distance;
      //  cout << s[i-1] << " - " << s[i] << " = " << distance << endl;
      }
      if (d > m) {
        m = d;
        ans = s;
      }
      next_permutation(s.begin(), s.end());
    }

    cout << ans << m << endl;
  }
}
