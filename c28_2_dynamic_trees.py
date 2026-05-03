import unittest
from typing import Optional
from dataclasses import dataclass
from copy import copy

@dataclass
class Node:
    value:int
    x:int
    y:int
    left:Optional['Node']=None
    right:Optional['Node']=None
    def sum(self,a,b):
        if b<self.x or a>self.y:
            return 0
        if a<=self.x and self.y<=b:
            return self.value
        return (self.left.sum(a,b) if self.left else 0)+(self.right.sum(a,b) if self.right else 0)
    def add(self,k,v):
        self.value+=v
        if self.x<self.y:
            d=(self.x+self.y)//2
            if k<=d:
                self.left=self.make_add(self.left,k,v,self.x,d)
            else:
                self.right=self.make_add(self.right,k,v,d+1,self.y)
    @staticmethod
    def make_add(node,k,v,x,y):
        node=node or Node(0,x,y)
        node.add(k,v)
        return node

class Sparse:
    def __init__(self,n):
        self.root=Node(0,0,2**max(n-1,0).bit_length()-1)
    def sum(self,a,b):
        return self.root.sum(a,b)
    def add(self,k,v):
        self.root.add(k,v)

@dataclass
class PNode:
    value:int
    x:int
    y:int
    left:Optional['PNode']=None
    right:Optional['PNode']=None
    def sum(self,a,b):
        if b<self.x or a>self.y:
            return 0
        if a<=self.x and self.y<=b:
            return self.value
        return (self.left.sum(a,b) if self.left else 0)+(self.right.sum(a,b) if self.right else 0)
    def add(self,k,v):
        self.value+=v
        if self.x<self.y:
            d=(self.x+self.y)//2
            if k<=d:
                self.left=self.copy_add(self.left,k,v,self.x,d)
            else:
                self.right=self.copy_add(self.right,k,v,d+1,self.y)
    @staticmethod
    def copy_add(node,k,v,x,y):
        if node is None:
            node=PNode(0,x,y)
        else:
            node=copy(node)
        node.add(k,v)
        return node

class Permanent:
    def __init__(self,n):
        self.hist=[PNode(0,0,2**max(n-1,0).bit_length()-1)]
    def sum(self,a,b,h=0):
        return self.hist[-h-1].sum(a,b)
    def add(self,k,v):
        self.hist.append(copy(self.hist[-1]))
        self.hist[-1].add(k,v)

class Test(unittest.TestCase):
    def test(self):
        s=Sparse(1)
        self.assertEqual(s.sum(0,-1),0)

        s=Sparse(16)
        self.assertEqual(s.sum(2,7),0)
        s.add(3,2)
        s.add(10,3)
        self.assertEqual(s.sum(2,7),2)

        s=Permanent(1)
        self.assertEqual(s.sum(0,-1),0)

        s=Permanent(16)
        self.assertEqual(s.sum(2,7),0)
        s.add(3,2)
        s.add(10,3)
        self.assertEqual(s.sum(2,7),2)
        self.assertEqual(s.sum(2,7,2),0)

if __name__=='__main__':
    unittest.main()
