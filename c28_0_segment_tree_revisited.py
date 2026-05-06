import unittest
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

class SegTree:
    def __init__(self,array):
        n=2**max(len(array)-1,0).bit_length()
        self.tree=[0]*n+array+[0]*(n-len(array))
        for i in range(n-1,0,-1):
            self.tree[i]=self.tree[2*i]+self.tree[2*i+1]
    def sum_rec(self,a,b,k,x,y):
        if b<x or a>y:
            return 0
        if a<=x and y<=b:
            return self.tree[k]
        d=(x+y)//2
        return self.sum_rec(a,b,2*k,x,d)+self.sum_rec(a,b,2*k+1,d+1,y)
    def sum(self,a,b):
        return self.sum_rec(a,b,1,0,len(self.tree)//2-1)
    def add(self,k,x):
        k+=len(self.tree)//2
        self.tree[k]+=x
        while (k:=k//2)>=1:
            self.tree[k]=self.tree[2*k]+self.tree[2*k+1]

class Test(unittest.TestCase):
    def test(self):
        s=SegTree([])
        self.assertEqual(s.sum(0,-1),0)

        s=SegTree([5,8,6,3,2,7,2,6])
        self.assertEqual(s.sum(2,7),26)
        s.add(5,7)
        self.assertEqual(s.sum(2,7),33)

if __name__=='__main__':
    unittest.main()
