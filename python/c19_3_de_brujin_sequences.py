import unittest
from itertools import product
from c19_1_eulerian_paths import hierhorzer2

def debrujin(n,k):
    if n<=1:
        yield from range(n*k)
        return
    adj=[]
    d=k**(n-2)
    for i in range(k**(n-1)):
        e=i%d*k
        adj.append([e+j for j in range(k)])
    yield from [0]*(n-2)
    for i in hierhorzer2(adj):
        yield i%k

class Test(unittest.TestCase):
    def assertDebrujin(self,n,k):
        with self.subTest(n=n,k=k):
            ret=[*debrujin(n,k)]
            self.assertEqual(len(ret),k**n+n-1)
            self.assertCountEqual((tuple(ret[i:i+n]) for i in range(k**n)),product(range(k),repeat=n))
    def test(self):
        self.assertDebrujin(0,0)
        self.assertDebrujin(1,3)
        self.assertDebrujin(3,2)

if __name__=='__main__':
    unittest.main()
