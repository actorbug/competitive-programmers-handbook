import unittest
from heapq import heappush,heappop
from collections import deque
from graphlib import TopologicalSorter
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
    q=[(-1,-1,x,-1)]
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

def delweight(adj):
    return [[b for b,_ in e] for e in adj]

class CoinProblem:
    def __init__(self,coins,x):
        self.coins=coins
        self.x=x
    def __len__(self):
        return self.x+1
    def __getitem__(self,i):
        if i<0 or self.x<i:
            raise IndexError()
        return (i+c for c in self.coins if i+c<=self.x)

def bfs(adj,x,y):
    q=deque([x])
    parent=[None]*len(adj)
    while q:
        s=q.popleft()
        if s==y:
            ret=[s]
            while (s:=parent[s]) is not None:
                ret.append(s)
            return reversed(ret)
        for u in adj[s]:
            if parent[u] is not None:
                continue
            parent[u]=s
            q.append(u)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(count_path([[]],0,0),1)
        self.assertEqual(count_path([[1,3],[2],[5],[4],[1,2],[]],0,5),3)
        self.assertEqual(count_path(delweight(dijkstra([[]],0)),0,0),1)
        self.assertEqual(count_path(delweight(dijkstra([[(1,3),(2,5)],[(0,3),(2,2),(3,4),(4,8)],[(0,5),(1,2),(3,2)],[(1,4),(2,2),(4,1)],[(1,8),(3,1)]],0)),0,4),3)
        cp=CoinProblem([],0)
        self.assertEqual([*bfs(cp,0,0)],[0])
        self.assertEqual(count_path(cp,0,0),1)
        cp=CoinProblem([1,3,4],6)
        self.assertSequenceEqual([*bfs(cp,0,6)],[0,3,6])
        self.assertEqual(count_path(cp,0,6),9)

if __name__=='__main__':
    unittest.main()
