import unittest
from copy import deepcopy

INF=1<<63

def floyd_warshall(adj):
    n=len(adj)
    distance=deepcopy(adj)
    for i in range(1,n):
        for j in range(1,n):
            if i!=j and distance[i][j]==0:
                distance[i][j]=INF
    for k in range(1,n):
        for i in range(1,n):
            for j in range(1,n):
                distance[i][j]=min(distance[i][j],distance[i][k]+distance[k][j])
    return distance

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(floyd_warshall([0]),[0])
        self.assertEqual(floyd_warshall([
            [0,0,0,0,0,0],
            [0,0,5,0,9,1],
            [0,5,0,2,0,0],
            [0,0,2,0,7,0],
            [0,9,0,7,0,2],
            [0,1,0,0,2,0]
        ]),[
            [0,0,0,0,0,0],
            [0,0,5,7,3,1],
            [0,5,0,2,8,6],
            [0,7,2,0,7,8],
            [0,3,8,7,0,2],
            [0,1,6,8,2,0]
        ])

if __name__=='__main__':
    unittest.main()
