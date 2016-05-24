import sys
import re

def foo(ch):
    c = ch.lower()
    if (c >= 'a' and c <= 'z'): return True;
    return False

for line in sys.stdin:
    line = line.rstrip()
    if(line == "DONE"): break
    w = list(filter(foo, line))
    s = ''.join(w).lower()
    #print(s)
    if(s == s[::-1]):print("You won’t be eaten!")
    else:print("Uh oh..")
