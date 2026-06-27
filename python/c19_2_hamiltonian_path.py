import unittest
from itertools import combinations,pairwise

def ore(adj):
    n=len(adj)
    adj=[set(e) for e in adj]
    return all(len(adj[i])+len(adj[j])>=n-1 for i,j in combinations(range(1,n),2) if j not in adj[i])

def construction(adj):
    n=len(adj)-1
    adj=[sum(1<<(j-1) for j in adj[i]) for i in range(1,n+1)]
    dp=[0]*(1<<n)
    for s in range(1,1<<n):
        if s.bit_count()<=1:
            dp[s]=s
        else:
            for i in range(n):
                if s&1<<i and dp[s^1<<i]&adj[i]:
                    dp[s]|=1<<i
    s=(1<<n)-1
    prev=s
    while s:
        for i in range(n):
            if prev&dp[s]&1<<i:
                break
        yield i+1
        prev=adj[i]
        s^=1<<i

class Test(unittest.TestCase):
    def assertConstruction(self,adj):
        with self.subTest(adj=adj):
            ret=[*construction(adj)]
            self.assertCountEqual(ret,range(1,len(adj)))
            for i,j in pairwise(ret):
                self.assertIn(j,adj[i])
    def test(self):
        adj=[[],[2,4],[1,3,5],[2,5],[1,5],[2,3,4]]
        self.assertTrue(ore([[]]))
        self.assertFalse(ore(adj))

        self.assertConstruction([[]])
        self.assertConstruction(adj)

if __name__=='__main__':
    unittest.main()
