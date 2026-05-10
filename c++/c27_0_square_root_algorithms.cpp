#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "util.h"

namespace {
	struct RootBlock {
		RootBlock(vector<ll> array) : a(move(array)) {
			ll n = ssize(a);
			k = 1 + isqrt(max(n - 1, 0ll));
			b.resize((n + k - 1) / k);
			for (ll i = 0; i < ssize(b); ++i)
				b[i] = reduce(a.begin() + k * i, a.begin() + min<ll>(ssize(a), k * (i + 1)));
		}
		ll sum(ll l, ll r) const {
			ll lk = (l + k - 1) / k, rk = r / k;
			if (lk >= rk)
				return reduce(a.begin() + l, a.begin() + r);
			else
				return reduce(a.begin() + l, a.begin() + lk * k) + reduce(b.begin() + lk, b.begin() + rk) + reduce(a.begin() + rk * k, a.begin() + r);
		}
		void add(ll i, ll x) {
			a[i] += x;
			b[i / k] += x;
		}
		ll k;
		vector<ll> a, b;
	};
}

TEST(C270SquareRootAlgorithms, RootBlock) {
	RootBlock r({});
	EXPECT_EQ(r.sum(0, 0), 0);
	r = RootBlock({5,8,6,3,2,7,2,6,7,1,7,5,6,2,3,2});
	EXPECT_EQ(r.k, 4);
	EXPECT_EQ(r.b, (vector<ll>{22,17,20,13}));
	EXPECT_EQ(r.a, (vector<ll>{5,8,6,3,2,7,2,6,7,1,7,5,6,2,3,2}));
	r.add(5, -2);
	EXPECT_EQ(r.k, 4);
	EXPECT_EQ(r.b, (vector<ll>{22,15,20,13}));
	EXPECT_EQ(r.a, (vector<ll>{5,8,6,3,2,5,2,6,7,1,7,5,6,2,3,2}));
	EXPECT_EQ(r.sum(1, 4), 17);
	EXPECT_EQ(r.sum(3, 14), 46);
}
