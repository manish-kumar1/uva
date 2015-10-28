#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
#include <bitset>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>

using namespace std;

template<typename InputIter, typename OutputIter, typename UnaryFunctor>
InputIter copy_till(InputIter first, OutputIter out, UnaryFunctor f) {
    while (f(*first))
        *out++ = *first++;

    return first;
}

void cal(const string& q, const multiset<string>& dict, multiset<string>& sol, int k, int start, int curLen, bitset<8>& mask) {
    if (curLen == k) {
        string query;
        for (size_t i = 0; i < q.size(); ++i)
            if (mask[i]) query += q[i];

        do {
            if (dict.find(query) != dict.cend()) {
                int knt;
                if (sol.count(query) != (knt = dict.count(query))) {
                    for (size_t x = 0; x < knt; ++x)
                        sol.insert(query);
                }
                //cerr << query << endl;
            }
        } while (next_permutation(query.begin(), query.end()));

        return;
    }

    if (start == q.size()) return;

    mask[start] = true;
    cal(q, dict, sol, k, start+1, curLen+1, mask);

    mask[start] = false;
    cal(q, dict, sol, k, start+1, curLen, mask);
}

void calculate(const string& q, const multiset<string>& dict, multiset<string>& sol, int k) {
    bitset<8> mask;
    cal(q, dict, sol, k, 0, 0, mask);
}

int main() {
    multiset<string> dict;
    copy_till(istream_iterator<string>(cin), inserter(dict, dict.begin()), [&dict](const string& _s) {
        return _s != "#";
    });

//    copy(dict.begin(), dict.end(), ostream_iterator<string>(cout, "\n")); cout << endl;

    char c;
    stringstream ss;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    all_of(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), [&](const char c) {
            //cout << "c = " << c << endl;
            if (c == '#') return false;

            if (c == '\n') {
                string query = ss.str();
                multiset<string> sol;
                //cerr << "read = " << query << endl;
                sort(query.begin(), query.end());

                for (size_t k = 1; k <= query.size(); ++k) {
                    calculate(query, dict, sol, k);
                }

                cout << sol.size() << endl;

                ss.str("");
            }
            else if (!isspace(c)) {
                ss << c;
            }

            return true;
    });

    return 0;
}
