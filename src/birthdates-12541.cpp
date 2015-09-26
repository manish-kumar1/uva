#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <vector>

using namespace std;

class data {
public:
    data(const string& s=string(), int d=0, int m=0, int y=0) : _name(s), _d(d), _m(m), _y(y) {}

    friend istream& operator >> (istream &iss, data& d) {
        iss >> d._name >> d._d >> d._m >> d._y;
        return iss;
    }
    bool operator < (const data& rhs) {
        if (_y < rhs._y) return true;
        else if (_y > rhs._y) return false;
        else if (_m < rhs._m) return true;
        else if (_m > rhs._m) return false;
        else if (_d < rhs._d) return true;
        else if (_d > rhs._d) return false;
        else return true;
    }
    const string& name() const { return _name; }
private:
    string _name;
    int _d, _m, _y;

};

int main() {
    int n;
    cin >> n;
    vector<data> d;
    copy_n(istream_iterator<data>(cin), n, back_inserter(d));
    sort(begin(d), end(d));
    cout << (d.end()-1)->name() << endl << d.begin()->name() << endl;
    return 0;
}
