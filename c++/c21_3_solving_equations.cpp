#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c21_2_modular_arithmetic.h"

namespace {
	tuple<ll, ll, ll> extGcd(ll a, ll b) {
		if (b == 0)
			return { a, 1, 0 };
		auto [d, x, y] = extGcd(b, a % b);
		return { d, y, x - (a / b) * y };
	}

	optional<pair<ll, ll>> diophantine(ll a, ll b, ll c) {
		auto [d, x, y] = extGcd(a, b);
		if (c % d == 0)
			return make_pair(x * (c / d), y * (c / d));
		else
			return nullopt;
	}

	ll chinese(const vector<pair<ll, ll>>& xs) {
		ll ms = 1;
		for (auto [_, m] : xs)
			ms *= m;
		ll ret = 0;
		for (auto [a, m] : xs)
			ret += a * ms / m * modinv(ms / m, m);
		return ret;
	}
}

TEST(C213SolvingEquations, diophantine) {
	EXPECT_EQ(diophantine(1, 1, 1), make_pair(0, 1));
	EXPECT_EQ(diophantine(5, 2, 11), make_pair(11, -22));
	EXPECT_EQ(diophantine(39, 15, 12), make_pair(8, -20));
}

TEST(C213SolvingEquations, chinese) {
	EXPECT_EQ(chinese({{1,2}}), 1);
	EXPECT_EQ(chinese({{3,5},{4,7},{2,3}}), 263);
}
