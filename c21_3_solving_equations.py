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
    def test(self):
        self.assertEqual(diophantine(1,1,1),(0,1))
        self.assertEqual(diophantine(5,2,11),(11,-22))
        self.assertEqual(diophantine(39,15,12),(8,-20))
        self.assertEqual(chinese([(1,2)]),1)
        self.assertEqual(chinese([(3,5),(4,7),(2,3)]),263)

if __name__=='__main__':
    unittest.main()
