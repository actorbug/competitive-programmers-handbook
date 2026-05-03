import unittest

def derangements1(n):
    c=-1 if n%2 else 1
    ret=c
    for i in range(n,0,-1):
        c=-c*i
        ret+=c
    return ret

def derangements2(n):
    if n<=2:
        return n-1
    else:
        return (n-1)*(derangements2(n-2)+derangements2(n-1))

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(derangements1(3),2)
        self.assertEqual(derangements2(3),2)

if __name__=='__main__':
    unittest.main()
