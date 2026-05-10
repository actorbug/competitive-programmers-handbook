import unittest
from c15_2_union_find_structure import UnionFind

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
        self.assertEqual([*map(set,kruskal([
            [(1,3),(4,5)],
            [(0,3),(2,5),(4,6)],
            [(1,5),(3,9),(5,3)],
            [(2,9),(5,7)],
            [(0,5),(1,6),(5,2)],
            [(2,3),(3,7),(4,2)]
        ]))],[
            {(1,3),(4,5)},
            {(0,3)},
            {(5,3)},
            {(5,7)},
            {(0,5),(5,2)},
            {(2,3),(3,7),(4,2)}
        ])

if __name__=='__main__':
    unittest.main()
