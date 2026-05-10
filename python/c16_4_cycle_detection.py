import unittest

def floyd(succ,x):
    a=succ[x]
    b=succ[succ[x]]
    while a!=b:
        a=succ[a]
        b=succ[succ[b]]
    a=x
    while a!=b:
        a=succ[a]
        b=succ[b]
    b=succ[a]
    length=1
    while a!=b:
        b=succ[b]
        length+=1
    return a,length

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(floyd([0],0),(0,1))
        self.assertEqual(floyd([1,2,3,4,5,3],0),(3,3))

if __name__=='__main__':
    unittest.main()
