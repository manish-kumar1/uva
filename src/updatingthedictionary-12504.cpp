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

template<typename iIter, typename OSS>
void print(const char prefix, iIter s, iIter e,  OSS& o, const char postfix='\n') {
    o << prefix;
    copy(s, --e, ostream_iterator<string>(o, ","));
    o << (*e) << '\n';
}

bool print(const char prefix, const set<string>& s) {
    if (s.empty()) return false;
    print(prefix, begin(s), end(s), cout);
    return true;
}

template<typename Iter, typename Oter, typename Func>
void mytransform(Iter s, Iter e, Oter o, Func f) {
    const typename Iter::traits_type::int_type newLine = Iter::traits_type::to_int_type('\n');
    for (;s != e; ++o, ++s) {
        if((Iter::traits_type::eq_int_type(*s, newLine))) {
            ++s;
            break;
        }
        *o = f(*s);
    }
}

int main() {
  int n;
  cin >> n >> ws;

  while (n--) {
    map<string, string> mpo, mpn;
    stringstream oss, nss;

    // istreambuf_iterator are much more faster than istream_iterator because of no sentry object
    mytransform(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), ostreambuf_iterator<char>(oss), foo());
    mytransform(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), ostreambuf_iterator<char>(nss), foo());

    string k, v;
    while (oss >> k >> v) {
      mpo.insert(make_pair(k,v));
    }

    set<string> newKeys, removedKeys, modifiedKeys;
    
    while (nss >> k >> v) {
        mpn.insert(make_pair(k,v));

        map<string,string>::iterator it = mpo.find(k);
        if (it == mpo.end()) newKeys.insert(k);
        else if (it->second.compare(v)) modifiedKeys.insert(k);
    }

    for_each(begin(mpo), end(mpo), 
            [&](const pair<const string, string> &kv) {
                if (mpn.find(kv.first) == mpn.cend()) removedKeys.insert(kv.first);
            }
    );


    bool changed = false;
    changed |= print('+', newKeys);
    changed |= print('-', removedKeys);
    changed |= print('*', modifiedKeys);

    if (!changed) cout << "No changes\n";
    cout << endl;
  }
}
