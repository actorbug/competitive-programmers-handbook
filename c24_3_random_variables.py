import unittest
from math import comb
from fractions import Fraction

def expected_empty(n):
    return n*((n-1)/n)**n

def expected_uniform(a,b):
    return (a+b)/2

def probability_binomial(p,n,x):
    return p**x*(1-p)**(n-x)*comb(n,x)

def expected_binomial(p,n):
    return p*n

def probability_geometric(p,x):
    return (1-p)**(x-1)*p

def expected_geometric(p):
    return 1/p

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(expected_empty(2),0.5)
        self.assertEqual(expected_uniform(1,6),3.5)
        self.assertEqual(probability_binomial(Fraction(1,6),10,3),Fraction(390625,2519424))
        self.assertEqual(expected_binomial(Fraction(1,6),10),Fraction(5,3))
        self.assertEqual(probability_geometric(Fraction(1,6),4),Fraction(125,1296))
        self.assertEqual(expected_geometric(Fraction(1,6)),6)

if __name__=='__main__':
    unittest.main()
