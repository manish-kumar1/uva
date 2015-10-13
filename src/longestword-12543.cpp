#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <cctype>
#include <algorithm>
#include <limits>
#include <sstream>

using namespace std;

inline bool eow(const char c) {
    return isspace(c); 
}

#if 0
class myTraits : public std::char_traits<char> {
  public:
  static void assign (char_type& l, const char_type& r) {
    if (isalpha(r)) l = std::tolower(r);
    else if (r == '-') l = r;
    else if (isprint(r)) l = ' ';
    else l = r;
  }
};

int main() {
    size_t maxSize = numeric_limits<size_t>::min();
    basic_string<char,myTraits> ans;
    for_each(istream_iterator<string>(cin), istream_iterator<string>(), [&](const string &w) {
        basic_string<char,myTraits> tmp(w.begin(), w.end()), t;
        basic_istringstream<char,myTraits> iss(tmp);
        iss >> t;
        if (t.size() > maxSize) {
			if (w != "E-N-D") {
	            maxSize = t.size();
    	        ans = t;
			}
        }
    });
    cout << ans.c_str() << endl;
    return 0;
}
#endif

int main() {
    string ans;
    size_t maxSize = numeric_limits<size_t>::min();
    ostringstream ss;

    for_each(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), [&](const char c) {
        if (isalpha(c)) ss.put(std::tolower(c));
        else if (c == '-') ss.put(c);
        else if (isspace(c)) {
            const string& t = ss.str();
            if (t.size() > maxSize) {
                if (t != "E-N-D") {
                    maxSize = t.size();
                    ans = t;
                }
            }
            ss.seekp(0);
        }
    });

    cout << ans << endl;

    return 0;
}

