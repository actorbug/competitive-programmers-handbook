import unittest
from collections import defaultdict
from util import reversed_adj
import sys
from itertools import pairwise

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def existence(adj):
    odd=[]
    for i,e in enumerate(adj):
        if len(e)%2==1:
            odd.append(i)
    if len(odd)==0:
        return [-1,-1]
    elif len(odd)==2:
        return odd
    else:
        return None

def existence2(adj,rev=None):
    if rev is None:
        rev=reversed_adj(adj)
    d=defaultdict(list)
    for e,(i,o) in enumerate(zip(rev,adj)):
        d[len(i)-len(o)].append(e)
    if len(d[0])==len(adj):
        return (-1,-1)
    elif len(d[0])==len(adj)-2 and len(d[1])==1:
        return (d[-1][0],d[1][0])
    else:
        return None

def hierhorzer(adj):
    e=existence(adj)
    if e is None or not adj:
        return ()
    adj=[*map(set,adj)]
    def dfs(s):
        while adj[s]:
            u=next(iter(adj[s]))
            adj[s].remove(u)
            adj[u].remove(s)
            yield from dfs(u)
        yield s
    return dfs(max(0,e[1]))

def hierhorzer2(adj):
    rev=reversed_adj(adj)
    e=existence2(adj,rev)
    if not e or not adj:
        return ()
    def dfs(s):
        while rev[s]:
            yield from dfs(rev[s].pop())
        yield s
    return dfs(max(0,e[1]))


class Test(unittest.TestCase):
    def assertHierhorzer(self,adj):
        with self.subTest(adj=adj):
            adj2=[[] for _ in adj]
            for i,j in pairwise(hierhorzer(adj)):
                adj2[i].append(j)
                adj2[j].append(i)
            for i,j in zip(adj,adj2):
                self.assertEqual(sorted(i), sorted(j))
    def assertHierhorzer2(self,adj):
        with self.subTest(adj=adj):
            adj2=[[] for _ in adj]
            for i,j in pairwise(hierhorzer2(adj)):
                adj2[i].append(j)
            for i,j in zip(adj,adj2):
                self.assertEqual(sorted(i), sorted(j))
    def test(self):
        adj1=[[1,3],[0,2,4],[1,4],[0,4],[1,2,3]]
        adj2=[[1,3],[0,2,3,4],[1,4],[0,1],[1,2]]

        self.assertEqual(existence([]),[-1,-1])
        self.assertCountEqual(existence(adj1),[1,4])
        self.assertEqual(existence(adj2),[-1,-1])
        self.assertIsNone(existence([[1,2,3],[0,2,3],[0,1,3],[0,1,2]]))

        adj3=[[1],[2,4],[4],[0],[3]]
        adj4=[[3],[0,4],[1],[1],[2]]

        self.assertEqual(existence2([]),(-1,-1))
        self.assertEqual(existence2(adj3),(1,4))
        self.assertEqual(existence2(adj4),(-1,-1))
        self.assertIsNone(existence2([[1,2,3],[2,3],[3],[]]))

        self.assertHierhorzer([])
        self.assertHierhorzer(adj1)
        self.assertHierhorzer(adj2)
        self.assertHierhorzer([[1,2],[0,2,4,5],[0,1,3,5],[2,6],[1,5],[1,2,4,6],[3,5]])

        self.assertHierhorzer2([])
        self.assertHierhorzer2(adj3)
        self.assertHierhorzer2(adj4)
        self.assertHierhorzer2([[1],[2,4],[0,3],[6],[5],[1,2],[5]])

if __name__=='__main__':
    unittest.main()
