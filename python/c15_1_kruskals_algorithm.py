import unittest
from c15_2_union_find_structure import UnionFind
from c12_3_applications import connected

def kruskal(adj):
    ret=[[] for _ in adj]
    uf=UnionFind(len(adj))
    for w,a,b in sorted((w,a,b) for a,e in enumerate(adj) for b,w in e):
        if not uf.same(a,b):
            uf.unite(a,b)
            ret[a].append((b,w))
            ret[b].append((a,w))
    return ret

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(kruskal([]),[])
        ret=kruskal([
            [(1,3),(4,5)],
            [(0,3),(2,5),(4,6)],
            [(1,5),(3,9),(5,3)],
            [(2,9),(5,7)],
            [(0,5),(1,6),(5,2)],
            [(2,3),(3,7),(4,2)]
        ])
        self.assertEqual(sum(j[1] for i in ret for j in i),20*2)
        self.assertEqual(len([*connected([[j[0] for j in i] for i in ret])]),1)

if __name__=='__main__':
    unittest.main()
