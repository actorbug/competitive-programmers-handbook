import unittest
import sys
from heapq import merge

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def bubble_sort(array):
    array=array[:]
    for i in range(len(array)-1,0,-1):
        for j in range(i):
            if array[j]>array[j+1]:
                array[j],array[j+1]=array[j+1],array[j]
    return array

def merge_sort(array):
    k=len(array)//2
    if k<=0:
        return array[:]
    return merge(merge_sort(array[:k]),merge_sort(array[k:]))

def counting_sort(array):
    ret=[0]*(max(array,default=0)+1)
    for e in array:
        ret[e]+=1
    for i,e in enumerate(ret):
        for _ in range(e):
            yield i

class Test(unittest.TestCase):
    def test(self):
        for s in (bubble_sort,merge_sort,counting_sort):
            with self.subTest(s=s):
                self.assertEqual([*s([])],[])
                self.assertEqual([*s([1,3,8,2,9,2,5,6])],[1,2,2,3,5,6,8,9])
                self.assertEqual([*s([1,3,6,2,8,2,5,9])],[1,2,2,3,5,6,8,9])
                self.assertEqual([*s([1,3,6,9,9,3,5,9])],[1,3,3,5,6,9,9,9])

if __name__=='__main__':
    unittest.main()
