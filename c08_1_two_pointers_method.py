import unittest

def subarray_sum(a,x):
    i=j=s=0
    while s<x and j<len(a):
        if s+a[j]<=x:
            s+=a[j]
            j+=1
        elif i<j:
            s-=a[i]
            i+=1
        else:
            i=j=i+1
    return (i,j) if s==x else (None,None)

def two_sum_problem(a,x):
    a=sorted(a)
    i,j=0,len(a)-1
    while i<j:
        if a[i]+a[j]<x:
            i+=1
        elif a[i]+a[j]>x:
            j-=1
        else:
            return a[i],a[j]
    return None,None

def three_sum_problem(a,x):
    a=sorted(a)
    n=len(a)
    for i in range(n-2):
        j,k=i+1,n-1
        while j<k:
            if a[i]+a[j]+a[k]<x:
                j+=1
            elif a[i]+a[j]+a[k]>x:
                k-=1
            else:
                return a[i],a[j],a[k]
    return None,None,None

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(subarray_sum([],0),(0,0))
        self.assertEqual(subarray_sum([],1),(None,None))
        self.assertEqual(subarray_sum([1,3,2,5,1,1,2,3],8),(2,5))
        self.assertEqual(subarray_sum([1,3,2,5,1,1,2,3],2),(2,3))
        self.assertEqual(two_sum_problem([1,4],5),(1,4))
        self.assertEqual(two_sum_problem([1,4],12),(None,None))
        self.assertEqual(two_sum_problem([1,4,5,6,7,9,9,10],12),(5,7))
        self.assertEqual(three_sum_problem([1,4,5],10),(1,4,5))
        self.assertEqual(three_sum_problem([1,4,5],12),(None,None,None))
        self.assertEqual(three_sum_problem([1,4,5,6,7,9,9,10],12),(1,4,7))

if __name__=='__main__':
    unittest.main()
