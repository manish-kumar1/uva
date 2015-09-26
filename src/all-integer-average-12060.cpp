#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <typeinfo>
#include <iomanip>

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

template<typename IntType>
IntType gcd(IntType a, IntType b) {
    IntType tmp;
    while (b != 0) {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

void print(int p, int num, int denom) {
//    cout << p << ',' << num << ',' << denom << endl;
    if (num == 0) {
        if (p < 0) cout << "- " << abs(p) << endl;
        else cout << p << endl;
    } else {
        stringstream pss, numss, denomss;
        numss << abs(num);
        denomss << abs(denom);
        size_t ps = 0;
        if (p < 0) {
            pss << "- " << -p;
            ps = pss.str().size();
        }
        else if (p > 0) {
            pss << p;
            ps = pss.str().size();
        }
        else if (num < 0 || denom < 0) ps = 2;
    
        size_t maxw = ps + max(numss.str().size(), denomss.str().size());

        cout << setw(maxw) << std::right << abs(num) << endl;

        char prev = cout.fill('-');
        if (p < 0) {
            cout << setw(maxw) << left << pss.str();
        } else if (p > 0) {
            cout << setw(maxw) << left << p;
        }
        else if (num < 0 || denom < 0) {
            cout << setw(maxw) << left << "- ";
        }
        else
            cout << setw(maxw) << '-';

        cout << endl;
        cout.fill(prev);
        cout << setw(maxw) << right << abs(denom) << endl;;
    }
}

void format(int avg, int n, const int &kase) {
    int cg = gcd(abs(avg), n);
//    cout << avg << ":" << n << ":" << cg << endl;
    if (cg != n) {
        avg /= cg;
        n /= cg;
    }
    int p = avg/n, numer = avg - p*n;
    cout << "Case " << kase << ":" << endl;
    print(p, numer, n);
}

int main() {
    int n, kase = 0;
    while ((cin >> n >> ws) && (n != 0)) {
        int avg = 0;
        for_each_n(istream_iterator<int>(cin), n, [&](const int &v) { avg += v;});
        format(avg, n, ++kase);
    }
    return 0;
}
