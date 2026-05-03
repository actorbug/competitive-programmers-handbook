import unittest
from operator import itemgetter

def solve(ary):
    return sorted(ary,key=itemgetter(1))

def score(ary):
    cur=sc=0
    for _,a,x in ary:
        cur+=a
        sc+=x-cur
    return sc

class Test(unittest.TestCase):
    def assertValid(self,ary,x,t):
        with self.subTest(ary=ary):
            self.assertEqual(y:=solve(ary),x)
            self.assertEqual(score(y),t)
    def test(self):
        self.assertValid([],[],0)
        self.assertValid([('A',4,2),('B',3,5),('C',2,7),('D',4,5)],[('C',2,7),('B',3,5),('A',4,2),('D',4,5)],-10)

if __name__=='__main__':
    unittest.main()
