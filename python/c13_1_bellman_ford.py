import unittest
from collections import deque

INF=1<<63

def bellman_ford(adj,x):
    n=len(adj)
    distance=[INF]*n
    distance[x]=0
    for _ in range(n-1):
        changed=False
        for a in range(1,n):
            for b,w in adj[a]:
                if distance[b]>distance[a]+w:
                    distance[b]=distance[a]+w
                    changed=True
        if not changed:
            return distance
    return None

class UniqueQueue:
    def __init__(self,a=()):
        self.q=deque(a)
        self.s=set(self.q)
    def append(self,v):
        if v not in self.s:
            self.q.append(v)
            self.s.add(v)
    def popleft(self):
        v=self.q.popleft()
        self.s.remove(v)
        return v
    def __len__(self):
        return len(self.q)

def spfa(adj,x):
    n=len(adj)
    q=UniqueQueue([x])
    distance=[INF]*n
    distance[x]=0
    len_=[0]*n
    while q:
        s=q.popleft()
        for u,w in adj[s]:
            if distance[u]>distance[s]+w:
                len_[u]=len_[s]+1
                if len_[u]>=n-1:
                    return None
                distance[u]=distance[s]+w
                q.append(u)
    return distance

class Test(unittest.TestCase):
    def test(self):
        for d in (bellman_ford,spfa):
            with self.subTest(d=d):
                self.assertEqual(d([[],[]],1),[INF,0])
                self.assertEqual(d([[],[(2,5),(3,3),(4,7)],[(1,5),(4,3),(5,2)],[(1,3),(4,1)],[(1,7),(2,3),(3,1),(5,2)],[(2,2),(4,2)]],1),[INF,0,5,3,4,6])
                self.assertIsNone(d([[],[(2,3),(3,5)],[(1,3),(3,2),(4,1)],[(1,5),(2,2),(4,-7)],[(2,1),(3,-7)]],1))

if __name__=='__main__':
    unittest.main()
