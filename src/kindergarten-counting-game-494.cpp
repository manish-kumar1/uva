#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <type_traits>
#include <algorithm>
#include <iterator>

using namespace std;


class my_traits : public std::char_traits<char> {
public:
    static void assign(char_type& l, const char_type& r) {
        if (isalpha(r)) l = r;
        else l = ' ';
    }
};

ostream& operator << (ostream& os, const basic_string<char,my_traits>& s) {
    return os.write(s.data(), s.size());
}

#if 0
istream& operator >> (istream& is, basic_string<char,my_traits>& s) {
    string tmp;
    is >> tmp;
    s.assign(tmp.begin(), tmp.end());
    return is;
}

int main() {
    size_t knt = 0;

    for (char c = cin.rdbuf()->sgetc(); ; c = cin.rdbuf()->snextc()) {
        if (c == '\n') {
            cout << knt << endl;
            knt = 0;
        }
        else if (char_traits<char>::eq_int_type(c, char_traits<char>::eof())) {
        //    cout << knt << endl;
            break;
        }
        else if (isspace(c)) {
           
        }
        else if (isalpha(c)) {
//            cout << c;
            ++knt;
            while (!char_traits<char>::eq_int_type(c, char_traits<char>::eof())) {
//                c = cin.rdbuf()->peek();
                if (isspace(c) || c == '\n') {
//                    cout << '-';
                    cin.rdbuf()->sungetc();
                    break;
                }
                else {
                    c = cin.rdbuf()->snextc(); 
//                    cout << (c == ' '? '_' : c); 
                }
            }

        }
       //cout << "-" << c;
    }
    return 0;
}
#endif

typedef basic_string<char,my_traits> String;

istream& getline(istream& is, String& s) {
    string tmp;
    getline(is, tmp);
    s.clear();
    s.assign(tmp.begin(), tmp.end());
    return is;
}

int main() {
    String line;

    while (!cin.eof() && getline(cin, line)) {
        basic_istringstream<char,my_traits> iss(line);
        cout << distance(istream_iterator<String,char,my_traits>(iss), istream_iterator<String,char,my_traits>()) << endl;
    }
    
    return 0;
}
