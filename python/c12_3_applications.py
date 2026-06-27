import unittest
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def connected(adj):
    n=len(adj)
    visited=[False]*n
    def dfs(s):
        if visited[s]:
            return
        visited[s]=True
        yield s
        for u in adj[s]:
            yield from dfs(u)
    for i in range(1,n):
        if not visited[i]:
            yield [*dfs(i)]

def finding_cycles(adj):
    n=len(adj)
    visited=[False]*n
    def dfs(s,e):
        if visited[s]:
            return True
        visited[s]=True
        return any(dfs(u,s) for u in adj[s] if u!=e)
    for i in range(1,n):
        if not visited[i] and dfs(i,0):
            return True
    return False

def finding_cycles2(adj):
    return any(sum(len(adj[i]) for i in c)!=len(c)*2-2 for c in connected(adj))

def bipartiteness_check(adj):
    n=len(adj)
    visited=[False]*n
    color=[False]*n
    def dfs(s,c):
        if visited[s]:
            return color[s]==c
        visited[s]=True
        color[s]=c
        return all(dfs(u,not c) for u in adj[s])
    for i in range(1,n):
        if not visited[i] and not dfs(i,False):
            return None
    return color

class Test(unittest.TestCase):
    def test(self):
        self.assertCountEqual(map(sorted,connected([[]])),[])
        self.assertCountEqual(map(sorted,connected([[],[]])),[[1]])
        self.assertCountEqual(map(sorted,connected([[],[3,4],[5],[1,4],[1,3],[2]])),[[1,3,4],[2,5]])
        self.assertFalse(finding_cycles([[]]))
        self.assertTrue(finding_cycles([[],[3,4],[3,5],[1,2,4,5],[1,3],[2,3]]))
        self.assertTrue(finding_cycles([[],[],[3,4],[4,2],[2,3]]))
        self.assertFalse(finding_cycles2([[]]))
        self.assertTrue(finding_cycles2([[],[3,4],[3,5],[1,2,4,5],[1,3],[2,3]]))
        self.assertTrue(finding_cycles2([[],[],[3,4],[4,2],[2,3]]))
        self.assertEqual(bipartiteness_check([[]]),[False])
        self.assertEqual(bipartiteness_check([[],[]]),[False,False])
        self.assertIsNone(bipartiteness_check([[],[2,4],[1,3,5],[2,5],[1,5],[2,3,4]]))
        self.assertIsNone(bipartiteness_check([[],[],[3,4],[4,2],[2,3]]))

if __name__=='__main__':
    unittest.main()
