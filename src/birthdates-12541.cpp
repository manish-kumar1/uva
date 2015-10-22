#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <vector>

using namespace std;

class data {
public:
    data(const string& s=string(), int d=0) : _name(s), _d(d) {}

    friend istream& operator >> (istream &iss, data& d) {
        int _m, _y;
        iss >> d._name >> d._d >> _m >> _y;
        d._d += ((_y*12 + _m)*30);
        return iss;
    }
    bool operator < (const data& rhs) {
        return _d < rhs._d;
    }
    const string& name() const { return _name; }
private:
    string _name;
    int _d;

};

int main() {
    int n;
    cin >> n;
    vector<data> d;
    copy_n(istream_iterator<data>(cin), n, back_inserter(d));
    auto p = minmax_element(d.begin(), d.end());
    cout << p.second->name() << '\n' << p.first->name() << endl;
    return 0;
}
