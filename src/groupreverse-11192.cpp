#include <iostream>
#include <string>
#include <iterator>
#include <type_traits>
#include <algorithm>

using namespace std;

#if 0
int main() {
    int g;
    while(cin >> g >> ws && (g != 0)) {
        int _g = 0;
        const auto newLineChar = istreambuf_iterator<char>::traits_type::to_int_type('\n');
        string r(104, '-');
        auto outIter = next(r.begin(), g);
        for(auto it = istreambuf_iterator<char>(cin); *it != newLineChar;) {
            *--outIter = *it++;
            if ((++_g) % g == 0) outIter = next(outIter, 2*g);
        }

        copy(r.begin(), next(outIter, -g), ostream_iterator<char>(cout, ""));
        cout << endl;;
    }
    return 0;
}
#endif

int main() {
    int g;
    while (cin >> g >> ws && (g != 0)) {
        string s;
        cin >> s;
        const size_t gs = s.size() / g;
        for (string::iterator it = s.begin(), it2 = next(it, gs); it != s.end(); it = next(it,gs), it2 = next(it, gs)) 
            reverse_copy(it, it2, ostream_iterator<char>(cout, ""));

        cout << endl;
    }
    return 0;
}
