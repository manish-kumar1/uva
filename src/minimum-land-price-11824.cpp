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

template<typename InputIter, typename OutputIter, typename UnaryFunctor>
InputIter copy_till(InputIter first, OutputIter out, UnaryFunctor f) {
    while (f(*first))
        *out++ = *first++;

    return first;
}

int main() {
    int kase;
    cin >> kase;
    while (kase--) {
        vector<int> prices;

        copy_till(istream_iterator<int>(cin), back_inserter(prices), [](const int _n) { return _n != 0; });
        sort(prices.begin(), prices.end(), greater<int>());

        int i = 1, total = 0;
        if (any_of(prices.begin(), prices.end(), [&i, &total](const int _price) {
            total += 2*pow(_price, i++);
            return (total > 5000000) ? true : false;}))
        {
            cout << "Too expensive" << endl;
        } else {
            cout << total << endl;
        }
    }

    return 0;
}
