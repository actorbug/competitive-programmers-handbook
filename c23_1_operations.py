import unittest
from fractions import Fraction

class M:
    def __init__(self,v):
        self.v=v
    def __repr__(self):
        return f'M({self.v})'
    def __eq__(self,o):
        return isinstance(o,M) and self.v==o.v
    def __add__(self,o):
        return M([[i+j for i,j in zip(si,oi)] for si,oi in zip(self.v,o.v)])
    def __sub__(self,o):
        return M([[i-j for i,j in zip(si,oi)] for si,oi in zip(self.v,o.v)])
    def __mul__(self,o):
        return M([[i*o for i in si] for si in self.v])
    def __rmul__(self,o):
        return self*o
    def __truediv__(self,o):
        return M([[i/o for i in si] for si in self.v]) 
    def __matmul__(self,o):
        return M([[sum(i*j for i,j in zip(si,oi)) for oi in zip(*o.v)] for si in self.v])
    def __pow__(self,n):
        if n==0:
            return self.identity(len(self.v))
        u=self**(n//2)
        u@=u
        if n%2==1:
            u@=self
        return u
    def submatrix(self,i,j):
        return M([[vxy for y,vxy in enumerate(vx) if y!=j] for x,vx in enumerate(self.v) if x!=i])
    def adj(self,i,j):
        return (-1 if (i+j)%2 else 1)*self.submatrix(i,j).det()
    def det(self):
        n=len(self.v)
        return sum(self.v[0][j]*self.adj(0,j) for j in range(n)) if n>1 else self.v[0][0]
    def inv(self):
        n=len(self.v)
        return M([[self.adj(j,i) for j in range(n)] for i in range(n)])/self.det()
    def transpose(self):
        return M([[self.v[j][i] for j in range(len(self.v))] for i in range(len(self.v[0]))])
    @staticmethod
    def identity(n):
        return M([[1 if i==j else 0 for j in range(n)] for i in range(n)])

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(M([[6,1,4],[3,9,2]])+M([[4,9,3],[8,1,3]]),M([[10,10,7],[11,10,5]]))
        self.assertEqual(2*M([[6,1,4],[3,9,2]]),M([[12,2,8],[6,18,4]]))
        self.assertEqual(M([[1,4],[3,9],[8,6]])@M([[1,6],[2,9]]),M([[9,42],[21,99],[20,102]]))
        self.assertEqual(M.identity(3),M([[1,0,0],[0,1,0],[0,0,1]]))
        self.assertEqual(M([[2,5],[1,4]])**3,M([[48,165],[33,114]]))
        self.assertEqual(M([[3,4],[1,6]]).det(),14)
        self.assertEqual(M([[2,4,3],[5,1,6],[7,2,4]]).det(),81)
        self.assertEqual(M([[Fraction(2),4,3],[5,1,6],[7,2,4]]).inv(),M([[Fraction(-8,81),Fraction(-10,81),Fraction(7,27)],[Fraction(22,81),Fraction(-13,81),Fraction(1,27)],[Fraction(1,27),Fraction(8,27),Fraction(-2,9)]]))
        self.assertEqual(M([[6,1,4],[3,9,2]]).transpose(),M([[6,3],[1,9],[4,2]]))

if __name__=='__main__':
    unittest.main()
