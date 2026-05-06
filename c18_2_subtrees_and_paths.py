import unittest
from c09_2_binary_indexed_tree import BIT
from c09_4_additional_techniques import RangeUpdates
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def traversal(adj,x):
    def dfs(s,e):
        yield s
        for u in adj[s]:
            if u!=e:
                yield from dfs(u,s)
    return dfs(x,-1)

class SubtreeQueries:
    def __init__(self,adj,val,x):
        n=len(adj)
        cur=0
        self.pos=[None]*n
        self.size=[None]*n
        def dfs(s,e):
            nonlocal cur
            self.pos[s]=cur
            cur+=1
            size=1
            for u in adj[s]:
                if u!=e:
                    size+=dfs(u,s)
            self.size[self.pos[s]]=size
            return size
        dfs(x,-1)
        self.value=BIT(n)
        for i in range(n):
            self.value.add(self.pos[i]+1,val[i])
    def set(self,k,x):
        self.value[self.pos[k]+1]=x
    def sum(self,k):
        p=self.pos[k]
        return self.value.sum(p+self.size[p])-self.value.sum(p)

class PathQueries:
    def __init__(self,adj,val,x):
        n=len(adj)
        cur=0
        self.pos=[None]*n
        self.size=[None]*n
        self.value=RangeUpdates(n)
        def dfs(s,e,v):
            nonlocal cur
            self.pos[s]=cur
            v+=val[s]
            self.value.add(cur,cur,v)
            cur+=1
            size=1
            for u in adj[s]:
                if u!=e:
                    size+=dfs(u,s,v)
            self.size[self.pos[s]]=size
            return size
        dfs(x,-1,0)
    def add(self,k,x):
        p=self.pos[k]
        self.value.add(p,p+self.size[p],x)
    def sum(self,k):
        return self.value[self.pos[k]]

class Test(unittest.TestCase):
    def test(self):
        adj=[[1,2,3,4],[0,5],[0],[0,6,7,8],[0],[1],[3],[3],[3]]
        self.assertEqual([*traversal([[]],0)],[0])
        self.assertEqual([*traversal(adj,0)],[0,1,5,2,3,6,7,8,4])

        self.assertEqual(SubtreeQueries([[]],[3],0).sum(0),3)
        sq=SubtreeQueries(adj,[2,3,5,3,1,4,4,3,1],0)
        self.assertEqual(sq.sum(3),11)
        sq.set(6,2)
        self.assertEqual(sq.sum(3),9)

        self.assertEqual(PathQueries([[]],[3],0).sum(0),3)
        pq=PathQueries(adj,[4,5,3,5,2,3,5,3,1],0)
        self.assertEqual(pq.sum(6),14)
        pq.add(3,1)
        self.assertEqual(pq.sum(6),15)

if __name__=='__main__':
    unittest.main()
