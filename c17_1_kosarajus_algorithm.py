import unittest

def kosaraju(adj):
    n=len(adj)
    visited=[False]*n
    nodes=[]
    for x in range(n):
        if not visited[x]:
            nodes+=dfs(adj,x,visited)
    radj=reversed_adj(adj)
    visited=[False]*n
    count=0
    ret=[None]*n
    for x in reversed(nodes):
        if not visited[x]:
            for u in dfs(radj,x,visited):
                ret[u]=count
            count+=1
    return ret

def dfs(adj,s,visited):
    if visited[s]:
        return
    visited[s]=True
    for u in adj[s]:
        yield from dfs(adj,u,visited)
    yield s

def reversed_adj(adj):
    radj=[[] for _ in adj]
    for i,e in enumerate(adj):
        for j in e:
            radj[j].append(i)
    return radj

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(kosaraju([]),[])
        self.assertEqual(kosaraju([[1,3],[0,4],[1,6],[],[3],[2,4],[5]]),[1,1,0,3,2,0,0])

if __name__=='__main__':
    unittest.main()
