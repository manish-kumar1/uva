#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <set>

using namespace std;

int main(){
  string n;
  while (cin >> n && n != "0") {
    set<string> chains;
    cout << "Original number was " << n << '\n';
    do {
      chains.insert(n);
      string ascen = n;
      sort(ascen.begin(), ascen.end());
      string descn(ascen.rbegin(), ascen.rend());
      int n1, n2;
      sscanf(ascen.data(), "%d", &n1);
      sscanf(descn.data(), "%d", &n2);
      stringstream ss;
      ss << (n2-n1);
      cout << n2 << " - " << n1 << " = " << (n2-n1) << '\n';
      ss >> n;
    } while (chains.find(n) == chains.end());

    cout << "Chain length " << chains.size() << '\n';
    cout << endl;
  }

  return 0;
}
