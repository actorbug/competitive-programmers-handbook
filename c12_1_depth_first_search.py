import unittest

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
        self.assertEqual([*dfs([[]],0)],[0])
        self.assertEqual([*dfs([[1,3],[0,2,4],[1,4],[0],[1,2]],0)],[0,1,2,4,3])

if __name__=='__main__':
    unittest.main()
