#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c19_1_eulerian_paths.h"
#include "util.h"

namespace {
	vector<ll> debrujin(ll n, ll k) {
		if (n <= 1)
			return views::iota(0ll, n * k) | ranges::to<vector>();
		vector<vector<ll>> adj(1);
		ll d = ipow(k, n - 2);
		for (ll i = 0; i < d * k; ++i) {
			ll e = i % d * k;
			adj.push_back(views::iota(e + 1, e + k + 1) | ranges::to<vector>());
		}
		vector<ll> ret(n - 2);
		for (ll i : hierholzer2(adj))
			ret.push_back((i - 1) % k);
		return ret;
	}

	void test(ll n, ll k) {
		auto ret = debrujin(n, k);
		EXPECT_EQ(ret.size(), ipow(k, n) + n - 1);
		if (n > 0) {
			vector<ll> vec(n);
			do {
				EXPECT_TRUE(ranges::search(ret, vec).begin() != ret.end());
			} while (next_product(vec, k));
		}
	}
}

TEST(C193DeBrujinSequences, debrujin) {
	test(0, 0);
	test(1, 3);
	test(3, 2);
}
