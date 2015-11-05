#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>

using namespace std;
#if 0

int main() {
    const size_t WSIZE = 16;
    int kase;
    cin >> kase >> ws;
    while(kase--) {
        vector<string> dict;
        array<vector<size_t>, WSIZE> lenMap;
        auto it = back_inserter(dict);
        auto iss = istream_iterator<string>(cin);
        size_t idx = 0;
        while (iss->at(0) != '#') {
            lenMap[iss->size()].push_back(idx++);
            *it++ = *iss++;
        }
        for ( ;iss->at(0) != '#'; ++iss) {
            const string &query = *iss;
            const size_t &qsize = query.size();
            if (qsize < WSIZE) {
                const vector<size_t>& match = lenMap[qsize];
                bool found = false;
                for (auto idx = match.cbegin(); idx != match.cend(); ++idx) {
                    if (query == dict[*idx]) {
                        cout << query << " is correct" << endl;
                        found = true;
                        break;
                    }
                }
                if (found) continue;
            }
            set<string> edited;
            for (char c = 'a'; c <= 'z'; ++c) {
                
            }
            
        copy(dict.begin(), dict.end(), ostream_iterator<string>(cout, "\n"));
    }
}
#endif

int main ()
{
    int kase;
    cin >> kase >> ws;

    for (int k = 0; k < kase; ++k) {
        unordered_map<string, int> dict;
        int idx = 0;

        if (k != 0) cout << endl;

        all_of(istream_iterator<string>(cin), istream_iterator<string>(), [&](const string& _w) {
            if (_w.at(0) == '#') return false;
            else return dict.insert(make_pair(_w, idx++)).second;
        });

        all_of(istream_iterator<string>(cin), istream_iterator<string>(), [&](const string& _q) {
            if (_q.at(0) == '#') return false;
            if (dict.find(_q) != dict.end()) {
                cout << _q << " is correct" << endl;
            }
            else {
                set<string> edits;
                // delete char
                for (int i = 0; i < _q.size(); ++i) {
                    stringstream word;
                    int j = 0;
                    for (j = 0; j < i; ++j)
                        word << _q[j];

                    for (int j = i+1; j < _q.size(); ++j)
                        word << _q[j];

                    const string& nw = word.str();
                    //cout << "deleted:" << nw << endl;
                    if (dict.find(nw) != dict.end()) edits.insert(nw);
                }

                // insert
                for (char c = 'a'; c <= 'z'; ++c) {
                    for (int i = 0; i <= _q.size(); ++i) {
                        stringstream word;
                        int j = 0;
                        for (j = 0; j < _q.size(); ++j) {
                            if (j == i) word << c;
                            word << _q[j];
                        }
                        if (i >= j) word << c;
                        const string& nw = word.str();
                        //cout << "inserted:" << nw << endl;
                        if (dict.find(nw) != dict.end()) edits.insert(nw);
                    }
                    for (int i = 0; i <= _q.size(); ++i) {
                        stringstream word;
                        for (int j = 0; j < _q.size(); ++j) {
                            if (j == i) word << c;
                            else word << _q[j];
                        }
                        const string& nw = word.str();
                        //cout << "modified:" << nw << endl;
                        if (dict.find(nw) != dict.end()) edits.insert(nw);
                    }
                }

                cout << _q << ":";
                if (!edits.empty()) {
                    cout << " ";
                    vector<string> out(edits.begin(), edits.end());
                    sort(out.begin(), out.end(), [&](const string& _l, const string& _r) {
                        return dict.find(_l)->second < dict.find(_r)->second;
                    });
                    copy_n(out.begin(), out.size()-1, ostream_iterator<string>(cout, " ")); cout << *out.rbegin();
                }
                cout << endl;
            }
            return true;
        });
    }

    return 0;
}
