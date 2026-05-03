import unittest

class UnionFind:
    def __init__(self,n):
        self.parents=[-1]*n
    def find(self,x):
        if self.parents[x]<0:
            return x
        self.parents[x]=self.find(self.parents[x])
        return self.parents[x]
    def same(self,a,b):
        return self.find(a)==self.find(b)
    def unite(self,a,b):
        a,b=self.find(a),self.find(b)
        if self.parents[a]>self.parents[b]:
            a,b=b,a
        self.parents[a]+=self.parents[b]
        self.parents[b]=a

class Test(unittest.TestCase):
    def test(self):
        uf=UnionFind(8)
        uf.unite(3,0)
        uf.unite(3,6)
        uf.unite(1,2)
        uf.unite(2,5)
        uf.unite(2,7)
        self.assertFalse(uf.same(3,1))
        self.assertEqual(uf.find(3),3)
        uf.unite(3,1)
        self.assertTrue(uf.same(3,1))
        self.assertEqual(uf.find(3),1)

if __name__=='__main__':
    unittest.main()
