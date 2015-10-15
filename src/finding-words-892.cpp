#include <iostream>
#include <string>
#include <iterator>
#include <type_traits>
#include <sstream>
#include <algorithm>

using namespace std;

void format(string::iterator s, string::iterator e) {
    copy_if(s, e, ostream_iterator<char>(cout, ""), [](const char c) {
        if (isalpha(c) || isspace(c)) return true;
        return false;
    });
    cout << endl; 
}

int main() {
    string line;
    while (!getline(cin, line).eof()) {
        if (line == "#") break;
        if (*line.rbegin() == '-') {
            while(*line.rbegin() == '-') {
                string line2;
                getline(cin, line2);

                string hyphenStr("");

                auto it1 = line.end();
                bool empty = false;
                while ((!isspace(*--it1))) {
                    hyphenStr += *it1;
                    if (it1 == line.begin()) {
                        empty = true;
                        break;
                    }
                }

                reverse(hyphenStr.begin(), hyphenStr.end());

                auto it2 = line2.begin();
                while (it2 != line2.end() && (!isspace(*it2))) hyphenStr += *it2, ++it2;
 
                if (!empty || it1 != line.begin()) format(line.begin(), next(it1));
                else format(line.begin(), it1);

                format(hyphenStr.begin(), hyphenStr.end());
                line.assign(it2, line2.end());
            }
            if (!line.empty()) format(line.begin(), line.end());
        }
        else
            format(line.begin(), line.end());
    }

    return 0;
}
