import sys

for line in sys.stdin:
    palins = set()
    line = line.rstrip()
    length = len(line)
    for i in range(length):
        for j in range(i, length):
            l = line[i:j+1]
            if (l == l[::-1]): palins.add(l)

    print("The string '%s' contains %d palindromes." % (line, len(palins)))
