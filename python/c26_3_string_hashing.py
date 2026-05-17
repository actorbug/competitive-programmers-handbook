import unittest
from functools import total_ordering

a,b=3,97

@total_ordering
class Preprocessing:
    def __init__(self,s):
        self.s=s
        h,p=0,b-1
        self.h,self.p=[h],[p]
        for c in s:
            h,p=(h*a+ord(c))%b,p*a%b
            self.h.append(h)
            self.p.append(p)
    def __eq__(self,o):
        return isinstance(o,Preprocessing) and self.s==o.s
    def __len__(self):
        return len(self.s)
    def subhash(self,l,r):
        return (self.h[l]*self.p[r-l]%b+self.h[r])%b
    def __lt__(self,o):
        ok,ng=0,min(len(self),len(o))+1
        while ng-ok>1:
            mid=(ok+ng)//2
            if self.subhash(0,mid)==o.subhash(0,mid):
                ok=mid
            else:
                ng=mid
        return not ok>=len(o) and (ok>=len(self) or self.s[ok]<o.s[ok])
    def find(self,t):
        n,ht=len(t),self.hash(t)
        for i in range(len(self.s)-n+1):
            if self.subhash(i,i+n)==ht and self.s[i:i+n]==t:
                return i
        return None
    @classmethod
    def hash(cls,s):
        return cls(s).h[-1]

class Test(unittest.TestCase):
    def test(self):
        p=Preprocessing('ALLEY')
        self.assertEqual(p.h,[0,65,77,16,20,52])
        self.assertEqual(p.p,[96,94,88,70,16,48])
        self.assertEqual(p.subhash(0,1),65)
        self.assertEqual(p.subhash(0,2),77)
        self.assertEqual(Preprocessing('').find(''),0)
        self.assertEqual(Preprocessing('ABABCBABC').find('ABC'),2)
        self.assertIsNone(Preprocessing('ABABCBABC').find('XXX'))
        abc=Preprocessing('ABC')
        abcd=Preprocessing('ABCD')
        abd=Preprocessing('ABD')
        self.assertGreaterEqual(abc,abc)
        self.assertGreaterEqual(abcd,abc)
        self.assertLess(abc,abcd)
        self.assertLess(abc,abd)
        self.assertGreaterEqual(abd,abc)

if __name__=='__main__':
    unittest.main()
