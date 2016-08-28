#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
  vector<string> dict;
  copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(dict));
  sort(dict.begin(), dict.end());
//  copy(dict.cbegin(), dict.cend(), ostream_iterator<string>(cout, "\n")); cout << endl;
  set<string> ans;
  for(vector<string>::const_iterator it = dict.cbegin(); it != dict.cend(); ++it) {
            const string& w = *it;
            if (w.size() > 1) {
              vector<string>::const_iterator niter = it+1;
              for(size_t i = 1; i < w.size(); ++i) {
                const string f = w.substr(0, i);
                const string s = w.substr(i);
                //vector<string>::iterator fiter = lower_bound(dict.begin(), dict.end(), f);
                //vector<string>::iterator siter = lower_bound(dict.begin(), dict.end(), s);
                //cout << w << "=" << f << ' ' << s << endl;

                if ((binary_search(dict.cbegin(), niter, f) || binary_search(niter, dict.cend(), f)) &&
                   (binary_search(dict.cbegin(), niter, s) || binary_search(niter, dict.cend(), s)))
                      ans.insert(w);
              }
            }
          }


  copy(ans.cbegin(), ans.cend(), ostream_iterator<const string>(cout, "\n"));

  return 0;
}
