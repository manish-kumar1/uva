import sys

chaos = []

h = 0
while (h < 24):
    m = 0
    while(m < 60):
        if (h == 0):
            if (m < 10):
                s = "%d" % (m)
            else:
                s = "%2d" % (m)
        elif (h < 10):
            s = "%d%2d" % (h,m)
        else:
            s = "%02d%02d" % (h, m)

        if (s == s[::-1]): chaos.append(h*60+m)
        m += 1

    h += 1

n = int(input())
i = 0
while(i < n):
    s = input()
    (h,m) = s.split(':')
    v = int(h)*60+int(m)
    itr = 0
    while(itr < len(chaos)):
        if (v < chaos[itr]): break
        itr += 1

    if (itr >= len(chaos)): itr = 0
    ans = chaos[itr]
#    ans = chaos[next(idx for idx,val in enumerate(chaos) if v < val)]
    hrs = int(ans/60)
    print("%02d:%02d" % (hrs, ans-hrs*60))
    i += 1
