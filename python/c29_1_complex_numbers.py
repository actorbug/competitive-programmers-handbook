import unittest
from cmath import phase,rect

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual((3+1j)+(2+2j),5+3j)
        self.assertAlmostEqual(abs((3-1j-(4+2j))),3.16228,5)
        v=4+2j
        self.assertAlmostEqual(phase(v),0.463648,6)
        v*=rect(1.0,0.5)
        self.assertAlmostEqual(phase(v),0.963648,6)

if __name__=='__main__':
    unittest.main()
