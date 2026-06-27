import unittest
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

class Ancestor:
    def __init__(self,adj,x):
        n=len(adj)
        f=[0]*n
        def dfs(s,e):
            f[s]=e
            for u in adj[s]:
                if u!=e:
                    dfs(u,s)
        dfs(x,0)
        self.a=[f]
        for _ in range((n-2).bit_length()-1):
            f=[f[i] for i in f]
            self.a.append(f)
    def __call__(self,x,k):
        for f in self.a:
            if k&1:
                x=f[x]
            k>>=1
        return x if k<=0 else 0

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(Ancestor([[],[]],1)(1,0),1)
        ancestor=Ancestor([[],[4,5,2],[1,6],[4],[1,3,7],[1],[2],[4,8],[7]],1)
        self.assertEqual(ancestor(2,1),1)
        self.assertEqual(ancestor(8,2),4)
        self.assertEqual(ancestor(8,17),0)

if __name__=='__main__':
    unittest.main()
