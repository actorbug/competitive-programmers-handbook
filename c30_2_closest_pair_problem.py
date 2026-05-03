import unittest
from bisect import bisect_left,insort

def asc_x(p):
    return p.real,p.imag

def asc_y(p):
    return p.imag,p.real

def closest_pair(points):
    points=sorted(points,key=asc_x)
    b=sorted([points[0],points[1]],key=asc_y)
    i,d,r=0,abs(points[0]-points[1]),(points[0],points[1])
    for j in range(2,len(points)):
        while i<j and points[i].real<points[j].real-d:
            del b[bisect_left(b,asc_y(points[i]),key=asc_y)]
            i+=1
        l=bisect_left(b,(points[j].imag-d,points[j].real-d),key=asc_y)
        while l<len(b) and b[l].imag<=points[j].imag+d:
            d1=abs(b[l]-points[j])
            if d>d1:
                d,r=d1,(b[l],points[j])
            l+=1
        insort(b,points[j],key=asc_y)
    return r

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(closest_pair((0,0)),(0,0))
        self.assertEqual(closest_pair((3j,1+1j,1+6j,3+5j,4+1j,5+5j,6+2j,7+0j,8+2j,9+4j,10+3j,11+1j,14+2j,16+3j)),(9+4j,10+3j))

if __name__=='__main__':
    unittest.main()
