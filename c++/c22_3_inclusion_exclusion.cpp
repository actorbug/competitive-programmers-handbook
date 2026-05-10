#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	ll derangements1(ll n) {
		ll c = (n % 2) ? -1 : 1, ret = c;
		for (ll i = n; i > 0; --i) {
			c = -c * i;
			ret += c;
		}
		return ret;
	}

	ll derangements2(ll n) {
		if (n <= 2)
			return n - 1;
		return (n - 1) * (derangements2(n - 2) + derangements2(n - 1));
	}
}

TEST(C223InclusionExclusion, derangements1) {
	EXPECT_EQ(derangements1(3), 2);
}

TEST(C223InclusionExclusion, derangements2) {
	EXPECT_EQ(derangements2(3), 2);
}
