#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

struct Driver {
    Driver() : _name(), _lapTime() {}
    friend istream& operator >> (istream& iss, Driver& d) {
        string _dummy;
        int _v;
        iss >> d._name >> _dummy >> d._lapTime >> _dummy;
        d._lapTime *= 60*1000;
        iss >> _v >> _dummy;
        d._lapTime += _v*1000;
        iss >> _v >> _dummy;
        d._lapTime += _v;
    }

    bool operator < (const Driver& _other) const {
        if (_lapTime < _other._lapTime) return true;
        else if (_lapTime > _other._lapTime) return false;
        else return lexicographical_compare(_name.begin(), _name.end(), 
                   _other._name.begin(), _other._name.end(), 
                   [](const char a, const char b) { return tolower(a) < tolower(b);});
    }

    string _name;
    int    _lapTime;
};

int main() {
    int n;

    while (!(cin >> n >> ws).eof() && n != 0) {
        vector<Driver> drivers;
        copy_n(istream_iterator<Driver>(cin), n, back_inserter(drivers));
        sort(drivers.begin(), drivers.end());

        int totalRows = lround(static_cast<float>(n)/2.0);
        vector<Driver>::const_iterator it = drivers.begin();
        for (int row = 1; row <= totalRows; ++row) {
            cout << "Row " << row << endl;
            for (int i = 0; it != drivers.end() && i < 2; ++i, ++it) {
                cout << it->_name << endl;
            }
        }

        cout << endl;
    }

    return 0;
}
