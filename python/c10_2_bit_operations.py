import unittest

def checkbit(x,k):
    return x&(1<<k)
def setbit(x,k,b):
    return x|(1<<k) if b else x&~(1<<k)
def invertbit(x,k):
    return x^(1<<k)
def resetlastbit(x):
    return x&(x-1)
def getlastbit(x):
    return x&-x
def invertafterlastbit(x):
    return x|(x-1)
def is2n(x):
    return resetlastbit(x)==0

def clz(x):
    return 32-x.bit_length() if x>=0 else 0
def ctz(x):
    return getlastbit(x).bit_length()-1 if x!=0 else 32
def popcount(x):
    return x.bit_count()
def parity(x):
    return x.bit_count()%2

class Test(unittest.TestCase):
    def test(self):
        self.assertTrue(checkbit(0b1100,2))
        self.assertFalse(checkbit(0b1000,2))
        self.assertEqual(setbit(0b1000,2,1),0b1100)
        self.assertEqual(setbit(0b1100,2,0),0b1000)
        self.assertEqual(invertbit(0b1100,2),0b1000)
        self.assertEqual(invertbit(0b1000,2),0b1100)
        self.assertEqual(resetlastbit(0b1100),0b1000)
        self.assertEqual(getlastbit(0b1100),0b100)
        self.assertEqual(invertafterlastbit(0b1100),0b1111)
        self.assertTrue(is2n(0b1000))
        self.assertFalse(is2n(0b1100))

        x=0b_0000_0000_0000_0000_0001_0100_1101_0000
        self.assertEqual(clz(x),19)
        self.assertEqual(ctz(x),4)
        self.assertEqual(popcount(x),5)
        self.assertEqual(parity(x),1)

if __name__=='__main__':
    unittest.main()
