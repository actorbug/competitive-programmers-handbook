import unittest
from itertools import combinations,chain
from collections import deque,defaultdict
from math import isqrt

def min_dist(board):
    h,w=len(board),len(board[0])
    mind,minp=w+h,None
    def algorithm1(ps):
        nonlocal mind,minp
        for (y1,x1),(y2,x2) in combinations(ps,2):
            md=abs(y2-y1)+abs(x2-x1)
            if mind>md:
                mind,minp=md,((y1,x1),(y2,x2))
    def algorithm2(ps):
        nonlocal mind,minp
        q,r=deque(ps),[[(-1,-1)]*w for _ in range(h)]
        for i,(y,x) in enumerate(ps):
            r[y][x]=i,0
        while q:
            y,x=q.popleft()
            for dy,dx in ((-1,0),(0,-1),(1,0),(0,1)):
                ny,nx=y+dy,x+dx
                if ny<0 or h<=ny or nx<0 or w<=nx or r[ny][nx][0]==r[y][x][0]:
                    continue
                if r[ny][nx][0]<0:
                    r[ny][nx]=r[y][x][0],r[y][x][1]+1
                    continue
                md=r[y][x][1]+r[ny][nx][1]+1
                if mind>md:
                    mind,minp=md,(ps[r[y][x][0]],ps[r[ny][nx][0]])
    n,d=w*h,defaultdict(list)
    for i,a in enumerate(board):
        for j,c in enumerate(a):
            d[c].append((i,j))
    for ps in d.values():
        if len(ps)**2<n:
            algorithm1(ps)
        else:
            algorithm2(ps)
    return minp

def min_dist2(pos):
    h,w=(max(*v)+1 for v in zip(*pos))
    m=1+isqrt(len(pos)-1)
    for i,(y,x) in enumerate(pos):
        if i>0:
            yield min(chain((board[y][x],),(abs(y-y1)+abs(x-x1) for y1,x1 in rest)))
        if i%m:
            rest.append((y,x))
            continue
        q,board=deque(),[[None]*w for _ in range(h)]
        for y,x in pos[:i+1]:
            q.append((y,x))
            board[y][x]=0
        while q:
            y,x=q.popleft()
            for dy,dx in [(-1,0),(0,-1),(1,0),(0,1)]:
                ny,nx=y+dy,x+dx
                if ny<0 or h<=ny or nx<0 or w<=nx:
                    continue
                if board[ny][nx] is None:
                    board[ny][nx]=board[y][x]+1
                    q.append((ny,nx))
        rest=[]

class Test(unittest.TestCase):
    def test(self):
        self.assertCountEqual(min_dist(['AFBA','CEGE','BDAF','ACBD']),((1,1),(1,3)))
        self.assertEqual([*min_dist2([(0,0),(2,3),(2,1),(0,2),(3,0),(3,2),(0,1),(0,3),(1,0),(1,1),(1,2),(1,3),(2,0),(2,2),(3,1),(3,3)])],[5,2,2,2,2,1,1,1,1,1,1,1,1,1,1])

if __name__=='__main__':
    unittest.main()
