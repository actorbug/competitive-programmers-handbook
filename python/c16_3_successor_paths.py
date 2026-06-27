import unittest

class Succ:
    def __init__(self,func,u):
        f=[*func]
        self.succ=[f]
        for _ in range(u):
            f=[f[i] for i in f]
            self.succ.append(f)
    def __call__(self,x,k):
        for f in self.succ:
            if k&1:
                x=f[x]
            k>>=1
        return x if k==0 else None

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(Succ([0,1],3)(1,10),1)
        succ=Succ([0,3,5,7,6,2,2,1,6,3],3)
        self.assertEqual(succ(4,6),2)
        self.assertEqual(succ(4,11),5)

if __name__=='__main__':
    unittest.main()
