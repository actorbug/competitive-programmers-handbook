import unittest

def solve(a):
    s=[]
    for i in range(len(a)):
        while s and a[s[-1]]>=a[i]:
            s.pop()
        yield s[-1] if s else None
        s.append(i)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual([*solve([])],[])
        self.assertEqual([*solve([1,3,4,2,5,3,4,2])],[None,0,1,0,3,3,5,0])

if __name__=='__main__':
    unittest.main()
