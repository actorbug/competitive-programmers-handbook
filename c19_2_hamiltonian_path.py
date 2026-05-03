import unittest
from itertools import combinations

def ore(adj):
    n=len(adj)
    adj=[set(e) for e in adj]
    return all(len(adj[i])+len(adj[j])>=n for i,j in combinations(range(n),2) if j not in adj[i])

def construction(adj):
    n=len(adj)
    adj=[sum(1<<j for j in i) for i in adj]
    dp=[0]*(1<<n)
    for s in range(1,1<<n):
        if s.bit_count()<=1:
            dp[s]=s
        else:
            for i in range(n):
                if s&1<<i and dp[s^1<<i]&adj[i]:
                    dp[s]|=1<<i
    s=(1<<n)-1
    while s:
        for i in range(n):
            if dp[s]&1<<i:
                break
        yield i
        s^=1<<i

class Test(unittest.TestCase):
    def test(self):
        adj=[[1,3],[0,2,4],[1,4],[0,4],[1,2,3]]
        self.assertTrue(ore([]))
        self.assertFalse(ore(adj))

        self.assertEqual([*construction([])],[])
        self.assertEqual([*construction(adj)],[0,1,2,3,4])

if __name__=='__main__':
    unittest.main()
