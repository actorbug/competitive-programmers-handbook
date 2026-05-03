import unittest

class SegTree:
    def __init__(self,arg):
        if isinstance(arg,int):
            n=2**max(arg-1,0).bit_length()
            self.tree=[0]*(n*2)
        else:
            n=2**max(len(arg)-1,0).bit_length()
            self.tree=[0]*n+arg+[0]*(n-len(arg))
            for i in range(n-1,0,-1):
                self.tree[i]=self.tree[2*i]+self.tree[2*i+1]
    def sum(self,a,b):
        a+=len(self.tree)//2
        b+=len(self.tree)//2
        s=0
        while a<=b:
            if a%2==1:
                s+=self.tree[a]
                a+=1
            if b%2==0:
                s+=self.tree[b]
                b-=1
            a//=2
            b//=2
        return s
    def add(self,k,x):
        k+=len(self.tree)//2
        self.tree[k]+=x
        while (k:=k//2)>=1:
            self.tree[k]=self.tree[2*k]+self.tree[2*k+1]

class SegTreeMin:
    def __init__(self,array):
        self.MAX=max(array)+1
        n=2**max(len(array)-1,0).bit_length()
        self.tree=[0]*n+array+[self.MAX]*(n-len(array))
        for i in range(n-1,0,-1):
            self.tree[i]=min(self.tree[2*i],self.tree[2*i+1])
    def min(self,a,b):
        a+=len(self.tree)//2
        b+=len(self.tree)//2
        m=self.MAX
        while a<=b:
            if a%2==1:
                m=min(m,self.tree[a])
                a+=1
            if b%2==0:
                m=min(m,self.tree[b])
                b-=1
            a//=2
            b//=2
        return m
    def add(self,k,x):
        k+=len(self.tree)//2
        self.tree[k]+=x
        while (k:=k//2)>=1:
            self.tree[k]=min(self.tree[2*k],self.tree[2*k+1])
    def minpos(self):
        k,n=1,len(self.tree)//2
        while k<n:
            k=2*k if self.tree[k]==self.tree[2*k] else 2*k+1
        return k-n

class Test(unittest.TestCase):
    def test(self):
        s=SegTree([])
        self.assertEqual(s.sum(0,-1),0)

        s=SegTree([5,8,6,3,2,7,2,6])
        self.assertEqual(s.sum(2,7),26)
        s.add(5,7)
        self.assertEqual(s.sum(2,7),33)

        s=SegTreeMin([5])
        self.assertEqual(s.min(0,0),5)
        self.assertEqual(s.minpos(),0)

        s=SegTreeMin([5,8,6,3,1,7,2,6])
        self.assertEqual(s.min(2,7),1)
        self.assertEqual(s.minpos(),4)

if __name__=='__main__':
    unittest.main()
