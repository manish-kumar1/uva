#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <cstdio>

using namespace std;

int main(int argc, char*argv[]) {
  int c;
  list<char> text;
  list<char>::iterator it = text.begin();
  while (EOF != (c = getchar())) {
    switch (c) 
    {
      case '[':  it = text.begin(); break;
      case ']':  it = text.end();   break;
      case '\n': {
        text.insert(it, c);
        copy(text.begin(), text.end(), ostream_iterator<char>(cout));
        text.clear();
        break;
      }
      default: text.insert(it, c);
    }
  }
}
