import unittest
from c09_3_segment_tree import SegTree

class SegTree2D:
    def __init__(self,array):
        n=2**max(len(array)-1,0).bit_length()
        self.tree=[None]*n+[*map(SegTree,array)]+[SegTree(len(array[0]))]*(n-len(array))
        for i in range(n-1,0,-1):
            self.tree[i]=SegTree.__new__(SegTree)
            self.tree[i].tree=[a+b for a,b in zip(self.tree[2*i].tree,self.tree[2*i+1].tree)]
    def sum(self,xa,xb,ya,yb):
        ya+=len(self.tree)//2
        yb+=len(self.tree)//2
        s=0
        while ya<=yb:
            if ya%2==1:
                s+=self.tree[ya].sum(xa,xb)
                ya+=1
            if yb%2==0:
                s+=self.tree[yb].sum(xa,xb)
                yb-=1
            ya//=2
            yb//=2
        return s
    def add(self,x,y,v):
        y+=len(self.tree)//2
        while y>=1:
            self.tree[y].add(x,v)
            y//=2

class Test(unittest.TestCase):
    def test(self):
        s=SegTree2D([[7,6,1,6],[8,7,5,2],[3,9,7,1],[8,5,3,8]])
        self.assertEqual(s.sum(1,2,1,2),28)

if __name__=='__main__':
    unittest.main()
