import unittest
from collections import Counter
from c26_3_string_hashing import Preprocessing

def knapsack(w):
    w=Counter(w)
    W=sum(k*v for k,v in w.items())
    possible=[True]+[False]*W
    for k,v in w.items():
        for x in range(W-k,-1,-1):
            if possible[x]:
                for y in range(x+k,min(x+k*v,W)+1,k):
                    if possible[y]:
                        break
                    possible[y]=True
    return possible

def string_construction(s,d):
    count=[1]
    sh=Preprocessing(s)
    dh={Preprocessing.hash(i) for i in d}
    dp=set(map(len,d))
    for i in range(1,len(s)+1):
        count.append(sum(count[i-j] for j in dp if i>=j and sh[i-j:i] in dh and s[i-j:i] in d))
    return count[-1]

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(knapsack([1,3,3]),[True,True,False,True,True,False,True,True])
        self.assertEqual(string_construction('ABAB',{'A','B','AB'}),4)

if __name__=='__main__':
    unittest.main()
