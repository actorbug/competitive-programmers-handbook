#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	ll solve1(const vector<ll>& array) {
		ll n = ssize(array);
		vector<ll> length(n);
		for (ll k = 0; k < n; ++k) {
			length[k] = 1;
			for (ll i = 0; i < k; ++i) {
				if (array[i] < array[k]) {
					length[k] = max(length[k], length[i] + 1);
				}
			}
		}
		return (n == 0) ? 0 : ranges::max(length);
	}

	ll solve2(const vector<ll>& array) {
		vector<ll> minval;
		for (ll v : array) {
			auto i = ranges::lower_bound(minval, v);
			if (i != minval.end())
				*i = v;
			else
				minval.push_back(v);
		}
		return ssize(minval);
	}

	void test(auto f) {
		EXPECT_EQ(f({}), 0);
		EXPECT_EQ(f({ 6,2,5,1,7,4,8,3 }), 4);
	}
}

TEST(C072LongestIncreasingSubseqence, solve1) {
	test(solve1);
}

TEST(C072LongestIncreasingSubseqence, solve2) {
	test(solve2);
}
