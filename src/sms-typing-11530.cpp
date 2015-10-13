#include <iostream>
#include <string>
#include <iterator>
#include <array>
#include <algorithm>

using namespace std;

int main() {
    std::array<size_t, 256> map = {0,};
    for (char c = 'a'; c <= 'z';)
        for (size_t i = 0; i < 3; ++i) {
            map[c] = (i % 3) + 1;
      //      cout << c << " = " << map[c] << endl;
            c++;
        }

    map['s'] = 4;
    map['t'] = 1;
    map['u'] = 2;
    map['v'] = 3;
    map['w'] = 1;
    map['x'] = 2;
    map['y'] = 3;
    map['z'] = 4;
    map[' '] = 1;
    //copy(map.begin(), map.end(), ostream_iterator<size_t>(cout, ",")); cout << endl;

    int t, kase = 1;
    size_t total = 0;
    cin >> t;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for_each(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), [&](const char &c) {
    //if (t > 0) {
        if (char_traits<char>::eq_int_type(c, '\n')) {
            cout << "Case #" << kase++ << ": " << total << endl;
            total = 0;
      //      --t;
        }
        else {
            total += map[c];
        }
    //}
    });

    return 0;

}
