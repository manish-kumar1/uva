#include <iostream>
#include <iterator>
#include <array>
#include <limits>
#include <cctype>
#include <algorithm>

using namespace std;

int main() {
    while (!cin.eof()) {
        array<int, 256> table = {0, };
        int kase = 0;

        for_each(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), [&](char c) {
            if (c == '\n') {
                vector<pair<int, int>> o;
                int idx = 32;
                for_each(next(table.begin(), 32), next(table.begin(), 129), [&](int freq) {
                    o.push_back(make_pair(idx++, freq));
                });

                sort(o.begin(), o.end(), [](pair<int,int>&a, pair<int,int>&b) {
                    if (a.second < b.second) return true;
                    else if (a.second > b.second) return false;
                    else if (a.first > b.first) return true;
                    else if (a.first < b.first) return false;
                    else return false;
                });

                if (kase++ > 0) cout << endl;

                for_each(o.begin(), o.end(), [](pair<int,int> &p) {
                    if (p.second > 0) cout << p.first << ' ' << p.second << endl;
                });


                fill(next(table.begin(), 32), next(table.begin(), 129), 0);
            }
            else
                ++table[c];
        });

        cin.ignore(numeric_limits<streamsize>::max());
    }

    return 0;
}
