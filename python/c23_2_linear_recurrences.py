import unittest
from c23_1_operations import M

def fib(n):
    return (M([[0,1],[1,1]])**(n-1)).v[1][1] if n>0 else 0

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(fib(0),0)
        self.assertEqual(fib(7),13)

if __name__=='__main__':
    unittest.main()
