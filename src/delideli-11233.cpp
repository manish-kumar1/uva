#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    int L, N;
    map<string, string> mp;
    const string vowels("aeiou");
    cin >> L >> N;
    for (int i = 0; i < L; ++i) {
        string s, p;
        cin >> s >> p;
        mp.insert(make_pair(s,p));
    }

    transform(istream_iterator<string>(cin), istream_iterator<string>(), 
             ostream_iterator<string>(cout, "\n"), 
             [&](const string& _s) {
                auto it = mp.find(_s);
                if (it != mp.end())
                    return it->second;

                const size_t _slen = _s.length();
                const string sub = _s.substr((_slen >= 2 ? (_slen-2) : 0), 2);
                if (sub.length() == 2) {
                    if (sub[1] == 'y' && (find(vowels.begin(), vowels.end(), sub[0]) == vowels.end())) {
                        return _s.substr(0, _slen-1).append("ies", 3);
                    }
                    else if (sub == "ch" || sub == "sh" || sub == "es") return _s.substr(0, _slen).append("es", 2);
                }

                const char _c = _s.back();
                if (_c == 'o' || _c == 's' || _c == 'x') return _s.substr(0, _slen).append("es", 2);
                return _s.substr(0, _slen).append(1, 's');
            });

    return 0;
}
