#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 2;

namespace {
	ll solve(vector<ll> coins, ll n) {
		if (n < 0)
			return INF;
		ll count = 0;
		ranges::sort(coins, greater());
		for (ll c : coins) {
			count += n / c;
			n %= c;
		}
		return (n == 0) ? count : INF;
	}
}

TEST(C061CoinProblem, solve) {
	vector<ll> coins = { 1,2,5,10,20,50,100,200 };
	EXPECT_EQ(solve({}, 0), 0);
	EXPECT_EQ(solve({}, 1), INF);
	EXPECT_EQ(solve({ 5 }, 3), INF);
	EXPECT_EQ(solve(coins, -1), INF);
	EXPECT_EQ(solve(coins, 0), 0);
	EXPECT_EQ(solve(coins, 520), 4);
	EXPECT_EQ(solve({ 200,1,2,5,10,20,50,100 }, 520), 4);
}
