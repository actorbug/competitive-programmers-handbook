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
        self.assertEqual(Succ([0],3)(0,10),0)
        succ=Succ([2,4,6,5,1,1,0,5,2],3)
        self.assertEqual(succ(3,6),1)
        self.assertEqual(succ(3,11),4)

if __name__=='__main__':
    unittest.main()
