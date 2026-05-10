import unittest

def zalgorithm(s):
    n,x,y=len(s),0,0
    z=[0]*n
    for i in range(1,n):
        z[i]=max(0,min(z[i-x],y-i+1))
        while i+z[i]<n and s[z[i]]==s[i+z[i]]:
            x,y=i,i+z[i]
            z[i]+=1
    return z

def find(s,t):
    n=len(t)
    if n <= 0:
        return 0
    try:
        return zalgorithm(t+'#'+s).index(n,n+1)-n-1
    except ValueError:
        return None

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(zalgorithm(''),[])
        self.assertEqual(zalgorithm('ACBACDACBACBACDA'),[0,0,0,2,0,0,5,0,0,7,0,0,2,0,0,1])
        self.assertEqual(find('',''),0)
        self.assertEqual(find('HATTIVATTI','ATT'),1)
        self.assertIsNone(find('HATTIVATTI','XXX'))

if __name__=='__main__':
    unittest.main()
