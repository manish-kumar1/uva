import sys

N = int(input())
i = 0
while (i < N):
    num = input()
    steps = 0
    rnum = num[::-1]

    while (num != rnum):
        steps += 1
        num = str(int(num) + int(rnum))
        rnum = num[::-1]

    print(steps, num)
    i += 1
