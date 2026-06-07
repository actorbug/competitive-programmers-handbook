import unittest
from bisect import bisect

def solve(lst,x):
    m=len(lst)//2
    sa=sb=[0]
    for e in lst[:m]:
        sa=[*merge(sa,e)]
    for e in lst[m:]:
        sb=[*merge(sb,e)]
    i,j=0,bisect(sb,x)-1
    while i<len(sa) and j>=0:
        if sa[i]+sb[j]<x:
            i+=1
        elif sa[i]+sb[j]>x:
            j-=1
        else:
            return True
    return False

def  merge(l,d):
    n=len(l)
    i1=i2=0
    while i1<n and i2<n:
        if l[i1]<l[i2]+d:
            yield l[i1]
            i1+=1
        else:
            yield l[i2]+d
            if l[i1]==l[i2]+d:
                i1+=1
            i2+=1
    for i in range(i1,n):
        yield l[i]
    for i in range(i2,n):
        yield l[i]+d

class Test(unittest.TestCase):
    def test(self):
        self.assertTrue(solve([],0))
        self.assertFalse(solve([],1))
        self.assertTrue(solve([3,2,1],1))
        self.assertTrue(solve([2,4,5,9],15))
        self.assertFalse(solve([2,4,5,9],10))

if __name__=='__main__':
    unittest.main()
