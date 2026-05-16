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

	void test_diophantine(ll a, ll b, ll c) {
		auto ret = diophantine(a, b, c);
		ASSERT_TRUE(ret);
		auto [x, y] = *ret;
		EXPECT_EQ(a * x + b * y, c);
	}

	void test_chinese(const vector<pair<ll, ll>>& xs) {
		ll x = chinese(xs);
		for (auto [a, m] : xs)
			EXPECT_EQ(x % m, a);
	}
}

TEST(C213SolvingEquations, diophantine) {
	test_diophantine(1, 1, 1);
	test_diophantine(5, 2, 11);
	test_diophantine(39, 15, 12);
}

TEST(C213SolvingEquations, chinese) {
	test_chinese({{1,2}});
	test_chinese({{3,5},{4,7},{2,3}});
}
