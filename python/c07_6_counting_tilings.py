import unittest
from math import pi,cos,prod
from itertools import product

def solve(n,m):
    def isvalid(prev,curr):
        for j in range(m):
            if prev[j]=='A':
                if curr[j]!='V' or j>0 and curr[j-1]=='<':
                    return False
            elif j>0 and curr[j-1]=='<':
                if curr[j]!='>':
                    return False
            elif curr[j]!='A' and not (j<m-1 and curr[j]=='<'):
                return False
        return True
    if n<m:
        n,m=m,n
    dp={'V'*m:1}
    for _ in range(n):
        ndp={}
        for curr in product('V<A>',repeat=m):
            sum_=sum(v for prev,v in dp.items() if isvalid(prev,curr))
            if sum_>0:
                ndp[curr]=sum_
        dp=ndp
    return sum(v for prev,v in dp.items() if 'A' not in prev)

def solve2(n,m):
    def isvalid(prev,curr):
        open_=False
        for j in range(m):
            if prev[j]=='A':
                if curr[j]!='O' or open_:
                    return False
            elif open_:
                if curr[j]!='O':
                    return False
                open_=False
            elif curr[j]=='O':
                if j>=m-1:
                    return False
                open_=True
        return True
    if n<m:
        n,m=m,n
    dp={'O'*m:1}
    for _ in range(n):
        ndp={}
        for curr in product('OA',repeat=m):
            sum_=sum(v for prev,v in dp.items() if isvalid(prev,curr))
            if sum_>0:
                ndp[curr]=sum_
        dp=ndp
    return sum(v for prev,v in dp.items() if 'A' not in prev)

def solve3(n,m):
    def cosn(n):
        return [cos(pi*a/(n+1))**2 for a in range(1,(n+3)//2)]
    cn,cm=cosn(n),cosn(m)
    return round(prod(prod(4*(k+l) for l in cm) for k in cn))

class Test(unittest.TestCase):
    def test(self):
        for s in (solve,solve2,solve3):
            with self.subTest(s=s):
                self.assertEqual(s(0,0),1)
                self.assertEqual(s(4,7),781)

if __name__=='__main__':
    unittest.main()
