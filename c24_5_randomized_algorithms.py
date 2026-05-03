import unittest
from random import seed,randint,randrange
from c23_1_operations import M

def partition(a,left,right,pivotIndex):
    pivotValue=a[pivotIndex]
    a[pivotIndex],a[right]=a[right],a[pivotIndex]
    storeIndex=left
    for i in range(left,right):
        if a[i]<=pivotValue:
            a[storeIndex],a[i]=a[i],a[storeIndex]
            storeIndex+=1
    a[right],a[storeIndex]=a[storeIndex],a[right]
    return storeIndex

def order_statistics(a,k):
    left,right=0,len(a)-1
    while True:
        pivotIndex=randint(left,right)
        pivotNewIndex=partition(a,left,right,pivotIndex)
        if k==pivotNewIndex:
            return a[k]
        elif k<pivotNewIndex:
            right=pivotNewIndex-1
        else:
            left=pivotNewIndex+1

def verify(a,b,c):
    x=M([[randrange(1,10)] for _ in c.v[0]])
    return (a@(b@x)).v==(c@x).v

def coloring(edges):
    d={j:False for i in edges for j in i}
    while True:
        for i in d:
            d[i]=randrange(2)>0
        c=sum(d[i]!=d[j] for i,j in edges)
        if c>=(len(edges)+1)//2:
            return d

class Test(unittest.TestCase):
    def test(self):
        seed(0)
        self.assertEqual(order_statistics([8,4,3,7,6,5,2,1],3),4)
        self.assertFalse(verify(M([[1,0],[0,1]]),M([[6,8],[1,3]]),M([[8,7],[3,2]])))
        edges=[(0,1),(0,2),(0,3),(1,3),(1,4),(2,3),(3,4)]
        self.assertEqual(coloring([]), {})
        d=coloring(edges)
        self.assertGreaterEqual(sum(d[i]!=d[j] for i,j in edges),4)

if __name__=='__main__':
    unittest.main()
