import unittest
from heapq import heappush,heappop

INF=1<<63

def dijkstra(adj,x):
    distance=[INF]*len(adj)
    distance[x]=0
    q=[(0,x)]
    while q:
        m,a=heappop(q)
        if distance[a]<m:
            continue
        for b,w in adj[a]:
            if distance[a]+w<distance[b]:
                distance[b]=distance[a]+w
                heappush(q,(distance[b],b))
    return distance

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(dijkstra([[]],0),[0])
        self.assertEqual(dijkstra([[(1,5),(3,9),(4,1)],[(0,5),(2,2)],[(1,2),(3,6)],[(0,9),(2,6),(4,2)],[(0,1),(3,2)]],0),[0,5,7,3,1])

if __name__=='__main__':
    unittest.main()
