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
		vector<vector<ll>> adj;
		ll d = ipow(k, n - 2);
		for (ll i = 0; i < d * k; ++i) {
			ll e = i % d * k;
			adj.push_back(views::iota(e, e + k) | ranges::to<vector>());
		}
		vector<ll> ret(n - 2);
		for (ll i : hierholzer2(adj))
			ret.push_back(i % k);
		return ret;
	}
}

TEST(C193DeBrujinSequences, debrujin) {
	EXPECT_EQ(debrujin(0, 0), vector<ll>{});
	EXPECT_EQ(debrujin(1, 3), (vector<ll>{ 0,1,2 }));
	EXPECT_EQ(debrujin(3, 2), (vector<ll>{ 0,0,1,1,1,0,1,0,0,0 }));
}
