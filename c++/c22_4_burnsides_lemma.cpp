#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "util.h"

namespace {
	ll burnside(ll n, ll m) {
		ll ret = 0;
		for (ll i = 0; i < n; ++i)
			ret += ipow(m, gcd(i, n));
		return ret / n;
	}
}

TEST(C224BurnsidesLemma, burnside) {
	EXPECT_EQ(burnside(4, 3), 24);
}
