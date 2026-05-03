import unittest

def algorithm1(array):
    n=len(array)
    best=0
    for a in range(n):
        for b in range(a,n):
            sum_=0
            for k in array[a:b+1]:
                sum_+=k
            best=max(best,sum_)
    return best

def algorithm2(array):
    n=len(array)
    best=0
    for a in range(n):
        sum_=0
        for b in array[a:]:
            sum_+=b
            best=max(best,sum_)
    return best

def algorithm3(array):
    best,sum_=0,0
    for k in array:
        sum_=max(k,sum_+k)
        best=max(best,sum_)
    return best

class Test(unittest.TestCase):
    def test(self):
        for a in (algorithm1,algorithm2,algorithm3):
            with self.subTest(a=a):
                self.assertEqual(a([]),0)
                self.assertEqual(a([-1]),0)
                self.assertEqual(a([-1,2,4,-3,5,2,-5,2]),10)

if __name__=='__main__':
    unittest.main()
