#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	ll solve(const vector<vector<ll>>& value) {
		ll n = ssize(value);
		vector<vector<ll>> sum(n + 1, vector<ll>(n + 1));
		for (ll y = 1; y <= n; ++y) {
			for (ll x = 1; x <= n; ++x) {
				sum[y][x] = max(sum[y][x - 1], sum[y - 1][x]) + value[y - 1][x - 1];
			}
		}
		return sum.back().back();
	}
}

TEST(C073PathsInAGrid, solve) {
	EXPECT_EQ(solve({}), 0);
	EXPECT_EQ(solve({ {3,7,9,2,7},{9,8,3,5,5},{1,7,9,8,5},{3,8,6,4,10},{6,3,9,7,8} }), 67);
}
