import unittest
from operator import itemgetter

def solve(ary):
    end=0
    for e in sorted(ary,key=itemgetter(-1)):
        if e[1]>=end:
            yield e
            end=e[-1]

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(len([*solve([])]),0)
        self.assertEqual(len([*solve([('A',1,3),('B',2,5),('C',3,9),('D',6,8)])]),2)
        self.assertEqual(len([*solve([('A',1,4),('B',3,5),('C',4,7)])]),2)
        self.assertEqual(len([*solve([('A',1,7),('B',2,4),('C',4,6)])]),2)

if __name__=='__main__':
    unittest.main()
