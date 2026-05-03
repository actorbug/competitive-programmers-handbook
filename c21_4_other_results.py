import unittest
from math import factorial

def pythagorean(m,n):
    return n**2-m**2,2*n*m,n**2+m**2

def wilson(n):
    return factorial(n-1)%n==n-1

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(pythagorean(1,2),(3,4,5))
        self.assertTrue(wilson(11))
        self.assertFalse(wilson(12))

if __name__=='__main__':
    unittest.main()
