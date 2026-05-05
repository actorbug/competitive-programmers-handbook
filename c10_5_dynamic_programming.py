import unittest

INF=1<<63

def optimal_selection(price):
    if not price:
        return 0
    n,k=len(price[0]),len(price)
    if n<k:
        return None
    total=[[INF]*n for _ in range(1<<k)]
    total[0][0]=0
    for x in range(k):
        total[1<<x][0]=price[x][0]
    for d in range(1,n):
        for s in range(1<<k):
            total[s][d]=total[s][d-1]
            for x in range(k):
                if s&(1<<x):
                    total[s][d]=min(total[s][d],total[s^(1<<x)][d-1]+price[x][d])
    return total[-1][-1]

def from_permutations_to_subsets(x,weight):
    if not weight:
        return 0
    if any(x<w for w in weight):
        return None
    n=len(weight)
    best=[(n+1,0)]*(1<<n)
    best[0]=1,0
    for s in range(1,1<<n):
        for p in range(n):
            if s&(1<<p):
                rides,last=best[s^(1<<p)]
                if last+weight[p]<=x:
                    last+=weight[p]
                else:
                    rides+=1
                    last=weight[p]
                best[s]=min(best[s],(rides,last))
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
