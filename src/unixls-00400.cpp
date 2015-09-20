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
#if 0
int main() {
  int N;

  while (cin >> N && !cin.eof()) {
    vector<string> v;
    size_t l = numeric_limits<size_t>::min();

    for (int i = 0; i < N; ++i) {
      string str;
      cin >> str;
      v.push_back(str);
  //    s = min(s, str.size());
      l = max(l, str.size());
    }

    sort(v.begin(), v.end());

    for (int ii = 0; ii < 60; ++ii) putchar('-');
    putchar('\n');
    int Cols = 60/(l+2);
    int Rows = v.size()/Cols;
    if (v.size() % Cols != 0) ++Rows;

    //cout << endl << v.size() << ", " << l << ", " << Rows << ", " << Cols << endl;
    for (int r = 0; r < Rows; ++r) {
      string str;
      for (int c = 0; c < Cols; ++c) {
        if (r + c*Rows >= v.size()) break;
        const string& s = v[r + c*Rows];
        str += s;
        int w = l+2;
        if (c == Cols -1) w = l;
        for (int i = s.size(); i < w; ++i) str += ' ';
      }
      if (!str.empty()) cout << str << endl;
    }
  }

  //60 = (maxCols-1)*(s+2) + s; = (s+2)*(maxCols) -2 = 60;
//  int maxCols = 1 + 62/(s+2);
//  int minCols = 1 + 62/(l+2);
//
//  int maxRows = v.size()/minCols, minRows = v.size()/maxCols, i;
//
//  for (i = minRows; i <= maxRows; ++i) {
//    // if ok
//    int r = 0;
//    for (r = 0; r < i; r++) {
//      int len = 0, col = 0;
//      while (len <= 60 && (r + i*col < v.size())) {
//        len += v[i*col+r].size() + 2;
//        col++;
//      }
//      if (col < v.size()/i) break;
//    }
//    if (r == i) break;
//  }
//
//  int R = i;
//  int C = v.size()/R + 1;
//  for (i = 0; i < R; ++i) {
//    string str;
//    for (int j = 0; j*R+i < v.size(); ++j) {
//      str += v[j*R+i];
//      str
//    }
//    cout <<
//  }

}

#endif

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
