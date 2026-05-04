import unittest

dv=((1,0),(-1,0),(0,1),(0,-1))

def can_move(y,x,n,visited):
    return 0<=y<n and 0<=x<n and not visited[y][x]

def basic(n):
    count=0
    visited=[[False]*n for _ in range(n)]
    def rec(k,y,x):
        nonlocal count
        if not can_move(y,x,n,visited):
            return
        if k>=n*n and y==n-1 and x==n-1:
            count+=1
        visited[y][x]=True
        for dy,dx in dv:
            rec(k+1,y+dy,x+dx)
        visited[y][x]=False
    rec(1,0,0)
    return count

def optimize1(n):
    if n<2:
        return max(n,0)
    count=0
    visited=[[False]*n for _ in range(n)]
    visited[0][0]=True
    def rec(k,y,x):
        nonlocal count
        if not can_move(y,x,n,visited):
            return
        if k>=n*n and y==n-1 and x==n-1:
            count+=1
        visited[y][x]=True
        for dy,dx in dv:
            rec(k+1,y+dy,x+dx)
        visited[y][x]=False
    rec(2,1,0)
    return count*2

def optimize2(n):
    if n<2:
        return max(n,0)
    count=0
    visited=[[False]*n for _ in range(n)]
    visited[0][0]=True
    def rec(k,y,x):
        nonlocal count
        if not can_move(y,x,n,visited):
            return
        if y==n-1 and x==n-1:
            if k>=n*n:
                count+=1
            return
        visited[y][x]=True
        for dy,dx in dv:
            rec(k+1,y+dy,x+dx)
        visited[y][x]=False
    rec(2,1,0)
    return count*2

def optimize3(n):
    if n<2:
        return max(n,0)
    count=0
    visited=[[False]*n for _ in range(n)]
    visited[0][0]=True
    def rec(k,y,x):
        nonlocal count
        if not can_move(y,x,n,visited):
            return
        if y==n-1 and x==n-1:
            if k>=n*n:
                count+=1
            return
        if y in (0,n-1) and can_move(y,x-1,n,visited) and can_move(y,x+1,n,visited):
            return
        if x in (0,n-1) and can_move(y-1,x,n,visited) and can_move(y+1,x,n,visited):
            return
        visited[y][x]=True
        for dy,dx in dv:
            rec(k+1,y+dy,x+dx)
        visited[y][x]=False
    rec(2,1,0)
    return count*2

def optimize4(n):
    if n<2:
        return max(n,0)
    count=0
    visited=[[False]*n for _ in range(n)]
    visited[0][0]=True
    def rec(k,y,x):
        nonlocal count
        if not can_move(y,x,n,visited):
            return
        if y==n-1 and x==n-1:
            if k>=n*n:
                count+=1
            return
        if can_move(y+1,x,n,visited)==can_move(y-1,x,n,visited) and can_move(y,x+1,n,visited)==can_move(y,x-1,n,visited):
            return
        visited[y][x]=True
        for dy,dx in dv:
            rec(k+1,y+dy,x+dx)
        visited[y][x]=False
    rec(2,1,0)
    return count*2

class Test(unittest.TestCase):
    def test(self):
        for o in (basic,optimize1,optimize2,optimize3,optimize4):
            with self.subTest(o=o):
                self.assertEqual(o(1),1)
                self.assertEqual(o(5),104)

if __name__=='__main__':
    unittest.main()
