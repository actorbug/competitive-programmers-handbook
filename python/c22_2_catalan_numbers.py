import unittest
from math import comb

def cataran(n):
    return comb(2*n,n)//(n+1)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(cataran(3),5)

if __name__=='__main__':
    unittest.main()
