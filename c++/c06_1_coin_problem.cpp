#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	ll solve(vector<ll> coins, ll n) {
		ll count = 0;
		ranges::sort(coins, greater());
		for (ll c : coins) {
			count += n / c;
			n %= c;
		}
		return (n == 0) ? count : -1;
	}
}

TEST(C061CoinProblem, solve) {
	EXPECT_EQ(solve({}, 0), 0);
	EXPECT_EQ(solve({}, 1), -1);
	EXPECT_EQ(solve({ 1,2,5,10,20,50,100,200 }, 520), 4);
	EXPECT_EQ(solve({ 200,1,2,5,10,20,50,100 }, 520), 4);
}
