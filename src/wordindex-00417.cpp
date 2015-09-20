#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

map<string, int> mp;
int idx = 0;

void make_map(const string& s, unsigned n) {
  if (s.size() == n) {
    mp[s] = ++idx;
    //cout << s << " => " << idx << endl; 
    return;
  }

  char last;
  if (s == "") last = 'a';
  else last = s[s.size()-1] + 1;

  for (char c = last; c <= 'z'; ++c) {
    make_map(s+c, n);
  }
}

int main () {
  string str("");
  for (unsigned i = 1; i < 6; ++i) make_map(str, i);

  //str.clear();
  map<string, int>::iterator it, end = mp.end();
  while (cin >> str && !cin.eof()) {
    if ((it = mp.find(str)) != end) cout << it->second  << endl;
    else cout << "0" << endl;
  }

  return 0;
}
