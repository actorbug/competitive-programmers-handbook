import unittest
from heapq import heapify,heappush,heappop

def prim(adj):
    if not adj:
        return []
    processed=[False]*len(adj)
    ret=[[] for _ in adj]
    processed[0]=True
    q=[(w,0,c) for c,w in adj[0]]
    heapify(q)
    while q:
        w,a,b=heappop(q)
        if processed[b]:
            continue
        processed[b]=True
        ret[a].append((b,w))
        ret[b].append((a,w))
        for c,w in adj[b]:
            heappush(q,(w,b,c))
    return ret

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(prim([]),[])
        self.assertEqual([*map(set,prim([
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
