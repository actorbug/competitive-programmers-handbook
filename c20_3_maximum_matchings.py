import unittest
from functools import reduce
from operator import or_
from c20_1_ford_fulkerson_algorithm import ford_fulkerson

def maximum_matching(edges):
    l=max(max(s,e) for s,e in edges)+1
    adj=[[] for _ in range(l+2)]
    for s,e in edges:
        adj[l].append((s,1))
        adj[s].append((e,1))
        adj[e].append((l+1,1))
    adj2=ford_fulkerson(adj,l,l+1)
    for s,e in edges:
        if adj2[s][e]==0:
            yield s,e

def halls_theorem(edges):
    ns=[[*set(n)] for n in zip(*edges)]
    l=max(max(i) for i in ns)+1
    adj=[set() for _ in range(l)]
    for s,e in edges:
        adj[s].add(e)
    for b in range(1,1<<len(ns[0])):
        s=[ns[0][i] for i in range(len(ns[0])) if b&(1<<i)]
        if len(s)>len(reduce(or_,(adj[i] for i in s))):
            return False
    return True

class Test(unittest.TestCase):
    def test(self):
        edges=[(0,1)]
        self.assertEqual(len([*maximum_matching(edges)]),1)
        self.assertTrue(halls_theorem(edges))

        edges=[(0,4),(1,6),(2,4),(2,5),(2,7),(3,6)]
        self.assertEqual(len([*maximum_matching(edges)]),3)
        self.assertFalse(halls_theorem(edges))

if __name__=='__main__':
    unittest.main()
