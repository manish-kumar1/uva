#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <array>
#include <map>

using namespace std;

int main() {
    int kase;
    vector<int> input;
    map<int, array<int,10>> in;
    cin >> kase;

    copy_n(istream_iterator<int>(cin), kase, back_inserter(input));
    for_each(input.begin(), input.end(), [&in](const int &n) { in.insert(make_pair(n, array<int,10>())); });

    array<int,10> lastArr = in.begin()->second;
    int lastN = 0;
    for_each(in.begin(), in.end(), [&lastN,&lastArr](pair<const int, array<int,10>>& p) {
        auto &curArr = p.second;
        auto &curN   = p.first;

        for (int x = ++lastN; x <= curN; ++x) {
            for (int y = x; y > 0; y /= 10)
                lastArr[y%10]++;
        }

        lastN = curN;
        curArr = lastArr;
     });

    for_each(input.begin(), input.end(), [&in](const int n) {
        auto it = in.find(n);
        copy_n(it->second.begin(), 9, ostream_iterator<int>(cout, " "));
        cout << *(it->second.rbegin()) << endl;
    });

    return 0;
}
