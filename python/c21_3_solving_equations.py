import unittest
from math import prod
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def ext_gcd(a,b):
    if b==0:
        return a,1,0
    d,x,y=ext_gcd(b,a%b)
    return d,y,x-(a//b)*y

def diophantine(a,b,c):
    d,x,y=ext_gcd(a,b)
    return (x*(c//d),y*(c//d)) if c%d==0 else None

def chinese(xs):
    ms=prod(m for _,m in xs)
    return sum(a*ms//m*pow(ms//m,-1,m) for a,m in xs)

class Test(unittest.TestCase):
    def assertDiophantine(self,a,b,c):
        with self.subTest(a=a,b=b,c=c):
            x,y=diophantine(a,b,c)
            self.assertEqual(a*x+b*y,c)
    def assertChinese(self,xs):
        with self.subTest(xs=xs):
            x=chinese(xs)
            for a,m in xs:
                self.assertEqual(x%m,a)
    def test(self):
        self.assertDiophantine(1,1,1)
        self.assertDiophantine(5,2,11)
        self.assertDiophantine(39,15,12)
        self.assertChinese([(1,2)])
        self.assertChinese([(3,5),(4,7),(2,3)])

if __name__=='__main__':
    unittest.main()
