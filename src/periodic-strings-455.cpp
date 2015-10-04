#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

void solve() {
    string s;
    cin >> s;
    for (int period = 1; period < s.size(); ++period) {
        int p = period;
        for (; p < s.size(); p += period) {
            int m = 0;
            for (; m < period && s[m] == s[p+m]; ++m);
            if (m < period) break;
        }
        if (p >= s.size()) {
            cout << period;
            return;
        }
    }
    cout << s.size();
}

int main() {
    int n;
    cin >> n >> ws;
    for(; n > 1; --n) {
        solve();
        cout << "\n\n";
    }
    solve();
    cout << endl;

    return 0;
}
