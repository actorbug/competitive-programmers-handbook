import unittest
from collections.abc import Iterable
from functools import reduce
from operator import or_

class Bitset:
    def __init__(self,arg=0):
        if isinstance(arg,Iterable):
            self.v=reduce(or_,(1<<int(i) for i in arg))
        else:
            self.v=int(arg)
    def __repr__(self):
        return f'Bitset([{",".join(str(i) for i in self)}])'
    def __eq__(self,other):
        return isinstance(other,Bitset) and self.v==other.v
    def __len__(self):
        return self.v.bit_count()
    def __contains__(self,k):
        return self.v&(1<<k)
    def __iter__(self):
        return (i for i in range(self.v.bit_length()) if self.v&(1<<i))
    def __and__(self,other):
        return Bitset(self.v&int(other))
    def __or__(self,other):
        return Bitset(self.v|int(other))
    def __sub__(self,other):
        return Bitset(self.v&~int(other))
    def __invert__(self):
        return Bitset(self.v^0xffffffff)
    def __int__(self):
        return self.v

def subsets(n):
    for b in range(1<<n):
        yield Bitset(b)

def subsets_k(n,k):
    for b in range(1<<n):
        bs=Bitset(b)
        if len(bs)==k:
            yield bs

def subsetof(x):
    b,v=0,int(x)
    while True:
        yield Bitset(b)
        b=(b-v)&v
        if b<=0:
            break

class Test(unittest.TestCase):
    def test(self):
        x=Bitset([1,3,4,8])
        y=Bitset([3,6,8,9])
        self.assertEqual(repr(x),'Bitset([1,3,4,8])')
        self.assertTrue(x==Bitset([1,3,4,8]))
        self.assertFalse(x==y)
        self.assertEqual(len(x),4)
        self.assertTrue(4 in x)
        self.assertFalse(5 in x)
        self.assertCountEqual(x,[1,3,4,8])
        self.assertEqual(x&y,Bitset([3,8]))
        self.assertEqual(x|y,Bitset([1,3,4,6,8,9]))
        self.assertEqual(x-y,Bitset([1,4]))
        self.assertEqual(~x,Bitset([0,2,5,6,7,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31]))
        self.assertEqual(int(x),0b100011010)

        self.assertCountEqual(subsets(2),[Bitset(),Bitset([0]),Bitset([1]),Bitset([0,1])])
        self.assertCountEqual(subsets_k(2,1),[Bitset([0]),Bitset([1])])
        self.assertCountEqual(subsetof(x),[Bitset(),Bitset([1]),Bitset([3]),Bitset([4]),Bitset([8]),Bitset([1,3]),Bitset([1,4]),Bitset([1,8]),Bitset([3,4]),Bitset([3,8]),Bitset([4,8]),Bitset([1,3,4]),Bitset([1,3,8]),Bitset([1,4,8]),Bitset([3,4,8]),Bitset([1,3,4,8])])

if __name__=='__main__':
    unittest.main()
