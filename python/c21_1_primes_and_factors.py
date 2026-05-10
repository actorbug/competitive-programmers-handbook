import unittest
from itertools import groupby
from math import prod,isqrt,log
import sys

sys.setrecursionlimit(max(sys.getrecursionlimit(),1<<20))

def prime(n):
    if n<2:
        return False
    for x in range(2,isqrt(n)+1):
        if n%x==0:
            return False
    return True

def factors(n):
    x=2
    while x*x<=n:
        while n%x==0:
            yield x
            n//=x
        x+=1
    if n>1:
        yield n

def factors_e(n):
    for p,g in groupby(factors(n)):
        yield p,sum(1 for _ in g)

def factor_count(n):
    return prod(a+1 for _,a in factors_e(n))

def factor_sum(n):
    return prod((p**(a+1)-1)//(p-1) for p,a in factors_e(n))

def factor_product(n):
    c=factor_count(n)
    return n**(c//2)*(isqrt(n) if c%2 else 1)

def is_perfect(n):
    return n==factor_sum(n)-n

def density(n):
    return n/log(n)

def eratosthenes(n):
    sieve=[1,1]+[0]*(n-1)
    for x in range(2,n+1):
        if sieve[x]:
            continue
        for u in range(2*x,n+1,x):
            sieve[u]=x
    return sieve

def gcd(a,b):
    if b==0:
        return a
    return gcd(b,a%b)

def totient(n):
    return prod((p-1)*p**(a-1) for p,a in factors_e(n))

class Test(unittest.TestCase):
    def test(self):
        self.assertFalse(prime(1))
        self.assertFalse(prime(35))
        self.assertTrue(prime(7))
        self.assertTrue(prime(19))
        self.assertTrue(prime(41))
        self.assertCountEqual(factors(1),[])
        self.assertCountEqual(factors(84),[2,2,3,7])
        self.assertCountEqual(factors_e(1),[])
        self.assertCountEqual(factors_e(84),[(2,2),(3,1),(7,1)])
        self.assertEqual(factor_count(1),1)
        self.assertEqual(factor_count(84),12)
        self.assertEqual(factor_sum(84),224)
        self.assertEqual(factor_product(84),351298031616)
        self.assertFalse(is_perfect(1))
        self.assertTrue(is_perfect(28))
        self.assertAlmostEqual(density(1000000),72382,0)
        self.assertEqual(eratosthenes(20),[1,1,0,0,2,0,3,0,2,3,5,0,3,0,7,5,2,0,3,0,5])
        self.assertEqual(gcd(24,36),12)
        self.assertEqual(gcd(13,8),1)
        self.assertEqual(totient(12),4)
        self.assertEqual(totient(2),1)

if __name__=='__main__':
    unittest.main()
