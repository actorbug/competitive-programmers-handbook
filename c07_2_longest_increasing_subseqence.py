import unittest
from bisect import bisect_left

def solve(array):
    n=len(array)
    length=[1]*n
    for k in range(n):
        for i in range(k):
            if array[i]<array[k]:
                length[k]=max(length[k],length[i]+1)
    return max(length,default=0)

def solve2(array):
    minval=[]
    for v in array:
        i=bisect_left(minval,v)
        minval[i:i+1]=[v]
    return len(minval)

class Test(unittest.TestCase):
    def test(self):
        for s in (solve,solve2):
            with self.subTest(s=s):
                self.assertEqual(s([]),0)
                self.assertEqual(s([6,2,5,1,7,4,8,3]),4)

if __name__=='__main__':
    unittest.main()
