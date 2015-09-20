#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <set>
#include <iterator>
#include <sstream>

using namespace std;

struct foo {
  char operator () (const char& c) {
    if (c == ',' || c == ':' || c == '{' || c == '}') return ' ';
    else return c;
  }
};

void print(const set<string>& st) {
  size_t sz = st.size() - 1;
  set<string>::const_iterator it = st.begin();
  while (sz-- > 0) {
    cout << *it++ << ',';
  }
  cout << *it;
}

int main() {
  int n;
  cin >> n >> ws;

  while (n--) {
    string old, nw;
    map<string, string> mpo, mpn;

    getline(cin, old);
    getline(cin, nw);

    transform(old.begin(), old.end(), old.begin(), foo());    
    transform(nw.begin(), nw.end(), nw.begin(), foo());    
    
    stringstream oss(old), nss(nw);
    string k, v;
    while (oss >> k) {
      oss >> v;
      mpo[k] = v;
    }

    set<string> newKeys, removedKeys, modifiedKeys;
    
    while (nss >> k) {
      nss >> v;
      mpn[k] = v;
      map<string,string>::iterator it = mpo.find(k);
      if (it == mpo.end()) newKeys.insert(k);
      else if (it->second.compare(v)) modifiedKeys.insert(k);
    }
   
    for (map<string,string>::iterator it = mpo.begin(); it != mpo.end(); ++it) {
      map<string,string>::iterator jt = mpn.find(it->first);
      if (jt == mpn.end()) removedKeys.insert(it->first);
    }
    bool noChange = true;
    if (!newKeys.empty()) {
      noChange = false; 
      cout << '+'; //copy(newKeys.begin(), newKeys.end()-1, ostream_iterator<string>(cout, ",")); cout << *(newKeys.end()-1) << endl;
      print(newKeys);
      cout << endl;
    }
    if (!removedKeys.empty()) {
      noChange = false; 
      cout << '-'; //copy(removedKeys.begin(), removedKeys.end()-1, ostream_iterator<string>(cout, ",")); cout << *(removedKeys.end()-1) << endl; 
      print(removedKeys);
      cout << endl;
    }
    if (!modifiedKeys.empty()) {
      noChange = false; 
      cout << '*'; //copy(modifiedKeys.begin(), modifiedKeys.end(), ostream_iterator<string>(cout, ",")); cout << *(modifiedKeys.end()-1) << endl;
      print(modifiedKeys);
      cout << endl;
    }
    if (noChange) cout << "No changes\n";
    cout << endl;
  }
}
