#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <limits>

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
    int n, kase = 1;
    while (cin >> n && n) {
        set<int> num;
        int m;
        copy_n(istream_iterator<int>(cin), n, inserter(num, num.begin()));
        cin >> m;
        cout << "Case " << kase++ << ":" << '\n';
        for_each_n(istream_iterator<int>(cin), m, 
                  [&](const int q) {
                    int best = numeric_limits<int>::max(), tmp, sum, _sum;
                    for(set<int>::const_iterator it = num.begin(); it != num.end(); ++it) {
                        for (set<int>::const_iterator it2 = next(it); it2 != num.end(); ++it2) {
                                tmp = abs((_sum = (*it2 + *it)) - q);
                                if(tmp < best) {
                                    best = tmp, sum = _sum;
                                }
                                //else if ((tmp > localBest) || (tmp > best)) break;
                                //cout << "it1 = " << *it << ",it2 = " << *it2 << ", " << _sum << ", " << best << endl;;
                        }
                    }
                    cout << "Closest sum to " << q << " is " << sum << "." << '\n';
                  }
        );
    }
	cout.flush();
    return 0;
}
