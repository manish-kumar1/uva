#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

class LoveCalculator {
public:
  friend istream& operator >> (istream& iss, LoveCalculator& lc) {
    getline(iss, lc.a);
    getline(iss, lc.b);
    return iss;
  }

  friend ostream& operator << (ostream& oss, const LoveCalculator& rhs) {
    return oss << rhs.Solve();
  }

  double Solve() const {
    int score_a = Score(a), score_b = Score(b);
    if (score_a < score_b) return (score_a*100.00f)/score_b;
    else return (score_b*100.00f)/score_a;
  }


private:
  int Score(const string& str) const {
      int score = 0;
      for(auto c : str) {
        char _c = tolower(c);
        if (isalpha(_c)) score += (_c - 'a' + 1);
      }

      while (score >= 10) {
        int new_score = 0;
        while (score > 0) {
          new_score += score % 10;
          score /= 10;
        }
        score = new_score;
      }

      return score;
  }

  string a, b;
};

int main() {
  LoveCalculator lc;
  while (!(cin >> lc).eof()) {
    printf("%.2f %\n", lc.Solve());
  }

  return 0;
}
