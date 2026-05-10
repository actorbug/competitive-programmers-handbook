import unittest

def solve(coins,n):
    count=0
    for c in sorted(coins,reverse=True):
        count+=n//c
        n%=c
    return count if n==0 else None

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(solve([],0),0)
        self.assertIsNone(solve([],1))
        self.assertEqual(solve([1,2,5,10,20,50,100,200],520),4)
        self.assertEqual(solve([200,1,2,5,10,20,50,100],520),4)

if __name__=='__main__':
    unittest.main()
