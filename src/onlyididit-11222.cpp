#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <typeinfo>
#include <set>
#include <limits>

using namespace std;

int main() {
    int kase;
    cin >> kase;
    for (int k = 1; k <= kase; ++k) {
        vector<set<int>> s(3);
        vector<set<int>> diff(3);
        vector<int> score(6, numeric_limits<int>::max());
        int n, best = 0;

        for (int i = 0; i < 3; ++i) {
            cin >> n;
            if (n > 0) copy_n(istream_iterator<int>(cin), n, inserter(s[i], s[i].begin()));
        }

        for_each(s[0].begin(), s[0].end(), [&](const int p) {
            if (s[1].find(p) == s[1].end() && s[2].find(p) == s[2].end()) diff[0].insert(p);
        });
        for_each(s[1].begin(), s[1].end(), [&](const int p) {
            if (s[2].find(p) == s[2].end() && s[0].find(p) == s[0].end()) diff[1].insert(p);
        });
        for_each(s[2].begin(), s[2].end(), [&](const int p) {
            if (s[1].find(p) == s[1].end() && s[0].find(p) == s[0].end()) diff[2].insert(p);
        });
        
        best = max(diff[0].size(), max(diff[1].size(), diff[2].size()));

        //for_each(score.begin(), score.end(), [](const int x) { cout << x << ":"; cout << endl; });
        //for_each(diff.begin(), diff.end(), [](const set<int>& s) { copy(s.begin(), s.end(), ostream_iterator<int>(cout, ", ")); cout << endl;});

        cout << "Case #" << k << ":" << endl;
        for(int i = 0; i < 3; ++i) {
            if (diff[i].size() == best) {
                cout << (1+i) << " " << best;
                if (best > 0) {
                    cout << " ";
                    copy_n(begin(diff[i]), best-1, ostream_iterator<int>(cout, " "));
                    cout << *diff[i].rbegin();
                }
                cout << endl;
            }
        }
    }
    return 0;
}
