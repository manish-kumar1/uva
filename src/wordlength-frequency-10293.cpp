#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <cctype>
#include <algorithm>

using namespace std;

bool eow(const char c) {
    return isspace(c) || (c == '.') || (c == '?') || (c == '!') || (c == ',');
}

int main() {

    while (!cin.eof()) { // each case
        istreambuf_iterator<char> it(cin);
        size_t len = 0;
        map<size_t, size_t> kntMap;

        for (; it != istreambuf_iterator<char>() && *it != '#';) {
            if (eow(*it)) {
                ++it;
                if (len > 0) {
                    kntMap[len]++;
                    len = 0;
             //       cout << endl;
                }
            }
            else if (*it == '\'') ++it;
            else if (*it == '-' && (*++it == '\n')) ++it;
            else if (*it != '-') len++, ++it;
            //cout << *it;}
        }

        for_each(kntMap.begin(), kntMap.end(), [](const pair<size_t,size_t>& p) {
            cout << p.first << ' ' << p.second << '\n';
        });
        if (it == istreambuf_iterator<char>()) break;
        else {
            ++it;
            cout << endl;
        }
    }

    return 0;
}
