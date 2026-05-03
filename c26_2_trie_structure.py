import unittest

class Trie:
    def __init__(self):
        self.v=[{}]
        self.last=set()
    def add(self,s):
        cur=0
        for c in s:
            if c in self.v[cur]:
                cur=self.v[cur][c]
            else:
                self.v[cur][c]=len(self.v)
                cur=len(self.v)
                self.v.append({})
        self.last.add(cur)
    def __contains__(self,s):
        cur=0
        for c in s:
            if c not in self.v[cur]:
                return False
            cur=self.v[cur][c]
        return cur in self.last
    def prefix(self,s):
        l,cur=0,0
        for i,c in enumerate(s):
            if c not in self.v[cur]:
                return s[:l]
            cur=self.v[cur][c]
            if cur in self.last:
                l=i+1
        return s[:l]

class Test(unittest.TestCase):
    def test(self):
        t=Trie()
        t.add('CANAL')
        t.add('CANDY')
        t.add('THE')
        t.add('THERE')
        self.assertFalse('THERN' in t)
        self.assertTrue('THE' in t)
        self.assertEqual(t.prefix('THERN'),'THE')

if __name__=='__main__':
    unittest.main()
