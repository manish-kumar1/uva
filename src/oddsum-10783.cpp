#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    vector<int> mem(101, 0);
    for (int i = 1, old = 0; i <= 100; ++i) {
        if (i % 2 == 1)
            old = (mem[i] = old + i);
        else
            mem[i] = old;

    //    cout << "mem[" << i << "] = " << mem[i] << endl;
    }

    int t;
    cin >> t;

    for (int i = 1; i <= t; ++i) {
        int a, b;
        cin >> a >> b;
        if (a == 0) a = 1;
        
        cout << "Case " << i << ": " << mem[b]-mem[a-1] << endl;
    }

    return 0;
}
