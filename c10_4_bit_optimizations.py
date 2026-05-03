import unittest
from itertools import combinations

def hamming(a,b):
    return sum(i!=j for i,j in zip(a,b))

def hamming2(a,b):
    return (a^b).bit_count()

def subgrids(color):
    total=0
    for a,b in combinations(color,2):
        count=sum(i==j==1 for i,j in zip(a,b))
        total+=count*(count-1)//2
    return total

def subgrids2(color):
    total=0
    for a,b in combinations(color,2):
        count=(a&b).bit_count()
        total+=count*(count-1)//2
    return total

class Test(unittest.TestCase):
    def assertHamming(self,x,y,r):
        with self.subTest(x=x,y=y):
            self.assertEqual(hamming(x,y),r)
            self.assertEqual(hamming2(int(x,2) if x else 0,int(y,2) if y else 0),r)
    def assertGrids(self,color,r):
        with self.subTest(color=color):
            self.assertEqual(subgrids(color),r)
            self.assertEqual(subgrids2([int(''.join(map(str,l)),2) for l in color]),r)
    def test(self):
        self.assertHamming('','',0)
        self.assertHamming('00111','01101',2)
        self.assertHamming('00111','11110',3)
        self.assertHamming('01101','11110',3)

        self.assertGrids([[0,1,0,0,1],[0,1,1,0,0],[1,0,0,0,0],[0,1,1,0,1],[0,0,0,0,0]],2)

if __name__=='__main__':
    unittest.main()
