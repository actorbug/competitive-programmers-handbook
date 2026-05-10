import unittest
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
    def test(self):
        self.assertEqual([*debrujin(0,0)],[])
        self.assertEqual([*debrujin(1,3)],[0,1,2])
        self.assertEqual([*debrujin(3,2)],[0,0,0,1,0,1,1,1,0,0])

if __name__=='__main__':
    unittest.main()
