import unittest
from heapq import heappush,heappop
from collections import deque
from graphlib import TopologicalSorter
from util import delweight
INF=1<<63

def count_path(adj,a,b):
    paths=[0]*len(adj)
    paths[a]=1
    t=TopologicalSorter()
    for i,e in enumerate(adj):
        for j in e:
            t.add(j,i)
    for s in t.static_order():
        for u in adj[s]:
            paths[u]+=paths[s]
    return paths[b]

def dijkstra(adj,x):
    n=len(adj)
    processed=[False]*n
    q=[(-1,0,x,-1)]
    ret=[[] for _ in adj]
    distance=[INF]*n
    distance[x]=0
    while q:
        d,a,b,w=heappop(q)
        if d==distance[b]:
            ret[a].append((b,w))
        if processed[b]:
            continue
        processed[b]=True
        for c,w in adj[b]:
            if distance[b]+w<=distance[c]:
                distance[c]=distance[b]+w
                heappush(q,(distance[c],b,c,w))
    return ret

class CoinProblem:
    def __init__(self,coins,x):
        self.coins=coins
        self.x=x
    def __len__(self):
        return self.x+2
    def __getitem__(self,i):
        if i==0:
            return ()
        if i<0 or self.x+1<i:
            raise IndexError()
        return (i+c for c in self.coins if i+c<=self.x+1)

def bfs(adj,x,y):
    q=deque([x])
    distance=[-1]*len(adj)
    distance[x]=0
    while q:
        s=q.popleft()
        if s==y:
            return distance[s]
        for u in adj[s]:
            if distance[u]>=0:
                continue
            distance[u]=distance[s]+1
            q.append(u)
    return INF

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(count_path([[],[]],1,1),1)
        self.assertEqual(count_path([[],[2,4],[3],[6],[5],[2,3],[]],1,6),3)
        self.assertEqual(count_path(delweight(dijkstra([[],[]],1)),1,1),1)
        self.assertEqual(count_path(delweight(dijkstra([[],[(2,3),(3,5)],[(1,3),(3,2),(4,4),(5,8)],[(1,5),(2,2),(4,2)],[(2,4),(3,2),(5,1)],[(2,8),(4,1)]],1)),1,5),3)
        cp=CoinProblem([],0)
        self.assertEqual(bfs(cp,1,1),0)
        self.assertEqual(count_path(cp,1,1),1)
        cp=CoinProblem([1,3,4],6)
        self.assertEqual(bfs(cp,1,7),2)
        self.assertEqual(count_path(cp,1,7),9)

if __name__=='__main__':
    unittest.main()
