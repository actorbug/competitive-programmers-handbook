import unittest
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def bubble_sort(array):
    for i in range(len(array)-1,0,-1):
        for j in range(i):
            if array[j]>array[j+1]:
                array[j],array[j+1]=array[j+1],array[j]

def merge_sort(array):
    def rec(a,b):
        if a>=b:
            return
        k=(a+b)//2
        rec(a,k)
        rec(k+1,b)
        merge=array[a:k+1]+array[b:k:-1]
        l,r=0,b-a
        for i in range(a,b+1):
            if merge[l]>merge[r]:
                array[i]=merge[r]
                r-=1
            else:
                array[i]=merge[l]
                l+=1
    rec(0,len(array)-1)

def counting_sort(array):
    ret=[0]*(max(array,default=0)+1)
    for e in array:
        ret[e]+=1
    i=0
    for j,e in enumerate(ret):
        for _ in range(e):
            array[i]=j
            i+=1

class Test(unittest.TestCase):
    def test(self):
        for s in (bubble_sort,merge_sort,counting_sort):
            with self.subTest(s=s):
                a=[]
                s(a)
                self.assertEqual(a,[])
                a=[1,3,8,2,9,2,5,6]
                s(a)
                self.assertEqual(a,[1,2,2,3,5,6,8,9])
                a=[1,3,6,2,8,2,5,9]
                s(a)
                self.assertEqual(a,[1,2,2,3,5,6,8,9])
                a=[1,3,6,9,9,3,5,9]
                s(a)
                self.assertEqual(a,[1,3,3,5,6,9,9,9])

if __name__=='__main__':
    unittest.main()
