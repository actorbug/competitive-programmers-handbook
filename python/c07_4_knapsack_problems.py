import unittest

def solve(w):
    n,W=len(w),sum(w)
    possible=[[False]*(W+1) for _ in range(n+1)]
    possible[0][0]=True
    for k in range(1,n+1):
        for x in range(W+1):
            if x-w[k-1]>=0:
                possible[k][x]|=possible[k-1][x-w[k-1]]
            possible[k][x]|=possible[k-1][x]
    return possible[n]

def solve2(w):
    W=sum(w)
    possible=[False]*(W+1)
    possible[0]=True
    for k in w:
        for x in range(W-k,-1,-1):
            if possible[x]:
                possible[x+k]=True
    return possible

class Test(unittest.TestCase):
    def test(self):
        for s in (solve,solve2):
            with self.subTest(s=s):
                self.assertEqual(s([]),[True])
                self.assertEqual(s([1,3,3,5]),[True,True,False,True,True,True,True,True,True,True,False,True,True])

if __name__=='__main__':
    unittest.main()
