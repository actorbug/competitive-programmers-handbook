#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	tuple<ll, ll, ll> pythagorean(ll m, ll n) {
		return { n * n - m * m, 2 * n * m, n * n + m * m };
	}

	bool wilson(ll n) {
		ll ret = 1;
		for (ll i = 2; i < n; ++i)
			ret = (ret * i) % n;
		return ret == n - 1;
	}
}

TEST(C214OtherResults, pythagorean) {
	EXPECT_EQ(pythagorean(1, 2), make_tuple(3, 4, 5));
}

TEST(C214OtherResults, wilson) {
	EXPECT_TRUE(wilson(11));
	EXPECT_FALSE(wilson(12));
}
