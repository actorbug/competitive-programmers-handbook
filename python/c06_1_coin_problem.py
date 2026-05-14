import unittest

INF=1<<63

def solve(coins,n):
    if n<0:
        return INF
    count=0
    for c in sorted(coins,reverse=True):
        count+=n//c
        n%=c
    return count if n==0 else INF

class Test(unittest.TestCase):
    def test(self):
        coins=[1,2,5,10,20,50,100,200]
        self.assertEqual(solve([],0),0)
        self.assertEqual(solve([],1),INF)
        self.assertEqual(solve([5],3),INF)
        self.assertEqual(solve(coins,-1),INF)
        self.assertEqual(solve(coins,0),0)
        self.assertEqual(solve(coins,520),4)
        self.assertEqual(solve([200,1,2,5,10,20,50,100],520),4)

if __name__=='__main__':
    unittest.main()
