#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template<typename InputIter, typename Functor>
InputIter apply_till(InputIter first, InputIter last, Functor f) {
    InputIter it = first;
    for (; it != last; ++it) {
        if (!f(*it)) return it;
    }

    return it;
}

int main() {
    int kase;
    cin >> kase;
    while (kase--) {
        vector<int> prices;
        auto it2 = back_inserter(prices);
        for (auto it1 = istream_iterator<int>(cin); *it1 != 0;)
            *it2++ = *it1++;

        sort(prices.begin(), prices.end(), greater<int>());

        int i = 1, total = 0;
        find_first_of(prices.begin(), next(prices.begin()), prices.begin(), prices.end(), [&i, &total](const int dummy, const int _price) {
            total += 2*pow(_price, i++);
            if (total > 5000000) return true;
            else return false;
        });

        if (total > 5000000) cout << "Too expensive" << endl;
        else cout << total << endl;
    }

    return 0;
}
