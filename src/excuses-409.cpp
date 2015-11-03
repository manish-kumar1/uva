#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>
#include <cctype>
#include <sstream>

using namespace std;

int main() {
    int kase = 0;
    int K, E;

    while (!(cin >> K >> E >> ws).eof()) {
        set<string> keys;
        string line;


        copy_n(istream_iterator<string>(cin), K, inserter(keys, keys.begin()));
        cin.ignore();

        vector<string> excuses;
        vector<int> scores;
        int best = numeric_limits<int>::min();
        for (int i = 0; i < E; ++i) {
            string line;
            multiset<string> words;
            int tot = 0;

            getline(cin, line);
            excuses.push_back(line);

            stringstream ss;
            transform(line.begin(), line.end(), ostreambuf_iterator<char>(ss), [&](const char _c) {
                if (isalpha(_c)) return tolower(_c);
                else return char_traits<char>::to_int_type(' ');
            });

            for_each(istream_iterator<string>(ss), istream_iterator<string>(), [&](const string& _w) {
                if (keys.find(_w) != keys.end()) ++tot;
            });

            scores.push_back(tot);
            if (tot > best) {
                best = tot;
            }
        }

        cout << "Excuse Set #" << ++kase << endl;

        for (int x = 0; x < E; ++x) {
            if (scores[x] == best) cout << excuses[x] << endl;
        }
        cout << endl;
    }

    return 0;
}
