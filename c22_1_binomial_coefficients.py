import unittest
from math import comb

def scenario1(n,k):
    return comb(n,k)

def scenario2(n,k):
    return comb(k+n-1,k)

def scenario3(n,k):
    return comb(n-k+1,n-2*k+1)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(scenario1(5,2),10)
        self.assertEqual(scenario2(5,2),15)
        self.assertEqual(scenario3(5,2),6)

if __name__=='__main__':
    unittest.main()
