import unittest
from itertools import pairwise
from c13_3_floyd_warshall_algorithm import INF,floyd_warshall
from c20_3_maximum_matchings import maximum_matching

class Connect:
    def __init__(self,l):
        self.adj=[[] for _ in range(l)]
        self.start={*range(1,l)}
    def add(self,i,j):
        self.adj[i].append(j)
        self.start.discard(j)
    def routes(self):
        for i in self.start:
            r=[i]
            while self.adj[r[-1]]:
                r.append(self.adj[r[-1]].pop())
            yield r

def node_disjoint(adj):
    l=len(adj)
    con=Connect(l)
    for i,j in maximum_matching([(i,j+l) for i in range(1,len(adj)) for j in adj[i]]):
        con.add(i,j-l)
    return con.routes()

def general(adj):
    l=len(adj)
    adj2=[[0]*l for _ in range(l)]
    for i in range(1,len(adj)):
        for j in adj[i]:
            adj2[i][j]=1
    distance=floyd_warshall(adj2)
    con=Connect(l)
    for i,j in maximum_matching([(i,j+l) for i in range(1,l) for j in range(1,l) if 0<distance[i][j]<INF]):
        j-=l
        while distance[i][j]>1:
            k=next(k for k in range(1,l) if distance[k][j]==distance[i][j]-1)
            con.add(i,k)
            i=k
        con.add(i,j)
    return con.routes()

class Test(unittest.TestCase):
    def assertNodeDisjoint(self,adj,l):
        with self.subTest(adj=adj):
            ret=[*node_disjoint(adj)]
            self.assertEqual(len(ret),l)
            self.assertCountEqual((a for r in ret for a in r), range(1,len(adj)))
            for r in ret:
                for a,b in pairwise(r):
                    self.assertIn(b,adj[a])
    def assertGeneral(self,adj,l):
        with self.subTest(adj=adj):
            ret=[*general(adj)]
            self.assertEqual(len(ret),l)
            self.assertCountEqual(set(a for r in ret for a in r), range(1,len(adj)))
            for r in ret:
                for a,b in pairwise(r):
                    self.assertIn(b,adj[a])
    def test(self):
        adj=[[],[2],[]]
        self.assertNodeDisjoint(adj,1)
        self.assertGeneral(adj,1)

        adj=[[],[5],[6],[4],[],[6],[3,7],[]]
        self.assertNodeDisjoint(adj,3)
        self.assertGeneral(adj,2)

if __name__=='__main__':
    unittest.main()
