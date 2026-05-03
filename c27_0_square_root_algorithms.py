import unittest
from math import isqrt

class RootBlock:
    def __init__(self,array):
        n=len(array)
        k=1+isqrt(max(n-1,0))
        self.a=array
        self.k=k
        self.b=[sum(array[k*i:k*(i+1)]) for i in range(((n+k-1)//k))]
    def sum(self,a,b):
        k=self.k
        ak,bk=(a+k-1)//k,b//k
        if ak>=bk:
            return sum(self.a[a:b])
        else:
            return sum(self.a[a:ak*k])+sum(self.b[ak:bk])+sum(self.a[bk*k:b])
    def add(self,k,x):
        self.a[k]+=x
        self.b[k//self.k]+=x

class Test(unittest.TestCase):
    def test(self):
        r=RootBlock([])
        self.assertEqual(r.sum(0,0),0)
        r=RootBlock([5,8,6,3,2,7,2,6,7,1,7,5,6,2,3,2])
        self.assertEqual(r.k,4)
        self.assertEqual(r.b,[22,17,20,13])
        self.assertEqual(r.a,[5,8,6,3,2,7,2,6,7,1,7,5,6,2,3,2])
        r.add(5,-2)
        self.assertEqual(r.k,4)
        self.assertEqual(r.b,[22,15,20,13])
        self.assertEqual(r.a,[5,8,6,3,2,5,2,6,7,1,7,5,6,2,3,2])
        self.assertEqual(r.sum(3,14),46)

if __name__=='__main__':
    unittest.main()
