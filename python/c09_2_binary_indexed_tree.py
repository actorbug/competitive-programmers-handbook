import unittest

class BIT:
    def __init__(self,arg):
        if isinstance(arg,int):
            self.tree=[0]*(arg+1)
        else:
            n=len(arg)+1
            self.tree=[0]+arg
            for i in range(1,n):
                if (j:=i+(i&-i))<n:
                    self.tree[j]+=self.tree[i]
    def sum(self,k):
        s=0
        while k>0:
            s+=self.tree[k]
            k-=k&-k
        return s
    def add(self,k,x):
        while k<len(self.tree):
            self.tree[k]+=x
            k+=k&-k
    def __getitem__(self,k):
        return self.sum(k)-self.sum(k-1)
    def __setitem__(self,k,x):
        self.add(k,x-self[k])
    def lower_bound(self, x):
        size=len(self.tree)-1
        sum_=0
        pos=0
        for i in range(size.bit_length(),-1,-1):
            k=pos+(1<<i)
            if k<=size and sum_+self.tree[k]<x:
                sum_+=self.tree[k]
                pos+=1<<i
        return pos+1

class Test(unittest.TestCase):
    def test(self):
        b=BIT(0)
        self.assertEqual(b.sum(0),0)

        b=BIT([1,3,4,8,6,1,4,2])
        self.assertEqual(b.sum(7),27)
        b.add(3,7)
        self.assertEqual(b.sum(7),34)

if __name__=='__main__':
    unittest.main()
