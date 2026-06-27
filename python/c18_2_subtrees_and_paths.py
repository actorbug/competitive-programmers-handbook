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
    return dfs(x,0)

class SubtreeQueries:
    def __init__(self,adj,val,x):
        n=len(adj)
        cur=1
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
        dfs(x,0)
        self.value=BIT(n)
        for i in range(1,n):
            self.value.add(self.pos[i],val[i])
    def set(self,k,x):
        self.value[self.pos[k]]=x
    def sum(self,k):
        p=self.pos[k]
        return self.value.sum(p+self.size[p]-1)-self.value.sum(p-1)

class PathQueries:
    def __init__(self,adj,val,x):
        n=len(adj)
        cur=0
        self.pos=[None]*n
        self.size=[None]*(n-1)
        self.value=RangeUpdates(n-1)
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
        dfs(x,0,0)
    def add(self,k,x):
        p=self.pos[k]
        self.value.add(p,p+self.size[p]-1,x)
    def sum(self,k):
        return self.value[self.pos[k]]

class Test(unittest.TestCase):
    def test(self):
        adj=[[],[2,3,4,5],[1,6],[1],[1,7,8,9],[1],[2],[4],[4],[4]]
        self.assertEqual([*traversal([[],[]],1)],[1])
        self.assertEqual([*traversal(adj,1)],[1,2,6,3,4,7,8,9,5])

        self.assertEqual(SubtreeQueries([[],[]],[0,3],1).sum(1),3)
        sq=SubtreeQueries(adj,[0,2,3,5,3,1,4,4,3,1],1)
        self.assertEqual(sq.sum(4),11)
        sq.set(7,2)
        self.assertEqual(sq.sum(4),9)

        self.assertEqual(PathQueries([[],[]],[0,3],1).sum(1),3)
        pq=PathQueries(adj,[0,4,5,3,5,2,3,5,3,1],1)
        self.assertEqual(pq.sum(7),14)
        pq.add(4,1)
        self.assertEqual(pq.sum(7),15)
        self.assertEqual(pq.sum(5),6)

if __name__=='__main__':
    unittest.main()
