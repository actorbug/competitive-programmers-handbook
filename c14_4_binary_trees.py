import unittest

def pre_order(tree):
    if tree is not None:
        c,l,r=tree
        yield c
        yield from pre_order(l)
        yield from pre_order(r)

def in_order(tree):
    if tree is not None:
        c,l,r=tree
        yield from in_order(l)
        yield c
        yield from in_order(r)

def post_order(tree):
    if tree is not None:
        c,l,r=tree
        yield from post_order(l)
        yield from post_order(r)
        yield c

def from_pre_in(pre,in_):
    if not pre or not in_:
        return None
    i=in_.index(pre[0])
    return (pre[0],from_pre_in(pre[1:i+1],in_[:i]),from_pre_in(pre[i+1:],in_[i+1:]))

def from_in_post(in_,post):
    if not in_ or not post:
        return None
    i=in_.index(post[-1])
    return (post[-1],from_in_post(in_[:i],post[:i]),from_in_post(in_[i+1:],post[i:-1]))

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual([*pre_order(None)],[])
        self.assertEqual([*in_order(None)],[])
        self.assertEqual([*post_order(None)],[])
        self.assertIsNone(from_pre_in([],[]))
        self.assertIsNone(from_in_post([],[]))
        tree=(1,(2,(4,None,None),(5,(6,None,None),None)),(3,None,(7,None,None)))
        self.assertEqual([*pre_order(tree)],[1,2,4,5,6,3,7])
        self.assertEqual([*in_order(tree)],[4,2,6,5,1,3,7])
        self.assertEqual([*post_order(tree)],[4,6,5,2,7,3,1])
        self.assertEqual(from_pre_in([1,2,4,5,6,3,7],[4,2,6,5,1,3,7]),tree)
        self.assertEqual(from_in_post([4,2,6,5,1,3,7],[4,6,5,2,7,3,1]),tree)

if __name__=='__main__':
    unittest.main()
