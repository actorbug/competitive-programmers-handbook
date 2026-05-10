import unittest
from c23_1_operations import M

def markov(mat,init,m):
    return (mat**m@M([init]).transpose()).transpose().v[0]

class Test(unittest.TestCase):
    def test(self):
        m=M([[0,0.5,0,0,0],[1,0,0.5,0,0],[0,0.5,0,0.5,0],[0,0,0.5,0,1],[0,0,0,0.5,0]])
        self.assertEqual(markov(m,[1,0,0,0,0],0),[1,0,0,0,0])
        self.assertEqual(markov(m,[1,0,0,0,0],1),[0,1,0,0,0])
        self.assertEqual(markov(m,[1,0,0,0,0],2),[0.5,0,0.5,0,0])

if __name__=='__main__':
    unittest.main()
