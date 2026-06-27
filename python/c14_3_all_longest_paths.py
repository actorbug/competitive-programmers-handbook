import unittest
from heapq import heappushpop
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def all_longest_paths(adj):
    maxLength=[[(0,s),(0,s)] for s in range(len(adj))]
    def dfs(s,e):
        m=maxLength[s]
        for u in adj[s]:
            if u!=e:
                heappushpop(m,(dfs(u,s)+1,u))
        return m[1][0]
    dfs(1,0)
    def dfs2(s,e):
        m=maxLength[s]
        for u in adj[s]:
            if u!=e:
                heappushpop(maxLength[u],(m[m[1][1]!=u][0]+1,s))
                dfs2(u,s)
    dfs2(1,0)
    return [m[1][0] for m in maxLength]

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual([*all_longest_paths([[],[]])],[0,0])
        self.assertEqual([*all_longest_paths([[],[2,3,4],[1,5,6],[1],[1],[2],[2]])],[0,2,2,3,3,3,3])

if __name__=='__main__':
    unittest.main()
