import unittest

def optimal_selection(price):
    n=len(price[0]) if price else 0
    k=len(price)
    INF=sum(max(p,default=0) for p in price)+1
    total=[0]+[INF]*((1<<k)-1)
    for d in range(1,n+1):
        for s in range((1<<k)-1,0,-1):
            total[s]=min(total[s],min(total[s^(1<<x)]+price[x][d-1] for x in range(k) if s&(1<<x)))
    return total[-1] if total[-1]<INF else None

def from_permutations_to_subsets(x,weight):
    if any(x<w for w in weight):
        return None
    def add(r,l,w):
        if l+w<=x:
            return r,l+w
        else:
            return r+1,w
    best=[(0,x)]
    for s in range(1,1<<len(weight)):
        best.append(min(add(*best[s^(1<<p)],w) for p,w in enumerate(weight) if s&(1<<p)))
    return best[-1][0]

def counting_subsets(value):
    n=len(value).bit_length()-1
    sum_=value[:]
    for k in range(n):
        for s in range(1<<n):
            if s&(1<<k):
                sum_[s]+=sum_[s^(1<<k)]
    return sum_

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(optimal_selection([]),0)
        self.assertIsNone(optimal_selection([[]]))
        self.assertEqual(optimal_selection([[6,9,5,2,8,9,1,6],[8,2,6,2,7,5,7,2],[5,3,9,7,3,5,1,4]]),5)
        self.assertEqual(from_permutations_to_subsets(10,[]),0)
        self.assertIsNone(from_permutations_to_subsets(2,[3]))
        self.assertEqual(from_permutations_to_subsets(10,[2,3,3,5,6]),2)
        self.assertEqual(counting_subsets([1]),[1])
        self.assertEqual(counting_subsets([3,1,4,5,5,1,3,3]),[3,4,7,13,8,10,15,25])

if __name__=='__main__':
    unittest.main()
