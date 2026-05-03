import unittest

class Ancestor:
    def __init__(self,adj,x):
        n=len(adj)
        f=[-1]*(n+1)
        def dfs(s,e):
            f[s]=e
            for u in adj[s]:
                if u!=e:
                    dfs(u,s)
        dfs(x,-1)
        self.a=[f]
        for _ in range((n-1).bit_length()-1):
            f=[f[i] for i in f]
            self.a.append(f)
    def __call__(self,x,k):
        for f in self.a:
            if k&1:
                x=f[x]
            k>>=1
        return x if k<=0 else -1

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(Ancestor([[]],0)(0,0),0)
        ancestor=Ancestor([[3,4,1],[0,5],[3],[0,2,6],[0],[1],[3,7],[6]],0)
        self.assertEqual(ancestor(1,1),0)
        self.assertEqual(ancestor(7,2),3)

if __name__=='__main__':
    unittest.main()
