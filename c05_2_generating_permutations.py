import unittest
from itertools import permutations
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def method1(n):
    permutation,chosen=[],[False]*n
    def search():
        if len(permutation)>=n:
            yield permutation[:]
            return
        for i in range(n):
            if chosen[i]:
                continue
            chosen[i]=True
            permutation.append(i)
            yield from search()
            chosen[i]=False
            permutation.pop()
    return search()

def method2(n):
    return permutations(range(n))

class Test(unittest.TestCase):
    def test(self):
        for m in (method1,method2):
            with self.subTest(m=m):
                self.assertCountEqual(map(list,m(0)),[[]])
                self.assertCountEqual(map(list,m(3)),[[0,1,2],[0,2,1],[1,0,2],[1,2,0],[2,0,1],[2,1,0]])

if __name__=='__main__':
    unittest.main()
