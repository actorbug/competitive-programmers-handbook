import unittest
from functools import cache
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

INF=1<<63

def solve(coins,x):
    if x<0:
        return INF
    if x==0:
        return 0
    best=INF
    for c in coins:
        best=min(best,solve(coins,x-c)+1)
    return best

def solve2(coins,x):
    @cache
    def rec(x):
        if x<0:
            return INF
        if x==0:
            return 0
        best=INF
        for c in coins:
            best=min(best,rec(x-c)+1)
        return best
    return rec(x)

def solve3(coins,n):
    if n<0:
        return INF
    value=[INF]*(n+1)
    value[0]=0
    for x in range(1,n+1):
        for c in coins:
            if x-c>=0:
                value[x]=min(value[x],value[x-c]+1)
    return value[n]

def solve4(coins,n):
    if n<0:
        return
    value=[INF]*(n+1)
    value[0]=0
    first=[0]*(n+1)
    for x in range(1,n+1):
        for c in coins:
            if x-c>=0 and value[x-c]+1<value[x]:
                value[x]=value[x-c]+1
                first[x]=c
    while n>0:
        yield first[n]
        n-=first[n]

def solve5(coins,n,m):
    if n<0:
        return 0
    count=[0]*(n+1)
    count[0]=1
    for x in range(1,n+1):
        for c in coins:
            if x-c>=0:
                count[x]+=count[x-c]
                count[x]%=m
    return count[n]

class Test(unittest.TestCase):
    def test(self):
        coins=[1,3,4]
        for s in (solve,solve2,solve3):
            with self.subTest(s=s):
                self.assertEqual(s(coins,-1),INF)
                self.assertEqual(s(coins,0),0)
                self.assertEqual(s(coins,10),3)
                self.assertEqual(s([5],3),INF)
        self.assertCountEqual(solve4(coins,-1),[])
        self.assertCountEqual(solve4(coins,0),[])
        self.assertCountEqual(solve4(coins,10),[3,3,4])
        m=10**9+7
        self.assertEqual(solve5(coins,-1,m),0)
        self.assertEqual(solve5(coins,0,m),1)
        self.assertEqual(solve5(coins,5,m),6)

if __name__=='__main__':
    unittest.main()
