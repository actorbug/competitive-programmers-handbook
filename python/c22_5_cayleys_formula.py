import unittest
from itertools import product
from heapq import heapify,heappush,heappop

def prufre2tree(a):
    n=len(a)+2
    adj=[[] for _ in range(n)]
    degree=[1]*n
    for i in a:
        degree[i]+=1
    q=[i for i in range(n) if degree[i]==1]
    heapify(q)
    for i in a:
        j=heappop(q)
        adj[i].append(j)
        adj[j].append(i)
        degree[i]-=1
        if degree[i]==1:
            heappush(q,i)
        degree[j]-=1
        if degree[j]==1:
            heappush(q,j)
    i,j=q
    adj[i].append(j)
    adj[j].append(i)
    return adj

def cayley(n):
    for i in product(range(n),repeat=n-2):
        yield prufre2tree(i)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual([*map(sorted,prufre2tree([3,3,1]))],[[3],[3,4],[3],[0,1,2],[1]])
        self.assertCountEqual(([*map(sorted,c)] for c in cayley(4)),[
            [[1,2,3],[0],[0],[0]],
            [[1],[0,2,3],[1],[1]],
            [[2],[2],[0,1,3],[2]],
            [[3],[3],[3],[0,1,2]],
            [[1],[0,2],[1,3],[2]],
            [[1],[0,3],[3],[1,2]],
            [[2],[2,3],[0,1],[1]],
            [[2],[3],[0,3],[1,2]],
            [[3],[2,3],[1],[0,1]],
            [[3],[2],[1,3],[0,2]],
            [[1,2],[0],[0,3],[2]],
            [[1,3],[0],[3],[0,2]],
            [[2,3],[2],[0,1],[0]],
            [[2,3],[3],[0],[0,1]],
            [[1,2],[0,3],[0],[1]],
            [[1,3],[0,2],[1],[0]]
        ])

if __name__=='__main__':
    unittest.main()
