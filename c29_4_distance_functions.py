import unittest

def max_distance(p):
    x=[(c.real+c.imag,i) for i,c in enumerate(p)]
    y=[(c.imag-c.real,i) for i,c in enumerate(p)]
    minxv,minxi,maxxv,maxxi=*min(x),*max(x)
    minyv,minyi,maxyv,maxyi=*min(y),*max(y)
    if maxxv-minxv>=maxyv-minyv:
        return (p[minxi],p[maxxi],maxxv-minxv)
    else:
        return (p[minyi],p[maxyi],maxyv-minyv)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(max_distance([0+2j,1+0j,3+3j,3+1j]),(1+0j,3+3j,5))
        self.assertEqual(max_distance([2+0j,0+1j,3+3j,1+3j]),(0+1j,3+3j,5))

if __name__=='__main__':
    unittest.main()
