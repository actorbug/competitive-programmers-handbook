import unittest
from math import isqrt
from collections import Counter

def dec(c,i):
    c[i]-=1
    if c[i]<=0:
        del c[i]

def mo(l,q):
    m=isqrt(len(l)-1)+1
    c=Counter()
    r=[None]*len(q)
    b=e=0
    for i in sorted(range(len(q)),key=lambda i:(q[i][0]//m,q[i][1])):
        if b==e:
            b=e=q[i][0]
        while e<q[i][1]:
            c[l[e]]+=1
            e+=1
        while e>q[i][1]:
            e-=1
            dec(c,l[e])
        while b>q[i][0]:
            b-=1
            c[l[b]]+=1
        while b<q[i][0]:
            dec(c,l[b])
            b+=1
        r[i]=len(c)
    return r

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(mo([4,2,5,4,2,4,3,3,4],[(1,5),(2,7)]),[3,4])

if __name__=='__main__':
    unittest.main()
