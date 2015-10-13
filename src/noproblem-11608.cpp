#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

template<typename Iter, typename Size, typename UnaryFunc>
Iter for_each_n(Iter it, Size n, UnaryFunc f) {
    if (n > 0) {
        f(*it);
        for (Size i = 1; i < n; ++i) {
            f(*++it);
        }
    }
    return it;
}

int main() {
    int s = -1, kase = 1;
    while (cin >> s && s >= 0) {
        vector<int> p1, p2;
        p1.push_back(0);
        copy_n(istream_iterator<int>(cin), 12, back_inserter(p1));
        auto it = p1.begin();
        cout << "Case " << kase++ << ":" << '\n';
        for_each_n(istream_iterator<int>(cin), 12, [&it, &s](const int n) {
            if (s + *it < n) {
                cout << "No problem. :(\n";
                s += *it;
            } else {
                cout << "No problem! :D\n";
                s = s + *it - n;
            }
            it++;
        });
    }
    return 0;
}
