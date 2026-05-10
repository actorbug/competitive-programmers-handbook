import unittest
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def bubblesort(array):
    for i in range(len(array)-1,0,-1):
        for j in range(i):
            if array[j]>array[j+1]:
                array[j],array[j+1]=array[j+1],array[j]

def merge(l,r):
    l=[*l]
    r=[*r]
    i=j=0
    while i<len(l) and j<len(r):
        if l[i]<=r[j]:
            yield l[i]
            i+=1
        else:
            yield r[j]
            j+=1
    yield from l[i:]
    yield from r[j:]

def mergesort(array):
    k=len(array)//2
    if k<=0:
        return array[:]
    return merge(mergesort(array[:k]),mergesort(array[k:]))

def countsort(array):
    ret=[0]*(max(array,default=0)+1)
    for e in array:
        ret[e]+=1
    for i,e in enumerate(ret):
        for _ in range(e):
            yield i

class Test(unittest.TestCase):
    @staticmethod
    def call(s,a):
        return a if (r:=s(a)) is None else [*r]
    def test(self):
        for s in (bubblesort,mergesort,countsort):
            with self.subTest(s=s):
                self.assertEqual(self.call(s,[]),[])
                self.assertEqual(self.call(s,[1,3,8,2,9,2,5,6]),[1,2,2,3,5,6,8,9])
                self.assertEqual(self.call(s,[1,3,6,2,8,2,5,9]),[1,2,2,3,5,6,8,9])
                self.assertEqual(self.call(s,[1,3,6,9,9,3,5,9]),[1,3,3,5,6,9,9,9])

if __name__=='__main__':
    unittest.main()
