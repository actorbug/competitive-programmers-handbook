import unittest
from math import inf
from c23_1_operations import M

def count(m,n):
    return m**n

def shortest(x,n):
    def mul(s,o):
        return M([[min(i+j for i,j in zip(si,oi)) for oi in zip(*o.v)] for si in s.v])
    u=M([[0 if i==j else inf for j in range(len(x.v))] for i in range(len(x.v))])
    while n>0:
        if n%2:
            u=mul(u,x)
        n//=2
        x=mul(x,x)
    return u

def kirchhoff(adj):
    n=len(adj)
    return M([[len(adj[i]) if i==j else -1 if j in adj[i] else 0 for j in range(n)] for i in range(n)]).submatrix(0,0).det()

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(count(M([[0,0,0,1,0,0],[1,0,0,0,1,1],[0,1,0,0,0,0],[0,1,0,0,0,0],[0,0,0,0,0,0],[0,0,1,0,1,0]]),4),M([[0,0,1,1,1,0],[2,0,0,0,2,2],[0,2,0,0,0,0],[0,2,0,0,0,0],[0,0,0,0,0,0],[0,0,1,1,1,0]]))
        self.assertEqual(shortest(M([[inf,inf,inf,4,inf,inf],[2,inf,inf,inf,1,2],[inf,4,inf,inf,inf,inf],[inf,1,inf,inf,inf,inf],[inf,inf,inf,inf,inf,inf],[inf,inf,3,inf,2,inf]]),4),M([[inf,inf,10,11,9,inf],[9,inf,inf,inf,8,9],[inf,11,inf,inf,inf,inf],[inf,8,inf,inf,inf,inf],[inf,inf,inf,inf,inf,inf],[inf,inf,12,13,11,inf]]))
        self.assertEqual(kirchhoff([[1,2,3],[0],[0,3],[0,2]]),3)

if __name__=='__main__':
    unittest.main()
