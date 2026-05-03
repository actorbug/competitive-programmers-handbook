import unittest
from collections import deque

def solve(a,n):
    s=deque()
    for i in range(len(a)):
        while s and a[s[-1]]>=a[i]:
            s.pop()
        s.append(i)
        if i>=n-1:
            if s[0]==i-n:
                s.popleft()
            yield s[0]

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual([*solve([],1)],[])
        self.assertEqual([*solve([1,2],1)],[0,1])
        self.assertEqual([*solve([2,1,4,5,3,4,1,2],4)],[1,1,4,6,6])

if __name__=='__main__':
    unittest.main()
