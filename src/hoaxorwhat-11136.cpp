//
// hoaxorwhat-11136.cpp
// Copyright 2013, 2014 Manish Kumar (manish.iitgcse@gmail.com)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//    * Redistributions of source code must retain the above copyright 
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above 
//      copyright notice, this list of conditions and the following 
//      disclaimer in the documentation and/or other materials provided 
//      with the distribution.
//
//	This software is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this software.  If not, see <http://www.gnu.org/licenses/>.
//
//  Created on: Oct 20, 2013
//      Author: Manish Kumar
//


#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>
#include <functional>

using namespace std;
#if 0
int main () {
  int n;
  while (true) {
    scanf("%d", &n);
    if (n == 0) break;

    multiset<int> bills;
    int k;
    int paid = 0;
    for (int t = 0; t < n; ++t) {
      scanf("%d", &k);
      int b;
      for (int i = 0; i < k; ++i) {
        scanf("%d", &b);
        bills.insert(b);
      }

      while (bills.size() > 1) {
        multiset<int>::iterator it = bills.end();
        --it;

        paid += *(it) - *(bills.begin());
        printf("paid = %d\n", paid);
        bills.erase(it);
        bills.erase(bills.begin());
      }
    }
    printf("%d\n", paid);
  }
  return 0;
}
#endif

int main() {
    int n;
    while ((cin >> n) && (n != 0)) {
        multiset<int> urn;
        long long paid = 0ll;
        int k, lastBill = -1, tot = 0;

        for (int i = 0; i < n; ++i) {
            cin >> k;
            if (k > 0) copy_n(istream_iterator<int>(cin), k, inserter(urn, urn.begin()));
            //  copy(urn.begin(), urn.end(), ostream_iterator<int>(cout, ", ")); cout << endl;
            multiset<int>::const_iterator lb = urn.cend(); --lb;
            multiset<int>::const_iterator sb = urn.cbegin();
                
            paid += (*lb - *sb);
            urn.erase(sb);
            urn.erase(lb);
        }
        cout << paid << endl;
    }
    return 0;
}
