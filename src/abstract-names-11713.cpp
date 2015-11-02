#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int n;
    cin >> n;
    const string vowels("aeiou");
    for (int i = 0; i < n; ++i) {
        string s1, s2;
        cin >> s1 >> s2;
        if (s1.length() != s2.length()) cout << "No" << endl;
        else if (equal(s1.begin(), s1.end(), s2.begin(), [&vowels](const char& _c1, const char& _c2) {
                    if (_c2 != _c1) {
                        if (find(vowels.begin(), vowels.end(), _c1) != vowels.end()) return true;
                        else return false;
                    }
                    return true;
                })) 
        {
            cout << "Yes" << endl;
        }
        else
            cout << "No" << endl;
    }

    return 0;
}
