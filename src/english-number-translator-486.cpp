#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <stack>
#include <iterator>

using namespace std;

int main() {
    map<const string,int> mp {{"negative",-1}, {"zero",0}, {"one",1}, {"two",2}, {"three",3}, {"four",4}, {"five",5}, {"six",6},
    {"seven",7}, {"eight",8}, {"nine",9}, {"ten",10}, {"eleven",11}, {"twelve",12}, {"thirteen",13}, {"fourteen",14}, {"fifteen",15},
    {"sixteen",16}, {"seventeen",17}, {"eighteen",18}, {"nineteen",19}, {"twenty",20}, {"thirty",30}, {"forty",40}, {"fifty",50}, {"sixty",60},
    {"seventy",70}, {"eighty",80}, {"ninety",90}, {"hundred",100}, {"thousand",1000}, {"million",1000000}};

    string line;
    while (!getline(cin, line).eof()) {
        string w;
        istringstream iss(line);
        int ans = 0, last = 0, hundred = 0, thousand = 0, million = 0;
        if (iss.peek() == 'n') {
            iss.get();
            if (iss.peek() == 'e') {
                iss.unget();
                cout << '-';
                string dummy;
                iss >> dummy;
            }
            iss.unget();
        }
        for_each(istream_iterator<string>(iss), istream_iterator<string>(), [&](const string& w) {
            int n = mp[w];
            switch(n) {
                case 100:
                    last *= 100;
                    break;
                case 1000:
                    thousand = last*1000;
                    last = 0;
                    break;
                case 1000000:
                    million = last*1000000;
                    last = 0;
                    break;
                default:
                    last += n;
            }
        });

        cout << (million + thousand + last) << endl;
    }

    return 0;
}
