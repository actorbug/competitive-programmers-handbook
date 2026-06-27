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
        self.assertEqual(dijkstra([[],[]],1),[INF,0])
        self.assertEqual(dijkstra([[],[(2,5),(4,9),(5,1)],[(1,5),(3,2)],[(2,2),(4,6)],[(1,9),(3,6),(5,2)],[(1,1),(4,2)]],1),[INF,0,5,7,3,1])

if __name__=='__main__':
    unittest.main()
