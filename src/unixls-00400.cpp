#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdio>
#include <iterator>
#include <set>
#include <sstream>
#include <functional>

using namespace std;

bool maxLength(const string& a, const string& b) {
    return a.size() < b.size();
}

void format(const multiset<string> &input, const size_t n) {
    static const string label(60, '-');
    size_t maxLen = max_element(begin(input), end(input), maxLength)->size();
    size_t columnSize = maxLen + 2;
    size_t maxCols = 0, maxRows = 0;
    for (int l = maxLen; l <= 60; l += (2+maxLen), ++maxCols);
    maxRows = n/maxCols;
    if (n % maxCols != 0) ++maxRows;

//    copy(input.begin(), input.end(), ostream_iterator<string>(cout, "\n"));   
//    cout << "log: " << maxRows << ", " << maxCols << ", " << maxLen << ", " << n << endl;
    vector<stringstream> table(maxRows);
    size_t i = 0;
    multiset<string>::const_iterator it = input.cbegin();
    for (i = 0; i < maxRows; ++i, ++it) {
        table[i] << (*it);
    }
    for (size_t c = 0; it != input.cend(); ++it, ++i) {
        if (i == maxRows) { i = 0; c++; }
        if (c != maxCols) {
//            cout << "xxx " << table[i].gcount() << ",,," << table[i].str().size() << endl;
            for (size_t sp = c*(maxLen + 2) - table[i].str().size(); sp > 0; --sp) table[i] << ' ';
        }
        table[i] << *it;
        if (c == maxCols-1) {
            for (size_t sp = maxCols*maxLen + (maxCols-1)*2 - table[i].str().size(); sp > 0; --sp) { table[i] << ' '; }
        }
    }
    
    cout << label << endl;
    for_each(table.begin(), table.end(), [](stringstream &s) { cout << s.str() << endl; });

}


int main() {
    while(!cin.eof()) {
        size_t N = 0;
        multiset<string> input;

        cin >> N;
        if (cin.eof()) break;
        copy_n(std::istream_iterator<string>(cin), N, std::insert_iterator<multiset<string>>(input, input.begin()));
        format(input, N);
    }

}
