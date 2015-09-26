#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

std::vector<unsigned> mem(1000000, 0u);

unsigned len (unsigned n) {
//    cout << "n: " << n << endl;
    if (mem[n] != 0u) {
        return mem[n];
    }
    else {
        unsigned N = n;
        unsigned  ans = 1;
        while (n != 1u) {
//            cout << n << ", ";
            if ((n & 1u) == 0) n >>= 1, ++ans;
            else {
                n = (3*n + 1);
                n >>= 1;
                ans += 2;
            }
        }
//       cout << endl;
        return mem[N] = ans;
    }
}

int main() {
    int i, j;
    mem[0] = 1;
    mem[1] = 1;
    mem[2] = 2;

    while (!(cin >> i >> j).eof()) {
        unsigned ans = 0;
        cout << i << ' ' << j << ' ';
        if (i > j) std::swap(i, j);
        for (int n = i; n <= j; ++n) {
            unsigned v = len(n);
            //cout << "len(" << n << ") = " << v << endl;
            if (v > ans) ans = v;
        }
        cout << ans << endl;
    }

  return 0;
}
