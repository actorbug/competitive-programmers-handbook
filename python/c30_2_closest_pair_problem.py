import unittest
from bisect import bisect_left
from c09_2_binary_indexed_tree import BIT

class SortedY:
    def __init__(self,points):
        self.p=points
        self.b=BIT(len(points))
    def add(self,i):
        self.b.add(i+1,1)
    def remove(self,i):
        self.b.add(i+1,-1)
    def range(self,l,r):
        i=bisect_left(self.p,l,key=lambda i:i.imag)
        i=self.b.lower_bound(i+1)
        while i<=len(self.p) and self.p[i-1].imag<=r:
            yield i-1
            i=self.b.lower_bound(i+1)

def closest_pair(points):
    points=sorted(points,key=lambda p:(p.imag,p.real))
    px=sorted(range(len(points)),key=lambda i:(points[i].real,points[i].imag))
    py=SortedY(points)
    py.add(px[0])
    py.add(px[1])
    i,d,r=0,abs(points[px[0]]-points[px[1]]),(px[0],px[1])
    for j in range(2,len(px)):
        while i<j and points[px[i]].real<points[px[j]].real-d:
            py.remove(px[i])
            i+=1
        for l in py.range(points[px[j]].imag-d,points[px[j]].imag+d):
            d1=abs(points[l]-points[px[j]])
            if d>d1:
                d,r=d1,(l,px[j])
        py.add(px[j])
    return points[r[0]],points[r[1]]

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(closest_pair((0,0)),(0,0))
        self.assertEqual(closest_pair((3j,1+1j,1+6j,3+5j,4+1j,5+5j,6+2j,7+0j,8+2j,9+4j,10+3j,11+1j,14+2j,16+3j)),(9+4j,10+3j))

if __name__=='__main__':
    unittest.main()
