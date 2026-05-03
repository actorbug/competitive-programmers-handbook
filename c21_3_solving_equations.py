import unittest
from math import prod

def matmul(a,b):
    return *((*(sum(i*j for i,j in zip(ai,bi)) for bi in zip(*b)),) for ai in a),

def diophantine(a,b,c):
    m=((1,0),(0,1))
    while b>0:
        m=matmul(m,((0,1),(1,-(a//b))))
        a,b=b,a%b
    return (m[0][0]*c//a,m[1][0]*c//a) if c%a==0 else None

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
