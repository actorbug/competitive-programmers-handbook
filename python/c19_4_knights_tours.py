import unittest
from itertools import pairwise
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def warnsdorf(h,w,y=0,x=0):
    board=[[0]*w+[-1]*2 for _ in range(h)]+[[-1]*(w+2)]*2
    def npos(y,x):
        for dy,dx in ((2,1),(1,2),(-1,2),(-2,1),(-2,-1),(-1,-2),(1,-2),(2,-1)):
            ny,nx=y+dy,x+dx
            if board[ny][nx]==0:
                yield ny,nx
    def dfs(y,x,d):
        board[y][x]=d
        if d==h*w:
            return True
        for ny,nx in sorted(npos(y,x),key=lambda p:sum(1 for _ in npos(*p))):
            if dfs(ny,nx,d+1):
                return True
        board[y][x]=0
        return False
    return [b[:w] for b in board[:h]] if dfs(y,x,1) else None

class Test(unittest.TestCase):
    def assertWarnsdorf(self,h,w,y=0,x=0):
        with self.subTest(h=h,w=w,y=y,x=x):
            ret=warnsdorf(h,w,y,x)
            route=[(-2,-2)]*(h*w)
            for i,r in enumerate(ret):
                for j,v in enumerate(r):
                    self.assertGreaterEqual(v,1)
                    self.assertLessEqual(v,len(route))
                    route[v-1]=i,j
            self.assertEqual(route[0],(y,x))
            for (i1,j1),(i2,j2) in pairwise(route):
                self.assertCountEqual((abs(i1-i2),abs(j1-j2)),(1,2))
    def test(self):
        self.assertWarnsdorf(1,1)
        self.assertWarnsdorf(4,3)
        self.assertWarnsdorf(5,5)

if __name__=='__main__':
    unittest.main()
