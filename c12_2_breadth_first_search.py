import unittest
from collections import deque

def bfs(adj,x):
    q=deque([x])
    distance=[None]*len(adj)
    distance[x]=0
    while q:
        s=q.popleft()
        yield s,distance[s]
        for u in adj[s]:
            if distance[u] is None:
                distance[u]=distance[s]+1
                q.append(u)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual([*bfs([[]],0)],[(0,0)])
        self.assertEqual([*bfs([[1,3],[0,2,4],[1,5],[0],[1,5],[2,4]],0)],[(0,0),(1,1),(3,1),(2,2),(4,2),(5,3)])

if __name__=='__main__':
    unittest.main()
