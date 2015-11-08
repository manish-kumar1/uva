#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <string>

using namespace std;

int main() {

    int N;
    cin >> N >> ws;

    for (int i = 0; i < N; ++i) {
        int M;
        vector<int> a;

        cin >> M;

        a.reserve(M);

        if (i != 0) cout << endl;

        for (int j = 0; j < M; ++j) {
            int d1, d2;
            cin >> d1 >> d2;
            a.push_back(d1+d2);
        }

        bool _carry = false;
        for_each(a.rbegin(), a.rend(), [&_carry](int &_d) {
                if (_carry) ++_d;
                if (_d < 10) {
                    _carry = false;  //traits_type::digit_type(0);
                } else {
                    _carry = true; //traits_type::digit_type(1);
                    _d %= 10;
                }
        });

        if (_carry) cout << "1";
        copy(a.begin(), a.end(), ostream_iterator<int>(cout, "")); cout << endl;
    }
    return 0;
}
