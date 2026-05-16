#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	void method1(ll n, auto f) {
		vector<ll> subset;
		auto search = [&](this auto self, ll k) -> void {
			if (k == n) {
				// process subset
				f(subset);
			}
			else {
				self(k + 1);
				subset.push_back(k);
				self(k + 1);
				subset.pop_back();
			}
			};
		search(0);
	}

	void method2(ll n, auto f) {
		for (ll b = 0; b < (1ll << n); ++b) {
			vector<ll> subset;
			for (ll i = 0; i < n; ++i) {
				if (b & (1ll << i)) subset.push_back(i);
			}
			// process subset
			f(subset);
		}
	}
}

#define TEST_SUBSET(f) do {\
	vector<vector<ll>> ret;\
	f(0, [&](const auto& v) { ret.push_back(v); });\
	EXPECT_EQ(ret, vector<vector<ll>>{{}});\
	ret.clear();\
	f(3, [&](const auto& v) { ret.push_back(v); });\
	EXPECT_EQ(ret | ranges::to<multiset>(), (multiset<vector<ll>>{{}, { 0 }, { 0, 1 }, { 0, 1, 2 }, { 0, 2 }, { 1 }, { 1, 2 }, { 2 }}));\
} while(0)

TEST(C051GeneratingSubsets, method1) {
	TEST_SUBSET(method1);
}

TEST(C051GeneratingSubsets, method2) {
	TEST_SUBSET(method2);
}
