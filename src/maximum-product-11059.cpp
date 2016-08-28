#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <functional>
#include <numeric>

using namespace std;

int main()
{
  int64_t N, kase = 0;
  while(!(cin >> N).eof()) {
    vector<int64_t> vec;
    copy_n(istream_iterator<int64_t>(cin), N, back_inserter(vec));
    int64_t best = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        int64_t localbest = 0;
        accumulate(it, vec.end(), int64_t(1), [&localbest](int64_t init, int64_t val) {
                    init *= val;
                    localbest = max(localbest, init);
                    return init;
                   });
        best = max(best, localbest);
    }

    cout << "Case #" << ++kase << ": The maximum product is " << best << ".\n" << std::endl;
  }
  return 0;
}
