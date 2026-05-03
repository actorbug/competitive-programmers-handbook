import unittest
from collections import Counter
from heapq import heapify,heappush,heappop

def huffman(freq):
    i=0
    heap=[(v,i:=i+1,k) for k,v in freq.items()]
    if len(heap)<2:
        heap.append((0,i:=i+1,None))
    heapify(heap)
    while len(heap)>1:
        v2,_,k2=heappop(heap)
        v1,_,k1=heappop(heap)
        heappush(heap,(v1+v2,i:=i+1,(k1,k2)))
    return heap[0][-1]

def tree2dict(tree):
    dict_={}
    def rec(k,v):
        if isinstance(k,tuple):
            rec(k[0],v+'0')
            rec(k[1],v+'1')
        else:
            dict_[k]=v
    rec(tree,'')
    return dict_

def encode(s,d):
    return ''.join(d[c] for c in s)

def decode(e,t):
    s,p=[],t
    for c in e:
        p=p[int(c)]
        if isinstance(p,str):
            s.append(p)
            p=t
    return ''.join(s)

class Test(unittest.TestCase):
    def assertValid(self,s,e):
        t=huffman(Counter(s))
        with self.subTest(s=s):
            self.assertEqual(encode(s,tree2dict(t)),e)
            self.assertEqual(decode(e,t),s)
    def test(self):
        self.assertValid('','')
        self.assertValid('AAA','000')
        self.assertValid('AABACDACA','001010111000110')

if __name__=='__main__':
    unittest.main()
