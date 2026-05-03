import unittest

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
    def test(self):
        self.assertEqual(warnsdorf(1,1),[[1]])
        self.assertEqual(warnsdorf(4,3),[
            [1,12,3],
            [4,9,6],
            [7,2,11],
            [10,5,8]
        ])
        self.assertEqual(warnsdorf(5,5),[
            [1,22,11,16,7],
            [12,17,8,21,10],
            [25,2,23,6,15],
            [18,13,4,9,20],
            [3,24,19,14,5]
        ])

if __name__=='__main__':
    unittest.main()
