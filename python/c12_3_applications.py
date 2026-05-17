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
    for i in range(n):
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
    for i in range(n):
        if not visited[i] and dfs(i,-1):
            return True
    return False

def finding_cycles2(adj):
    return any(sum(len(adj[i]) for i in c)!=len(c)*2-2 for c in connected(adj))

def bipartiteness_check(adj):
    n=len(adj)
    color=[None]*n
    def dfs(s,c):
        if color[s] is not None:
            return color[s]==c
        color[s]=c
        return all(dfs(u,not c) for u in adj[s])
    for i in range(n):
        if color[i] is None and not dfs(i,True):
            return None
    return color

class Test(unittest.TestCase):
    def test(self):
        self.assertCountEqual(map(sorted,connected([])),[])
        self.assertCountEqual(map(sorted,connected([[]])),[[0]])
        self.assertCountEqual(map(sorted,connected([[2,3],[4],[0,3],[0,2],[1]])),[[0,2,3],[1,4]])
        self.assertEqual(finding_cycles([]),False)
        self.assertEqual(finding_cycles([[2,3],[2,4],[0,1,3,4],[0,2],[1,2]]),True)
        self.assertEqual(finding_cycles2([]),False)
        self.assertEqual(finding_cycles2([[2,3],[2,4],[0,1,3,4],[0,2],[1,2]]),True)
        self.assertEqual(bipartiteness_check([]),[])
        self.assertEqual(bipartiteness_check([[]]),[True])
        self.assertIsNone(bipartiteness_check([[1,3],[0,2,4],[1,4],[0,4],[1,2,3]]))

if __name__=='__main__':
    unittest.main()
