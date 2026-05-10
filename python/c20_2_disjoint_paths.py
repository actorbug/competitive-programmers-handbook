import unittest
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
    def test(self):
        adj=[[1],[]]
        self.assertEqual(len([*edge_disjoint(adj,0,1)]),1)
        self.assertEqual(len([*node_disjoint(adj,0,1)]),1)

        adj=[[1,3],[3],[1,4,5],[2,4],[5],[]]
        self.assertEqual(len([*edge_disjoint(adj,0,5)]),2)
        self.assertEqual(len([*node_disjoint(adj,0,5)]),1)

if __name__=='__main__':
    unittest.main()
