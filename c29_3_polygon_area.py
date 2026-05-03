import unittest
from math import fsum,isclose,ceil,floor
from itertools import pairwise
from c29_2_points_and_lines import inner_product,cross_product,point_location,point_inside_a_polygon

def shoelace_formula(p):
    return abs(fsum(cross_product(p,q) for p,q in pairwise(p)))/2

def polygon_border(p,a):
    for s1,s2 in pairwise(p):
        if isclose(point_location(s1,s2,a),0):
            if 0<=inner_product(s2-s1,a-s1)<=abs(s2-s1)**2:
                return True
    return False

def picks_theorem(p):
    a=b=0
    ymin,ymax=ceil(min(i.imag for i in p)),floor(max(i.imag for i in p))
    xmin,xmax=ceil(min(i.real for i in p)),floor(max(i.real for i in p))
    for y in range(ymin,ymax+1):
        for x in range(xmin,xmax+1):
            if polygon_border(p,complex(x,y)):
                b+=1
            elif point_inside_a_polygon(p,complex(x,y)):
                a+=1
    return a+b/2-1

class Test(unittest.TestCase):
    def test(self):
        p=[2+4j,5+5j,7+3j,4+1j,4+3j,2+4j]
        self.assertEqual(shoelace_formula(p),17/2)
        self.assertEqual(picks_theorem(p),17/2)

if __name__=='__main__':
    unittest.main()
