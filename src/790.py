import sys

class Team:
    def __init__(self, nr):
        self.number = nr
        self.sub = {}
        self.totalTime = 0
        self.totalSolved = 0

    def rank(self):
        for p in self.sub:
            wrong = 0
            subs = self.sub[p]
            for s in sorted(subs):
                if not s[1]:
                    wrong += 1
                else:
                    self.totalTime += wrong*20 + s[0]
                    self.totalSolved += 1
                    #print(self.number, p, self.totalSolved, self.totalTime)
                    break


cases = int(input())
i = 0
fp = sys.stdin
next(fp)

while (i < cases):
    teams = {}
    for line in fp:
        if len(line) == 1:
            break

        (t, p, tm, y) = line.split()
        team = int(t)
        hm = tm.split(':')
        tm = int(hm[0])*60+int(hm[1])
        if (y == 'Y'):
            y = True
        else:
            y = False

        if team not in teams:
            teams[team] = Team(team)

        cur = teams[team]
    #    print(team, tm, y)
        if p in cur.sub:
            cur.sub[p].append((tm, y))
        else:
            cur.sub[p] = [(tm, y)]

    board = []
    for team in teams:
        t = teams[team]
        t.rank()
        board.append((t.totalSolved, -1*t.totalTime, -1*t.number))

    board = sorted(board, reverse=True)
    print("RANK TEAM PRO/SOLVED TIME")
    rank = 0
    lastscore = -1
    lasttime = -1
    samerank = 0
    for score in board:
        if (lastscore < 0 or (lastscore != score[0] or lasttime != score[1])):
            rank += 1
            rank += samerank
            samerank = 0
        else:
            samerank += 1

        if score[0] > 0:
            print("%4d %4d %4d       %4d" % (rank, abs(score[2]), score[0], abs(score[1])))
        else:
            print("%4d %4d" % (rank, abs(score[2])))
        lastscore = score[0]
        lasttime = score[1]

    i += 1
    if (i != cases):
        print()
