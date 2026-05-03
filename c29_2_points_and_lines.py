import unittest
from math import isclose
from itertools import pairwise

def inner_product(a,b):
    return (a.conjugate()*b).real

def cross_product(a,b):
    return (a.conjugate()*b).imag

def point_location(s1,s2,p):
    return cross_product(p-s1,p-s2)

def line_segment_intersection(a,b,c,d):
    abc=point_location(a,b,c)
    abd=point_location(a,b,d)
    cda=point_location(c,d,a)
    cdb=point_location(c,d,b)
    if all((isclose(abc,0),isclose(abd,0),isclose(cda,0),isclose(cdb,0))):
        ab=inner_product(b-a,b-a)
        ac=inner_product(b-a,c-a)
        ad=inner_product(b-a,d-a)
        return not(ac<0 and ad<0 or ac>ab and ad>ab)
    else:
        return abc*abd<=0 and cda*cdb<=0

def point_distance_from_a_line(s1,s2,p):
    return cross_product(s1-p,s2-p)/abs(s2-s1)

def point_inside_a_polygon(p,a):
    b=complex(0,1_000_000_000)
    return sum(1 for s1,s2 in pairwise(p) if line_segment_intersection(a,b,s1,s2))%2==1

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(inner_product(4+2j,1+2j),8)
        self.assertEqual(cross_product(4+2j,1+2j),6)

        self.assertGreater(point_location(0+0j,2+2j,0+2j),0)
        self.assertEqual(point_location(0+0j,2+2j,1+1j),0)
        self.assertLess(point_location(0+0j,2+2j,2+0j),0)

        self.assertTrue(line_segment_intersection(0+0j,2+2j,0+2j,2+0j))
        self.assertTrue(line_segment_intersection(0+0j,2+2j,2+2j,3+1j))
        self.assertTrue(line_segment_intersection(0+0j,2+2j,1+1j,3+3j))
        self.assertFalse(line_segment_intersection(0+0j,3+3j,3+0j,2+1j))
        self.assertFalse(line_segment_intersection(0+0j,1+1j,2+2j,3+3j))
        self.assertFalse(line_segment_intersection(3+3j,2+2j,1+1j,0+0j))

        self.assertEqual(point_distance_from_a_line(0+0j,2+0j,1+1j),1)

        p=[1+1j,-1+1j,-1-1j,1-1j,1+1j]
        self.assertFalse(point_inside_a_polygon(p,2+0j))
        self.assertTrue(point_inside_a_polygon(p,0+0j))
        self.assertFalse(point_inside_a_polygon(p,-2+0j))

if __name__=='__main__':
    unittest.main()
