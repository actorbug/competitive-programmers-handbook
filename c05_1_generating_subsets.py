import unittest
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def method1(n):
    subset=[]
    def search(k):
        if k==n:
            yield subset[:]
            return
        yield from search(k+1)
        subset.append(k)
        yield from search(k+1)
        subset.pop()
    return search(0)

def method2(n):
    for b in range(1<<n):
        yield [i for i in range(n) if b&(1<<i)]

class Test(unittest.TestCase):
    def test(self):
        for m in (method1,method2):
            with self.subTest(m=m):
                self.assertCountEqual(m(0),[[]])
                self.assertCountEqual(m(3),[[],[0],[1],[2],[0,1],[0,2],[1,2],[0,1,2]])

if __name__=='__main__':
    unittest.main()
