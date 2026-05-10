import unittest
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def nqueen(n):
    count=0
    column=[0]*n
    diag1=[0]*(2*n-1)
    diag2=[0]*(2*n-1)
    def search(y):
        nonlocal count
        if y==n:
            count+=1
            return
        for x in range(n):
            if column[x] or diag1[x+y] or diag2[x-y+n-1]:
                continue
            column[x]=diag1[x+y]=diag2[x-y+n-1]=1
            search(y+1)
            column[x]=diag1[x+y]=diag2[x-y+n-1]=0
    search(0)
    return count

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(nqueen(1),1)
        self.assertEqual(nqueen(2),0)
        self.assertEqual(nqueen(3),0)
        self.assertEqual(nqueen(4),2)

if __name__=='__main__':
    unittest.main()
