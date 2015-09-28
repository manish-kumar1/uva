#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>

using namespace std;

bool checkRule11(const string& small, const string& big) {
    int delta = 0;
    // dictonary:dictionary
    string::const_iterator d = small.begin(), q = big.begin();
    for (; d != small.end() && q != big.end();) {
        if (*d != *q) {
            ++q;
            if (++delta >= 2) return false;
        }
        else
            ++q, ++d;
    }
    return delta < 2;    
}

bool checkRule1(const int d, const string& dict, const string& query, set<string>& ans) {
    if (d < 0) {
        if (checkRule11(dict, query)) ans.insert(dict);
    } else {
        if (checkRule11(query, dict)) ans.insert(dict);
    }
}


bool checkRule2(const string& dict, const string& query, set<string>& ans) {
    auto p = mismatch(dict.begin(), dict.end(), query.begin());
    if (p.first == dict.end() && p.second == query.end()) {
        ans.insert(query);
        return true;
    }
    else {
        auto pp = mismatch(next(p.first), dict.end(), next(p.second));
        if (pp.first != dict.end()) return false;
        else {
            ans.insert(dict);
            return true;
        }
    }
}

bool checkRule3(const string& dict, const string& query, set<string>& ans) {
    bool ret = false;
    string q(query);

    if (query.size() > 1) {
        string::iterator i = q.begin(), j = next(q.begin());
        for(; j != q.end(); ++i, ++j) {
            iter_swap(i,j);
            if (dict == q) {
                ret = true;
                ans.insert(q);
                break;
            }
            iter_swap(i,j);
        }
    }
    return ret;
}



void solve(const map<string,int>& dict, const string& query) {
    set<string> candidate;
    if (dict.find(query) != dict.end()) {
        cout << query << " is correct" << endl;
        return;
    }

    for_each(dict.begin(), dict.end(), 
                            [&](const pair<const string, int>& p) {
                                const string& word = p.first;
                                int d = word.size() - query.size();
                                if (d == 0) {
                                    checkRule2(word, query, candidate);
                                    checkRule3(word, query, candidate);
                                } else if (abs(d) == 1) {
                                    checkRule1(d, word, query, candidate);
                                }
                            });

    if (candidate.empty()) {
        cout << query << " is unknown" << endl;
    }
    else {
//        copy(candidate.begin(), candidate.end(), ostream_iterator<string>(cout, ", ")); cout << endl;
        auto ans = min_element(candidate.begin(), candidate.end(), [&](auto &a, auto &b){ return dict.at(a) < dict.at(b);});
        cout << query << " is a misspelling of " << (*ans) << endl;
    }
}

int main() {
    int n, q;
    map<string,int> dict;
    vector<string> queries;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string tmp;
        cin >> tmp;
        dict.insert(make_pair(tmp,i));
    }
    //copy_n(istream_iterator<string>(cin), n, inserter(dict, dict.begin()));
    
    cin >> q;
    copy_n(istream_iterator<string>(cin), q, back_inserter(queries));
    for_each(queries.begin(), queries.end(), [&](const string& query) { solve(dict, query);});
    return 0;
}
