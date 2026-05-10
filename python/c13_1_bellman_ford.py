import unittest
from collections import deque

INF=1<<63

def bellman_ford(adj,x):
    n=len(adj)
    distance=[INF]*n
    distance[x]=0
    for _ in range(n):
        changed=False
        for a,e in enumerate(adj):
            for b,w in e:
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
                if len_[u]>=n:
                    return None
                distance[u]=distance[s]+w
                q.append(u)
    return distance

class Test(unittest.TestCase):
    def test(self):
        for d in (bellman_ford,spfa):
            with self.subTest(d=d):
                self.assertEqual(d([[]],0),[0])
                self.assertEqual(d([[(1,5),(2,3),(3,7)],[(0,5),(3,3),(4,2)],[(0,3),(3,1)],[(0,7),(1,3),(2,1),(4,2)],[(1,2),(3,2)]],0),[0,5,3,4,6])
                self.assertIsNone(d([[(1,3),(2,5)],[(0,3),(2,2),(3,1)],[(0,5),(1,2),(3,-7)],[(1,1),(2,-7)]],0))

if __name__=='__main__':
    unittest.main()
