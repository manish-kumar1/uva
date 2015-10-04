#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;


int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        multiset<int> s1, s2, common;
        cin >> n >> m;
        copy_n(istream_iterator<int>(cin), n, inserter(s1, s1.begin()));
        copy_n(istream_iterator<int>(cin), m, inserter(s2, s2.begin()));

        set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(common, common.begin()));
        cout << (s1.size() - 2*common.size() + s2.size()) << endl;
    }
    return 0;
}
