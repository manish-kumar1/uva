#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    while (!(cin >> n >> k).eof()) {
        int total = n;
        if ((n -=k) >= 0) ++total;
        total += n/(k-1);
        cout << total << endl;
    }

    return 0;
}
