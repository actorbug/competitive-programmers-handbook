import unittest
from util import delweight
from c12_3_applications import connected,finding_cycles
from c15_2_union_find_structure import UnionFind

def kruskal(adj):
    n=len(adj)
    ret=[[] for _ in adj]
    uf=UnionFind(n)
    for w,a,b in sorted((w,a,b) for a in range(1,n) for b,w in adj[a]):
        if not uf.same(a,b):
            uf.unite(a,b)
            ret[a].append((b,w))
            ret[b].append((a,w))
    return ret

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(kruskal([[]]),[[]])
        ret=kruskal([
            [],
            [(2,3),(5,5)],
            [(1,3),(3,5),(5,6)],
            [(2,5),(4,9),(6,3)],
            [(3,9),(6,7)],
            [(1,5),(2,6),(6,2)],
            [(3,3),(4,7),(5,2)]
        ])
        self.assertEqual(sum(w for i in range(1,len(ret)) for _,w in ret[i]),20*2)
        adj=delweight(ret)
        self.assertEqual(len([*connected(adj)]),1)
        self.assertFalse(finding_cycles(adj))

if __name__=='__main__':
    unittest.main()
