import unittest
from c29_2_points_and_lines import point_location

def andrew(points):
    if len(points)<2:
        return points
    points=sorted(points,key=lambda p:(p.real,p.imag))
    upper=points[:2]
    for i in range(2,len(points)):
        upper.append(points[i])
        while len(upper)>2 and point_location(*upper[-3:])>=0:
            del upper[-2]
    lower=points[-1:-3:-1]
    for i in range(len(points)-3,-1,-1):
        lower.append(points[i])
        while len(lower)>2 and point_location(*lower[-3:])>=0:
            del lower[-2]
    return upper[:-1]+lower[:-1]

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(andrew([]),[])
        self.assertEqual(andrew([0]),[0])
        self.assertEqual(andrew([0,1]),[0,1])
        self.assertEqual(andrew([0,1,1+1j]),[0,1+1j,1])
        self.assertEqual(andrew([0,1,2]),[0,2])
        self.assertEqual(andrew([0+1j,0+3j,1+2j,2+3j,2+5j,3+3j,4+0j,4+1j,4+4j,5+3j,6+2j,6+4j,7+2j]),[0+1j,0+3j,2+5j,6+4j,7+2j,4+0j])

if __name__=='__main__':
    unittest.main()
