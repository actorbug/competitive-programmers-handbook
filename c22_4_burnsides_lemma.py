import unittest
from math import gcd

def burnside(n,m):
    return sum(m**gcd(i,n) for i in range(n))//n

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(burnside(4,3),24)

if __name__=='__main__':
    unittest.main()
