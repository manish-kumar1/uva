import sys

def factorial(n):
    if n == 0 or n == 1: return 1
    ret = 1
    for x in range(1, n+1):
        ret *= x

    return ret

for line in sys.stdin:
    n = int(line)
    print("%d!" % (n))
    print(factorial(n))

