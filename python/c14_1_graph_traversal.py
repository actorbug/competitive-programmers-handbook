import unittest
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def graph_traversal(adj,x):
    def dfs(s,e):
        yield s
        for u in adj[s]:
            if u!=e:
                yield from dfs(u,s)
    return dfs(x,0)

def dynamic_programming(adj,x):
    count=[1]*len(adj)
    def dfs(s,e):
        for u in adj[s]:
            if u==e:
                continue
            dfs(u,s)
            count[s]+=count[u]
    dfs(x,0)
    return count

class Test(unittest.TestCase):
    def test(self):
        adj=[[],[2,3,4],[1,5,6],[1],[1,7],[2],[2,8],[4],[6]]
        self.assertEqual([*graph_traversal([[],[]],1)],[1])
        self.assertEqual([*graph_traversal(adj,1)],[1,2,5,6,8,3,4,7])
        self.assertEqual(dynamic_programming([[],[]],1),[1,1])
        self.assertEqual(dynamic_programming(adj,1),[1,8,4,1,2,1,2,1,1])

if __name__=='__main__':
    unittest.main()
