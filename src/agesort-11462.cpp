#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <vector>

using namespace std;

int main() {
    int n;
    vector<int> ages;
    ages.reserve(2000005);
    while (!(cin >> n).eof() && (n != 0)) {
        copy_n(istream_iterator<int>(cin), n, inserter(ages, ages.begin()));
        sort(ages.begin(), ages.end());
        copy_n(ages.begin(), n-1, ostream_iterator<int>(cout, " ")); cout << *ages.rbegin() << endl;
        ages.clear();   // invalidates references, iterators etc. but don't change capacity
    }
    return 0;
}
