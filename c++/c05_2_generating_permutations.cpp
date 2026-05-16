#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	void method1(ll n, auto f) {
		vector<ll> permutation;
		vector<bool> chosen(n, false);
		auto search = [&](this auto self) -> void {
			if (ssize(permutation) == n) {
				// process permutation
				f(permutation);
			}
			else {
				for (int i = 0; i < n; ++i) {
					if (chosen[i]) continue;
					chosen[i] = true;
					permutation.push_back(i);
					self();
					chosen[i] = false;
					permutation.pop_back();
				}
			}
			};
		search();
	}

	void method2(ll n, auto f) {
		auto permutation = views::iota(0ll, n) | ranges::to<vector>();
		do {
			// process permutation
			f(permutation);
		} while (next_permutation(permutation.begin(), permutation.end()));
	}
}

#define TEST_PERM(f) do {\
	vector<vector<ll>> ret;\
	f(0, [&](const auto& v) { ret.push_back(v); });\
	EXPECT_EQ(ret, vector<vector<ll>>{{}});\
	ret.clear();\
	f(3, [&](const auto& v) { ret.push_back(v); });\
	EXPECT_EQ(ret | ranges::to<multiset>(), (multiset<vector<ll>>{{ 0, 1, 2 }, { 0, 2, 1 }, { 1, 0, 2 }, { 1, 2, 0 }, { 2, 0, 1 }, { 2, 1, 0 }}));\
} while(0)

TEST(C052GeneratingPermutations, method1) {
	TEST_PERM(method1);
}

TEST(C052GeneratingPermutations, method2) {
	TEST_PERM(method2);
}
