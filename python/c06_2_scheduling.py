import unittest
from operator import itemgetter
from itertools import pairwise

def solve(ary):
    end=0
    for e in sorted(ary,key=itemgetter(-1)):
        if e[1]>=end:
            yield e
            end=e[-1]

class Test(unittest.TestCase):
    def assertValid(self,ary,l):
        with self.subTest(ary=ary):
            ret=[*solve(ary)]
            self.assertEqual(len(ret),l)
            for (_,_,e1),(_,s2,_) in pairwise(sorted(ret,key=itemgetter(1))):
                self.assertLessEqual(e1,s2)
    def test(self):
        self.assertValid([],0)
        self.assertValid([('A',1,3),('B',2,5),('C',3,9),('D',6,8)],2)
        self.assertValid([('A',1,4),('B',3,5),('C',4,7)],2)
        self.assertValid([('A',1,7),('B',2,4),('C',4,6)],2)

if __name__=='__main__':
    unittest.main()
