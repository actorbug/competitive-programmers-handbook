import unittest
from itertools import accumulate

class SumQueries:
    def __init__(self,array):
        self.s=[*accumulate(array,initial=0)]
    def __call__(self,a,b):
        return self.s[b+1]-self.s[a]

class MinimumQueries:
    def __init__(self,array):
        p=[*array]
        n=len(p)
        self.m=[p]
        for i in range(1,n.bit_length()):
            p=[min(p[j],p[j+(1<<(i-1))]) for j in range(n-(1<<i)+1)]
            self.m.append(p)
    def __call__(self,a,b):
        k=(b-a+1).bit_length()-1
        return min(self.m[k][a],self.m[k][b-(1<<k)+1])

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(SumQueries([])(0,-1),0)
        self.assertEqual(SumQueries([1,3,4,8,6,1,4,2])(3,6),19)
        self.assertEqual(MinimumQueries([1])(0,0),1)
        self.assertEqual(MinimumQueries([1,3,4,8,6,1,4,2])(1,6),1)

if __name__=='__main__':
    unittest.main()
