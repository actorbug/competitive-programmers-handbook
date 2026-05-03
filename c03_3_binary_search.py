import unittest

def method1(array,x):
    a,b=0,len(array)-1
    while a<=b:
        k=(a+b)//2
        if array[k]==x:
            return k
        if array[k]>x:
            b=k-1
        else:
            a=k+1
    return -1

def method2(array,x):
    n=len(array)
    k,b=0,n//2
    while b>=1:
        while k+b<n and array[k+b]<=x:
            k+=b
        b//=2
    return k if n>0 and array[k]==x else -1

def smallest(z,ok):
    x,b=-1,z
    while b>=1:
        while not ok(x+b):
            x+=b
        b//=2
    return x+1

def maximum(z,f):
    x,b=-1,z
    while b>=1:
        while f(x+b)<f(x+b+1):
            x+=b
        b//=2
    return x+1

class Test(unittest.TestCase):
    def test(self):
        for m in (method1,method2):
            with self.subTest(m=m):
                self.assertEqual(m([],5),-1)
                self.assertEqual(m([*range(10)],5),5)
                self.assertEqual(m([*range(10)],10),-1)
        self.assertEqual(smallest(10,lambda x:x>4),5)
        self.assertEqual(maximum(10,lambda x:-abs(5-x)),5)

if __name__=='__main__':
    unittest.main()
