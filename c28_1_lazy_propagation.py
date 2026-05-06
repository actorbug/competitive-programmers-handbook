import unittest
from itertools import zip_longest
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

class LazySegTree:
    def __init__(self,array):
        self.n=2**max(len(array)-1,0).bit_length()
        self.s=[0]*self.n+array+[0]*(self.n-len(array))
        self.z=[0]*(self.n*2)
        for i in range(self.n-1,0,-1):
            self.s[i]=self.s[2*i]+self.s[2*i+1]
    def apply(self,k,x,y):
        if self.z[k]:
            self.s[k]+=self.z[k]*(y-x+1)
            if x<y:
                self.z[2*k]+=self.z[k]
                self.z[2*k+1]+=self.z[k]
            self.z[k]=0
    def sum_rec(self,a,b,k,x,y):
        self.apply(k,x,y)
        if b<x or a>y:
            return 0
        if a<=x and y<=b:
            return self.s[k]
        d=(x+y)//2
        return self.sum_rec(a,b,2*k,x,d)+self.sum_rec(a,b,2*k+1,d+1,y)
    def sum(self,a,b):
        return self.sum_rec(a,b,1,0,self.n-1)
    def add_rec(self,a,b,u,k,x,y):
        self.apply(k,x,y)
        if b<x or a>y:
            return
        if a<=x and y<=b:
            self.z[k]+=u
            return
        d=(x+y)//2
        self.s[k]+=u*(min(b,y)-max(a,x)+1)
        self.add_rec(a,b,u,2*k,x,d)
        self.add_rec(a,b,u,2*k+1,d+1,y)
    def add(self,a,b,u):
        self.add_rec(a,b,u,1,0,self.n-1)

def add_poly(a,b):
    return [i+j for i,j in zip_longest(a,b,fillvalue=0)]
def shift_poly(t,h):
    t=t+[0,0]
    r=[t[0]+h*(t[1]+h*t[2]),t[1]+h*t[2]*2,t[2]]
    while r and r[-1]==0:
        r.pop()
    return r
def ind_sum_poly(z,n):
    return sum(i*j for i,j in zip(z,[n,n*(n-1)//2]))

class PolyLazySegTree:
    def __init__(self,array):
        self.n=2**max(len(array)-1,0).bit_length()
        self.s=[0]*self.n+array+[0]*(self.n-len(array))
        self.z=[[] for _ in range(self.n*2)]
        for i in range(self.n-1,0,-1):
            self.s[i]=self.s[2*i]+self.s[2*i+1]
    def apply(self,k,x,y):
        if self.z[k]:
            self.s[k]+=ind_sum_poly(self.z[k],y-x+1)
            if x<y:
                self.z[2*k]=add_poly(self.z[2*k],self.z[k])
                self.z[2*k+1]=add_poly(self.z[2*k+1],shift_poly(self.z[k],(y-x+1)//2))
            self.z[k]=[]
    def sum_rec(self,a,b,k,x,y):
        self.apply(k,x,y)
        if b<x or a>y:
            return 0
        if a<=x and y<=b:
            return self.s[k]
        d=(x+y)//2
        return self.sum_rec(a,b,2*k,x,d)+self.sum_rec(a,b,2*k+1,d+1,y)
    def sum(self,a,b):
        return self.sum_rec(a,b,1,0,self.n-1)
    def add_rec(self,a,b,u,k,x,y):
        self.apply(k,x,y)
        if b<x or a>y:
            return
        if a<=x and y<=b:
            self.z[k]=add_poly(self.z[k],shift_poly(u,x-a))
            return
        d=(x+y)//2
        self.s[k]+=ind_sum_poly(u,min(b,y)-a+1)-ind_sum_poly(u,max(0,x-a))
        self.add_rec(a,b,u,2*k,x,d)
        self.add_rec(a,b,u,2*k+1,d+1,y)
    def add(self,a,b,u):
        self.add_rec(a,b,u,1,0,self.n-1)

class Test(unittest.TestCase):
    def test(self):
        s=LazySegTree([])
        self.assertEqual(s.sum(0,-1),0)

        s=LazySegTree([5,8,6,3,2,7,2,6])
        self.assertEqual(s.sum(2,7),26)
        s.add(5,5,7)
        self.assertEqual(s.sum(2,7),33)

        s=LazySegTree([5,8,6,3,2,7,2,6,7,1,7,5,6,2,3,2])
        s.add(5,13,2)
        self.assertEqual(s.sum(10,13),28)

        s=PolyLazySegTree([])
        self.assertEqual(s.sum(0,-1),0)

        s=PolyLazySegTree([5,8,6,3,2,7,2,6])
        self.assertEqual(s.sum(2,7),26)
        s.add(5,5,[7])
        self.assertEqual(s.sum(2,7),33)

        s=PolyLazySegTree([5,8,6,3,2,7,2,6,7,1,7,5,6,2,3,2])
        s.add(5,13,[2])
        self.assertEqual(s.sum(10,13),28)

        s=PolyLazySegTree([5,8,6,3,2,7,2,6,7,1,7,5,6,2,3,2])
        s.add(5,13,[1,1])
        self.assertEqual(s.sum(10,13),50)

if __name__=='__main__':
    unittest.main()
