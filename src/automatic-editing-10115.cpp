#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

template<typename Iter, typename Size, typename UnaryFunc>
Iter for_each_n(Iter it, Size n, UnaryFunc f) {
    if (n > 0) {
        f(*it);
        for (Size i = 1; i < n; ++i) {
            f(*++it);
        }
    }
    return it;
}

template<typename InputIter, typename OutputIter, typename UnaryFunctor>
InputIter copy_till(InputIter first, OutputIter out, UnaryFunctor f) {
    while (f(*first))
        *out++ = *first++;

    return first;
}

int main() {
    int n;

    while (cin >> n >> ws && n != 0) {
        vector<string> frm, to;
        for (int i = 0; i < n; ++i) {
            string t, f;
            getline(cin, t);
            getline(cin, f);
            frm.push_back(t);
            to.push_back(f);
        }

        list<char> q;
        copy_till(istreambuf_iterator<char>(cin), inserter(q, q.begin()), [](const char &_c) { //cout << "c = " << _c << endl;
            return _c != '\n';
        });

        for (int i = 0; i < n; ++i) {
            size_t frmLen = frm[i].length(), toLen = to[i].length();
            for (auto it = search(q.begin(), q.end(), frm[i].begin(), frm[i].end()); it != q.end(); ) {
                auto here = q.erase(it, next(it, frmLen));
                q.insert(here, to[i].begin(), to[i].end());

                it = search(q.begin(), q.end(), frm[i].begin(), frm[i].end());
            }
        }

        copy(q.begin(), q.end(), ostreambuf_iterator<char>(cout)); cout << endl;
    }

    return 0;

}
