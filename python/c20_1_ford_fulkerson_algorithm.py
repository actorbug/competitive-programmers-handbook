import unittest
from collections import deque
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def bfs(adj,s,e):
    q=deque([s])
    prev=[-1]*len(adj)
    prev[s]=s
    while q and prev[e]<0:
        i=q.popleft()
        for j,c in adj[i].items():
            if c>0 and prev[j]<0:
                prev[j]=i
                q.append(j)
    return prev

def ford_fulkerson(adj,s,e,find=bfs):
    adj2=[{} for _ in adj]
    for i,a in enumerate(adj):
        for j,c in a:
            adj2[i][j]=c
            adj2[j][i]=0
    while (prev:= find(adj2,s,e))[e]>=0:
        mc=min(adj2[i][j] for i,j in prev2edges(prev,e))
        for i,j in prev2edges(prev,e):
            adj2[i][j]-=mc
            adj2[j][i]+=mc
    return adj2

def prev2edges(prev,e):
    while e!=prev[e]:
        n,e=e,prev[e]
        yield e,n

def scaling(adj,s,e):
    m=max(c for a in adj for _,c in a)
    def find(adj,s,e):
        nonlocal m
        while m:
            prev=[-1]*len(adj)
            def dfs(i,p):
                if prev[i]>=0:
                    return False
                prev[i]=p
                return i==e or any(dfs(u,i) for u,c in adj[i].items() if c>=m)
            if dfs(s,s):
                break
            m//=2
        return prev
    return ford_fulkerson(adj,s,e,find)

def minimum_cuts(adj,s):
    visited=set()
    stack=[s]
    while stack:
        i=stack.pop()
        if i not in visited:
            visited.add(i)
            stack+=(j for j,c in adj[i].items() if c>0)
    for i in visited:
        for j,_ in adj[i].items():
            if j not in visited:
                yield i,j

def adj2tc(adj,e):
    return sum(adj[e].values())

class Test(unittest.TestCase):
    def assertFlow(self,adj,s,e,f,tc,adj2,cut):
        with self.subTest(adj=adj,s=s,e=e,f=f):
            adj3=f(adj,s,e)
            self.assertEqual(adj3,adj2)
            self.assertEqual(adj2tc(adj3,e),tc)
            self.assertCountEqual(minimum_cuts(adj3,s),cut)
    def test(self):
        for f in (ford_fulkerson,scaling):
            self.assertFlow([[(1,2)],[]],0,1,f,2,[{1:0},{0:2}],[(0,1)])
            self.assertFlow([[(1,5),(3,4)],[(2,6)],[(4,8),(5,5)],[(1,3),(4,1)],[(5,2)],[]],0,5,f,7,[{1:0,3:2},{0:5,2:0,3:1},{1:6,4:7,5:0},{0:2,1:2,4:0},{2:1,3:1,5:0},{2:5,4:2}],[(1,2),(3,4)])

if __name__=='__main__':
    unittest.main()
