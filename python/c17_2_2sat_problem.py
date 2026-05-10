import unittest
from c17_1_kosarajus_algorithm import kosaraju

class TwoSatProblem:
    def __init__(self,n):
        self.adj=[[] for _ in range(n*2)]
    def add(self,i,f,j,g):
        v0,v1=i*2+f,j*2+g
        self.adj[v0^1].append(v1)
        self.adj[v1^1].append(v0)
    def solve(self):
        connect=kosaraju(self.adj)
        ret=[False]*(len(self.adj)//2)
        for i in range(len(ret)):
            if connect[i*2]==connect[i*2+1]:
                return None
            ret[i]=connect[i*2+1]>connect[i*2]
        return ret

class Test(unittest.TestCase):
    def test(self):
        ts=TwoSatProblem(1)
        ts.add(0,True,0,True)
        self.assertEqual(ts.solve(),[True])
        ts=TwoSatProblem(4)
        ts.add(1,True,0,False)
        ts.add(0,False,1,False)
        ts.add(0,True,2,True)
        ts.add(1,False,2,False)
        ts.add(0,True,3,True)
        self.assertEqual(ts.solve(),[False,False,True,True])
        ts=TwoSatProblem(3)
        ts.add(0,True,1,True)
        ts.add(0,True,1,False)
        ts.add(0,False,2,True)
        ts.add(0,False,2,False)
        self.assertIsNone(ts.solve())

if __name__=='__main__':
    unittest.main()
