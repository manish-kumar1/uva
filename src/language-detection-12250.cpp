#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
    int idx = 1;
    const map<string,string> lmap = {{"HELLO", "ENGLISH"}, {"HOLA", "SPANISH"}, {"HALLO", "GERMAN"}, {"BONJOUR", "FRENCH"}, {"CIAO", "ITALIAN"}, {"ZDRAVSTVUJTE", "RUSSIAN"}};
    for_each(istream_iterator<string>(cin), istream_iterator<string>(), [&](const string& _s) {
        auto it = lmap.find(_s);
        if (it != lmap.cend()) cout << "Case " << idx++ << ": " << it->second << endl;
        else if (_s != "#") cout << "Case " << idx++ << ": " << "UNKNOWN" << endl;
    });

    return 0;
}
