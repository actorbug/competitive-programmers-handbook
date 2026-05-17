import unittest
from itertools import pairwise
from c20_1_ford_fulkerson_algorithm import ford_fulkerson,adj2tc

def edge_disjoint(adj,s,e):
    adj2=ford_fulkerson([[(j,1) for j in i] for i in adj],s,e)
    for _ in range(adj2tc(adj2,e)):
        r=[s]
        while r[-1]!=e:
            i=next(i for i in adj[r[-1]] if adj2[i][r[-1]]>0)
            adj2[i][r[-1]]=0
            r.append(i)
        yield r

def node_disjoint(adj,s,e):
    l=len(adj)
    for r in edge_disjoint([[] if i in (s,e) else [i+l] for i in range(l)]+adj,s+l,e):
        yield [s,*r[1::2]]

class Test(unittest.TestCase):
    def assertEdgeDisjoint(self,adj,s,e,l):
        with self.subTest(adj=adj,s=s,e=e):
            edges = {(i,j) for i,a in enumerate(adj) for j in a}
            ret = [*edge_disjoint(adj,s,e)]
            self.assertEqual(len(ret),l)
            for r in ret:
                for p in pairwise(r):
                    self.assertIn(p,edges)
                    edges.discard(p)
    def assertNodeDisjoint(self,adj,s,e,l):
        with self.subTest(adj=adj,s=s,e=e):
            nodes = {*range(len(adj))}-{s,e}
            ret=[*node_disjoint(adj,s,e)]
            self.assertEqual(len(ret),l)
            for r in ret:
                for a in r[1:-1]:
                    self.assertIn(a,nodes)
                    nodes.discard(a)
            for r in ret:
                for a,b in pairwise(r):
                    self.assertIn(b,adj[a])
    def test(self):
        adj=[[1],[]]
        self.assertEdgeDisjoint(adj,0,1,1)
        self.assertNodeDisjoint(adj,0,1,1)

        adj=[[1,3],[3],[1,4,5],[2,4],[5],[]]
        self.assertEdgeDisjoint(adj,0,5,2)
        self.assertNodeDisjoint(adj,0,5,1)

if __name__=='__main__':
    unittest.main()
