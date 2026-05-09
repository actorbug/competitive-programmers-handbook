import unittest

def min1(ary):
    return sorted(ary)[len(ary)//2]

def sum1(ary,x):
    return sum(abs(a-x) for a in ary)

def min2(ary):
    return sum(ary)/len(ary)

def sum2(ary,x):
    return sum((a-x)**2 for a in ary)

class Test(unittest.TestCase):
    def assertValid(self,m,s,a,x,t):
        with self.subTest(m=m,a=a):
            self.assertEqual(y:=m(a),x)
            self.assertEqual(s(a,y),t)
    def test(self):
        self.assertValid(min1,sum1,[1],1,0)
        self.assertValid(min1,sum1,[1,2],2,1)
        self.assertValid(min1,sum1,[1,2,9,2,6],2,12)
        self.assertValid(min2,sum2,[1],1,0)
        self.assertValid(min2,sum2,[1,2,9,2,6],4,46)

if __name__=='__main__':
    unittest.main()
