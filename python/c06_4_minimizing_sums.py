import unittest
from c24_5_randomized_algorithms import order_statistics

def min1(ary):
    return order_statistics(ary,len(ary)//2) if ary else 0

def sum1(ary,x):
    return sum(abs(a-x) for a in ary)

def min2(ary):
    return sum(ary)/len(ary) if ary else 0

def sum2(ary,x):
    return sum((a-x)**2 for a in ary)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(sum1([],min1([])),0)
        self.assertEqual(sum1([1,2],min1([1,2])),1)
        self.assertEqual(sum1([1,2,9,2,6],min1([1,2,9,2,6])),12)
        self.assertEqual(sum2([],min2([])),0)
        self.assertEqual(sum2([1,2,9,2,6],min2([1,2,9,2,6])),46)

if __name__=='__main__':
    unittest.main()
