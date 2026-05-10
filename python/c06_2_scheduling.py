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
        self.assertCountEqual(solve([]),[])
        self.assertCountEqual(solve([('A',1,3),('B',2,5),('C',3,9),('D',6,8)]),[('A',1,3),('D',6,8)])
        self.assertCountEqual(solve([('A',1,4),('B',3,5),('C',4,7)]),[('A',1,4),('C',4,7)])
        self.assertCountEqual(solve([('A',1,7),('B',2,4),('C',4,6)]),[('B',2,4),('C',4,6)])

if __name__=='__main__':
    unittest.main()
