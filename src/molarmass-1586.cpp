#include <iostream>
#include <string>
#include <limits>
#include <regex>
#include <algorithm>
#include <sstream>
#include <cstdio>

using namespace std;

int main() {
    int n, d;
    char c;
    string line;
    cin >> n >> ws;

    while (n--) {
        getline(cin, line);
        regex reg("([CHNO][\\d]*)");
        auto wb = sregex_iterator(line.begin(), line.end(), reg);
        auto we = sregex_iterator();
        //cout << line << " = ";
        float ans = 0.f;
        for_each(wb, we, [&](const smatch &match) {
            d = 1;
            sscanf(match.str().c_str(), "%c%d", &c, &d);
            switch(c) {
            case 'N': ans += 14.01f*d; break;
            case 'C': ans += 12.01f*d; break;
            case 'O': ans += 16.00f*d; break;
            case 'H': ans += 1.008f*d; break;
            }
        });
        printf("%.3f\n", ans);
    }

}
