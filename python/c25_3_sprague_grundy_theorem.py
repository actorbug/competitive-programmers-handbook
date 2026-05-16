import unittest
from itertools import count
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def grundy(states,func):
    cache={}
    def rec(s):
        if s in cache:
            return cache[s]
        n=set(rec(i) for i in func(s))
        for i in count():
            if i not in n:
                cache[s]=i
                return i
    for s in states:
        rec(s)
    return cache

def grundy_maze(m):
    def maze(s):
        y,x=s
        for y1 in range(y-1,-1,-1):
            if m[y1][x]=='#':
                break
            yield y1,x
        for x1 in range(x-1,-1,-1):
            if m[y][x1]=='#':
                break
            yield y,x1
    h,w=len(m),len(m[0])
    r=[[None]*w for _ in range(h)]
    for (y,x),v in grundy(((i,j) for i in range(h) for j in range(w) if m[i][j]!='#'),maze).items():
        r[y][x]=v
    return r

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(grundy(range(6),lambda s:[[],[0],[1],[0,1],[1,3],[1,4]][s]),{0:0,1:1,2:0,3:2,4:0,5:2})
        self.assertEqual(grundy_maze(['..#..','#...#','..#..','#....','.....']),[[0,1,None,0,1],[None,0,1,2,None],[0,2,None,1,0],[None,3,0,4,1],[0,4,1,3,2]])

if __name__=='__main__':
    unittest.main()
