import unittest
from c09_2_binary_indexed_tree import BIT
from c09_4_additional_techniques import index_compression

def count(ls):
    d=index_compression(p.imag for i in ls for p in i)
    b=BIT(len(d))
    c=0
    s=[]
    for p1,p2 in ls:
        if p1.real==p2.real:
            y1,y2=min(p1.imag,p2.imag),max(p1.imag,p2.imag)
            s.append((p1.real,1,d[y1],d[y2]))
        else:
            x1,x2=min(p1.real,p2.real),max(p1.real,p2.real)
            s.append((x1,0,d[p1.imag],1))
            s.append((x2,2,d[p1.imag],-1))
    s.sort()
    for _,k,i1,i2 in s:
        if k==1:
            c+=b.sum(i2+1)-b.sum(i1)
        else:
            b.add(i1,i2)
    return c

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(count([(0+1j,3+1j),(1+3j,4+3j),(4+2j,6+2j),(2+0j,2+5j),(5+1j,5+4j)]),3)

if __name__=='__main__':
    unittest.main()
