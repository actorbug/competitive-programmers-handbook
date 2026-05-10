import unittest
from c21_1_primes_and_factors import totient

def modpow(x,n,m):
    u=1
    while n>0:
        if n%2:
            u=(u*x)%m
        n//=2
        x=(x*x)%m
    return u

def modinv(x,m):
    return modpow(x,totient(m)-1,m)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(modpow(2,3,7),1)
        self.assertEqual(modinv(6,17),3)

if __name__=='__main__':
    unittest.main()
