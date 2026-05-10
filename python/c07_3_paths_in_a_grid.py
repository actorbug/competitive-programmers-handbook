import unittest

def solve(value):
    h=len(value)
    w=len(value[0]) if value else 0
    sum_=[[0]*(w+1) for _ in range(h+1)]
    for y in range(h):
        for x in range(w):
            sum_[y][x]=max(sum_[y][x-1],sum_[y-1][x])+value[y][x]
    return sum_[h-1][w-1]

class Test(unittest.TestCase):
    def test(self):
        self.assertEqual(solve([]),0)
        self.assertEqual(solve([
            [3,7,9,2,7],
            [9,8,3,5,5],
            [1,7,9,8,5],
            [3,8,6,4,10],
            [6,3,9,7,8]
        ]),67)

if __name__=='__main__':
    unittest.main()
