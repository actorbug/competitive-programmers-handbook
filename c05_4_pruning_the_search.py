import unittest

dv=((1,0),(-1,0),(0,1),(0,-1))

def can_move(x,y,n,visited):
    return 0<=x<n and 0<=y<n and not visited[y][x]

def basic(n):
    count=0
    visited=[[False]*n for _ in range(n)]
    def rec(k,x,y):
        nonlocal count
        if not can_move(x,y,n,visited):
            return
        if k>=n*n and x==n-1 and y==n-1:
            count+=1
        visited[y][x]=True
        for dx,dy in dv:
            rec(k+1,x+dx,y+dy)
        visited[y][x]=False
    rec(1,0,0)
    return count

def optimize1(n):
    if n<2:
        return max(n,0)
    count=0
    visited=[[False]*n for _ in range(n)]
    visited[0][0]=True
    def rec(k,x,y):
        nonlocal count
        if not can_move(x,y,n,visited):
            return
        if k>=n*n and x==n-1 and y==n-1:
            count+=1
        visited[y][x]=True
        for dx,dy in dv:
            rec(k+1,x+dx,y+dy)
        visited[y][x]=False
    rec(2,0,1)
    return count*2

def optimize2(n):
    if n<2:
        return max(n,0)
    count=0
    visited=[[False]*n for _ in range(n)]
    visited[0][0]=True
    def rec(k,x,y):
        nonlocal count
        if not can_move(x,y,n,visited):
            return
        if x==n-1 and y==n-1:
            if k>=n*n:
                count+=1
            return
        visited[y][x]=True
        for dx,dy in dv:
            rec(k+1,x+dx,y+dy)
        visited[y][x]=False
    rec(2,0,1)
    return count*2

def optimize3(n):
    if n<2:
        return max(n,0)
    count=0
    visited=[[False]*n for _ in range(n)]
    visited[0][0]=True
    def rec(k,x,y):
        nonlocal count
        if not can_move(x,y,n,visited):
            return
        if x==n-1 and y==n-1:
            if k>=n*n:
                count+=1
            return
        if x in (0,n-1) and can_move(x,y-1,n,visited) and can_move(x,y+1,n,visited):
            return
        if y in (0,n-1) and can_move(x-1,y,n,visited) and can_move(x+1,y,n,visited):
            return
        visited[y][x]=True
        for dx,dy in dv:
            rec(k+1,x+dx,y+dy)
        visited[y][x]=False
    rec(2,0,1)
    return count*2

def optimize4(n):
    if n<2:
        return max(n,0)
    count=0
    visited=[[False]*n for _ in range(n)]
    visited[0][0]=True
    def rec(k,x,y):
        nonlocal count
        if not can_move(x,y,n,visited):
            return
        if x==n-1 and y==n-1:
            if k>=n*n:
                count+=1
            return
        if can_move(x+1,y,n,visited)==can_move(x-1,y,n,visited) and can_move(x,y+1,n,visited)==can_move(x,y-1,n,visited):
            return
        visited[y][x]=True
        for dx,dy in dv:
            rec(k+1,x+dx,y+dy)
        visited[y][x]=False
    rec(2,0,1)
    return count*2

class Test(unittest.TestCase):
    def test(self):
        for o in (basic,optimize1,optimize2,optimize3,optimize4):
            with self.subTest(o=o):
                self.assertEqual(o(1),1)
                self.assertEqual(o(5),104)

if __name__=='__main__':
    unittest.main()
