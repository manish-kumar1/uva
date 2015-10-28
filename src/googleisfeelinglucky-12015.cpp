#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

struct Data {
    
    friend istream& operator >> (istream& iss, Data& _d) {
        return iss >> _d.url >> _d.relvScore;
    }

    bool operator > (const Data& _rhs) const {
        return (relvScore > _rhs.relvScore);
    }

    string url;
    int relvScore;

};

int main() {
    int kase;
    cin >> kase;

    for (int k = 1; k <= kase; ++k) {
        vector<Data> input;
        copy_n(istream_iterator<Data>(cin), 10, back_inserter(input));
        stable_sort(input.begin(), input.end(), greater<Data>());

        cout << "Case #" << k << ":" << endl;
        int best = input.begin()->relvScore;
        all_of(input.begin(), input.end(), [&best](const Data& _d) {
            if (_d.relvScore == best) {
                cout << _d.url << endl;
                return true;
            }
            return false;
        });
    }

    return 0;
}
