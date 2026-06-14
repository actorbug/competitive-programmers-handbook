import unittest
from dataclasses import dataclass;

@dataclass
class Delete:
    pos: int
    c: str
@dataclass
class Add:
    pos: int
    c: str
@dataclass
class Edit:
    pos: int
    c1: str
    c2: str

def solve(x,y):
    distance=[[a+b for b in range(len(y)+1)] for a in range(len(x)+1)]
    for a in range(1,len(x)+1):
        for b in range(1,len(y)+1):
            distance[a][b]=min(distance[a][b-1]+1,distance[a-1][b]+1,distance[a-1][b-1]+(x[a-1]!=y[b-1]))
    ret=[]
    a,b=len(x),len(y)
    while a>0 or b>0:
        if a>0 and distance[a-1][b]+1==distance[a][b]:
            ret.append(Delete(b,x[a-1]))
            a-=1
        elif b>0 and distance[a][b-1]+1==distance[a][b]:
            ret.append(Add(b-1,y[b-1]))
            b-=1
        else:
            if distance[a-1][b-1]+1==distance[a][b]:
                ret.append(Edit(b-1,x[a-1],y[b-1]))
            a-=1
            b-=1
    return reversed(ret)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual([*solve('','')],[])
        self.assertEqual([*solve('ABC','ABCA')],[Add(3,'A')])
        self.assertEqual([*solve('ABC','AC')],[Delete(1,'B')])
        self.assertEqual([*solve('ABC','ADC')],[Edit(1,'B','D')])
        self.assertEqual([*solve('LOVE','MOVIE')],[Edit(0,'L','M'),Add(3, 'I')])

if __name__=='__main__':
    unittest.main()
