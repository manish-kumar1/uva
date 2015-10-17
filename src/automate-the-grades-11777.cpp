#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int main() {
    int kase;
    cin >> kase;

    for (int k = 1; k <= kase; ++k) {
        vector<int> v;
        char grade;

        copy_n(istream_iterator<int>(cin), 7, back_inserter(v));

        sort(next(v.begin(), 4), v.end(), std::greater<int>());
        v[4] = (v[4]+v[5])/2;

        int total = accumulate(v.begin(), next(v.begin(), 5), 0);

        if (total >= 90) grade = 'A';
        else if (total >= 80) grade = 'B';
        else if (total >= 70) grade = 'C';
        else if (total >= 60) grade = 'D';
        else grade = 'F';
        cout << "Case " << k << ": " << grade << endl;
    }

    return 0;
}
