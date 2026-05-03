import unittest
from collections import Counter

class SegTree:
    def __init__(self,array):
        n=2**max(len(array)-1,0).bit_length()
        self.tree=[None]*n+[Counter([i]) for i in array]+[Counter()]*(n-len(array))
        for i in range(n-1,0,-1):
            self.tree[i]=self.tree[2*i]+self.tree[2*i+1]
    def count(self,x,a,b):
        a+=len(self.tree)//2
        b+=len(self.tree)//2
        s=0
        while a<=b:
            if a%2==1:
                s+=self.tree[a][x]
                a+=1
            if b%2==0:
                s+=self.tree[b][x]
                b-=1
            a//=2
            b//=2
        return s
    def __setitem__(self,k,x):
        k+=len(self.tree)//2
        p=next(self.tree[k])
        while k>=1:
            self.tree[k][p]-=1
            self.tree[k][x]+=1
            k//=2

class Test(unittest.TestCase):
    def test(self):
        s=SegTree([3,1,2,3,1,1,1,2])
        self.assertEqual(s.count(1,1,5),3)

if __name__=='__main__':
    unittest.main()
