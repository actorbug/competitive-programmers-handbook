import unittest
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def dfs(adj,x):
    visited=[False]*len(adj)
    def rec(s):
        if visited[s]:
            return
        visited[s]=True
        yield s
        for u in adj[s]:
            yield from rec(u)
    return rec(x)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual([*dfs([[],[]],1)],[1])
        self.assertEqual([*dfs([[],[2,4],[1,3,5],[2,5],[1],[2,3]],1)],[1,2,3,5,4])

if __name__=='__main__':
    unittest.main()
