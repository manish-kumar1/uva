import sys

t = int(input())
i = 0
n = 0
while (i < t):
    n = int(input())
    n = int(abs(((((n*63)+7492 )*5)-498)/10))
    print(n%10)
    i += 1
