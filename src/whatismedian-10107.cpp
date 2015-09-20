#include <cstdio>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

int v[10004];

int main() {

  for (int i = 0; scanf("%d", &v[i]) != EOF; ++i) {
    sort(v, v+i+1);
    //cout << "===> "; copy(v, v+i+1, ostream_iterator<int>(cout, ", ")); cout << endl;
    if ((1+i)%2 == 1) printf("%d\n", v[(i)/2]);
    else printf("%d\n", (v[i/2] + v[(i+1)/2])/2);
  }
}
