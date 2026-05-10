import unittest
from itertools import pairwise
from c09_2_binary_indexed_tree import BIT

def index_compression(array,start=0):
    return {e:i for i,e in enumerate(sorted(set(array)),start)}

class RangeUpdates:
    def __init__(self,arg):
        if isinstance(arg,int):
            self.bit=BIT(arg+1)
        else:
            self.bit=BIT([b-a for a,b in pairwise([0,*arg,0])])
    def __getitem__(self,k):
        return self.bit.sum(k+1)
    def add(self,a,b,x):
        self.bit.add(a+1,x)
        self.bit.add(b+2,-x)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(index_compression([],1),{})
        self.assertEqual(index_compression([555,10**9,8],1),{8:1,555:2,10**9:3})

        ru=RangeUpdates([3])
        ru.add(0,0,5)
        self.assertEqual(ru[0],8)

        ru=RangeUpdates([3,3,1,1,1,5,2,2])
        ru.add(1,4,5)
        self.assertEqual([ru[0],ru[1],ru[4],ru[5]],[3,8,6,5])

if __name__=='__main__':
    unittest.main()
