import unittest
import sys
from util import reversed_adj

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def kosaraju(adj):
    n=len(adj)
    visited=[False]*n
    def dfs(adj,s):
        if visited[s]:
            return
        visited[s]=True
        for u in adj[s]:
            yield from dfs(adj,u)
        yield s
    nodes=[]
    for x in range(1,n):
        if not visited[x]:
            nodes+=dfs(adj,x)
    radj=reversed_adj(adj)
    visited=[False]*n
    for x in reversed(nodes):
        if not visited[x]:
            yield [*dfs(radj,x)]

class Test(unittest.TestCase):
    def assertKosaraju(self,adj,expected):
        with self.subTest(adj=adj):
            self.assertCountEqual((sorted(r) for r in kosaraju(adj)),expected)
    def test(self):
        self.assertKosaraju([[]], [])
        self.assertKosaraju([[],[2,4],[1,5],[2,7],[],[4],[3,5],[6]],[[1,2],[3,6,7],[4],[5]])

if __name__=='__main__':
    unittest.main()
