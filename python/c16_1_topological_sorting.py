import unittest
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def topological(adj):
    n=len(adj)
    visited=[0]*n
    ret=[]
    def dfs(s):
        if visited[s]:
            return visited[s]!=1
        visited[s]=1
        if not all(map(dfs,adj[s])):
            return False
        ret.append(s)
        visited[s]=2
        return True
    for x in range(n):
        if not visited[x] and not dfs(x):
            return None
    ret.reverse()
    return ret

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(topological([]),[])
        adj=[[1],[2],[5],[0,4],[1,2],[]]
        pos={v:i for i,v in enumerate(topological(adj))}
        for a in range(len(adj)):
            for b in adj[a]:
                self.assertLess(pos[a],pos[b])
        self.assertIsNone(topological([[1],[2],[4,5],[0,4],[1],[]]))

if __name__=='__main__':
    unittest.main()
