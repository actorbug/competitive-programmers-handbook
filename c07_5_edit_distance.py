import unittest

def solve(x,y):
    distance=[[a+b for b in range(len(y)+1)] for a in range(len(x)+1)]
    for a in range(1,len(x)+1):
        for b in range(1,len(y)+1):
            distance[a][b]=min(distance[a][b-1]+1,distance[a-1][b]+1,distance[a-1][b-1]+(x[a-1]!=y[b-1]))
    ret=[]
    a,b=len(x),len(y)
    while a>0 or b>0:
        if a>0 and distance[a-1][b]+1==distance[a][b]:
            ret.append(f'delete {b} {x[a-1]}')
            a-=1
        elif b>0 and distance[a][b-1]+1==distance[a][b]:
            ret.append(f'add {b-1} {y[b-1]}')
            b-=1
        else:
            if distance[a-1][b-1]+1==distance[a][b]:
                ret.append(f'edit {b-1} {x[a-1]} {y[b-1]}')
            a-=1
            b-=1
    return reversed(ret)

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual([*solve('','')],[])
        self.assertEqual([*solve('ABC','ABCA')],['add 3 A'])
        self.assertEqual([*solve('ABC','AC')],['delete 1 B'])
        self.assertEqual([*solve('ABC','ADC')],['edit 1 B D'])
        self.assertEqual([*solve('LOVE','MOVIE')],['edit 0 L M','add 3 I'])

if __name__=='__main__':
    unittest.main()
