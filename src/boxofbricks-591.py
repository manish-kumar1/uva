import sys

def solve(h, n, tot):
    req = tot/n
    ans = 0
    for x in h:
        if x > req:
            ans += (x-req)

    return ans

i = 1
while (True):
    n = int(input())
    if n == 0:
        break

    h = []
    tot = 0
    line = input()
    for tok in line.split():
        x = int(tok)
        tot += x
        h.append(x)

    print("Set #%d" % i)
    print("The minimum number of moves is %d.\n" %int(solve(h, n, tot)))
    i += 1
