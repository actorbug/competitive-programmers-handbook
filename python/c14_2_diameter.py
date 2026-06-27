import unittest
from heapq import heappushpop
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def dynamic_programming(adj):
    maxLength=0
    def dfs(s,e):
        nonlocal maxLength
        toLeaf=[-1,-1]
        for u in adj[s]:
            if u!=e:
                heappushpop(toLeaf,dfs(u,s))
        maxLength=max(maxLength,sum(toLeaf)+2)
        return toLeaf[1]+1
    dfs(1,0)
    return maxLength

def depth_first_search(adj):
    def dfs(d,s,e):
        ret=(d,s)
        for u in adj[s]:
            if u!=e:
                ret=max(ret,dfs(d+1,u,s))
        return ret
    return dfs(0,dfs(0,1,0)[1],0)[0]

class Test(unittest.TestCase):
    def test(self):
        for d in (dynamic_programming,depth_first_search):
            with self.subTest(d=d):
                self.assertEqual(d([[],[]]),0)
                self.assertEqual(d([[],[2,3,4],[1,5,6],[1],[1,7],[2],[2],[4]]),4)

if __name__=='__main__':
    unittest.main()
