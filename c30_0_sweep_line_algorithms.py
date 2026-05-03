import unittest
from itertools import accumulate
from operator import itemgetter

def count(r):
    return max(accumulate(map(itemgetter(1),sorted((v for i,j in r for v in ((i,1),(j,-1)))))))

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(count([(10,15),(6,12),(14,16),(5,13)]),3)

if __name__=='__main__':
    unittest.main()
