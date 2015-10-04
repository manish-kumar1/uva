#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>

using namespace std;

template<typename Iter1, typename Iter2, typename OutIter, typename BinaryFun>
OutIter sum(Iter1 first1, Iter1 last1, Iter2 first2, OutIter out, BinaryFun f) {
    while (first1 != last1) {
        *out++ = f(*first1, *first2);
        ++first1;
        ++first2;
    }

    return out;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string n1, n2;
        vector<int> ans;
        auto ansIter = inserter(ans, ans.begin());
        int carry = 0;
        cin >> n1 >> n2;
        size_t n1s = n1.size(), n2s = n2.size();
        auto foo = [&](const int a, const int b) {
                                        int sum = a + b - 2*'0' + carry;
                                        carry = sum >= 10 ? 1 : 0;
                                        return sum % 10;
                                    };
        
        if (n1s > n2s) {
            ansIter = sum(n2.begin(), n2.end(), n1.begin(), ansIter, foo);
            for (auto it = next(n1.begin(), n2s); it != n1.end(); ++ansIter, ++it) *ansIter = foo(*it, '0');
            if (carry) *ansIter = carry;
        }
        else {
            ansIter = sum(n1.begin(), n1.end(), n2.begin(), ansIter, foo);
            for (auto it = next(n2.begin(), n1s); it != n2.end(); ++ansIter, ++it) *ansIter = foo(*it, '0');
            if (carry) *ansIter = carry;
        }
        auto it = ans.begin();
        for (; it != ans.end() && (*it == 0); ++it);
        if (it != ans.end()) copy(it, ans.end(), ostream_iterator<int>(cout, ""));
        else cout << 0;
        cout << endl;
    }
    return 0;
}
