#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int num[104] = {0, };

int foo(const int n) {
    if (n >= 101) return n-10;
    else if (n >= 0 && n <= 100 && (num[n] != 0)) return num[n];
    else return num[n] = foo(foo(n+11));
}

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;;
        cout << "f91(" << n << ") = " << foo(n) << endl;
    };
    return 0;
}
