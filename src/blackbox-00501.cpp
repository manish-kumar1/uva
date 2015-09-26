#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>

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
    int t;
    cin >> t >> ws;

    for (int c = 1; c <= t; ++c) {
        int m, n;
        multiset<int> box;

        cin >> m >> n;
        vector<int> num(m);

        std::copy_n(std::istream_iterator<int>(cin), m, inserter(num, num.begin()));

        std::vector<int>::const_iterator it = num.begin();
        size_t g = 0;

        box.insert(*it++);
        multiset<int>::iterator sit = box.begin();

        for_each_n(istream_iterator<int>(cin), n,
                [&](const int tot) {
                    for (int sz = box.size(); sz < tot; ++sz) {
                        const int _num = *it++;
                        box.insert(_num);
                        if (_num < (*sit)) --sit;
                    }
//                  multiset<int>::iterator sit = box.begin();
//                  advance(sit, g++);  // this will TLE
                    if (g > 0) cout << *++sit << endl;
                    else 
                        cout << *sit << endl, g++;
                }
        );
        if (c != t) cout << endl;
    }

    return 0;
}
