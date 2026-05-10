import unittest
from collections import Counter,defaultdict
from c15_2_union_find_structure import UnionFind
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def merging(adj,val,x,q):
    a=[None]*len(q)
    r=defaultdict(list)
    for i,(p,_) in enumerate(q):
        r[p].append(i)
    d=[Counter([v]) for v in val]
    def dfs(s,e):
        for u in adj[s]:
            if u!=e:
                dfs(u,s)
                if len(d[u])>len(d[s]):
                    d[u],d[s]=d[s],d[u]
                d[s].update(d[u])
        for i in r[s]:
            a[i]=d[s][q[i][1]]
    dfs(x,-1)
    return a

def lca(adj,x,q):
    a=[None]*len(q)
    r=defaultdict(list)
    for i,(j,k) in enumerate(q):
        r[j].append((i,k))
        r[k].append((i,j))
    n=len(adj)
    uf=UnionFind(n)
    value=[*range(n)]
    visited=[False]*n
    def dfs(s,e):
        for i,k in r[s]:
            if visited[k]:
                a[i]=value[uf.find(k)]
        visited[s]=True
        for u in adj[s]:
            if u!=e:
                dfs(u,s)
                v=value[uf.find(s)]
                uf.unite(u,s)
                value[uf.find(u)]=v
    dfs(x,-1)
    return a

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(merging([[]],[3],0,[]),[])
        self.assertEqual(merging([[1,2,3,4],[0,5],[0],[0,6,7,8],[0],[1],[3],[3],[3]],[2,3,5,3,1,4,4,3,1],0,[(3,3)]),[2])

        self.assertEqual(lca([[]],0,[]),[])
        self.assertEqual(lca([[1,2,3],[0,4,5],[0],[0,6],[1],[1,7],[3],[5]],0,[(4,7),(1,6)]),[1,0])

if __name__=='__main__':
    unittest.main()
