import unittest
from c09_1_static_array_queries import MinimumQueries

class Doubling:
    def __init__(self,adj):
        n=len(adj)
        self.d=[None]*n
        f=[-1]*(n+1)
        def dfs(s,e,d):
            f[s]=e
            self.d[s]=d
            for u in adj[s]:
                if u!=e:
                    dfs(u,s,d+1)
        dfs(0,-1,1)
        self.a=[f]
        for _ in range((n-1).bit_length()-1):
            f=[f[i] for i in f]
            self.a.append(f)
    def ancestor(self,x,k):
        for f in self.a:
            if k&1:
                x=f[x]
            k>>=1
        return x if k<=0 else -1
    def __call__(self,a,b):
        if self.d[a]<self.d[b]:
            a,b=b,a
        a=self.ancestor(a,self.d[a]-self.d[b])
        if a==b:
            return a
        for f in reversed(self.a):
            if f[a]!=f[b]:
                a,b=f[a],f[b]
        return self.a[0][a]
    def distance(self,a,b):
        return self.d[a]+self.d[b]-2*self.d[self(a,b)]

class Euler:
    def __init__(self,adj):
        self.p=[None]*len(adj)
        depth=[]
        def dfs(s,e,d):
            self.p[s]=len(depth)
            depth.append((d,s))
            for u in adj[s]:
                if u!=e:
                    dfs(u,s,d+1)
                    depth.append((d,s))
        dfs(0,-1,1)
        self.d=MinimumQueries(depth)
    def __call__(self,a,b):
        return self.d(*sorted((self.p[a],self.p[b])))[1]
    def distance(self,a,b):
        pa,pb,pc=self.p[a],self.p[b],self.p[self(a,b)]
        return self.d(pa,pa)[0]+self.d(pb,pb)[0]-2*self.d(pc,pc)[0]

class Test(unittest.TestCase):
    def test(self):
        for A in (Doubling,Euler):
            with self.subTest(A=A):
                a=A([[]])
                self.assertEqual(a(0,0),0)
                self.assertEqual(a.distance(0,0),0)
                a=A([[1,2,3],[4,5],[],[6],[],[7],[],[]])
                self.assertEqual(a(4,7),1)
                self.assertEqual(a.distance(4,7),3)

if __name__=='__main__':
    unittest.main()
