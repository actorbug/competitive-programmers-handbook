import unittest

def graph_traversal(adj,x):
    def dfs(s,e):
        yield s
        for u in adj[s]:
            if u!=e:
                yield from dfs(u,s)
    return dfs(x,-1)

def dynamic_programming(adj,x):
    count=[1]*len(adj)
    def dfs(s,e):
        for u in adj[s]:
            if u==e:
                continue
            dfs(u,s)
            count[s]+=count[u]
    dfs(x,-1)
    return count

class Test(unittest.TestCase):
    def test(self):
        adj=[[1,2,3],[0,4,5],[0],[0,6],[1],[1,7],[3],[5]]
        self.assertEqual([*graph_traversal([[]],0)],[0])
        self.assertEqual([*graph_traversal(adj,0)],[0,1,4,5,7,2,3,6])
        self.assertEqual(dynamic_programming([[]],0),[1])
        self.assertEqual(dynamic_programming(adj,0),[8,4,1,2,1,2,1,1])

if __name__=='__main__':
    unittest.main()
