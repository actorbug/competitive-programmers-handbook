#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

namespace {
	bool ore(const vector<vector<ll>>& adj) {
		ll n = ssize(adj);
		auto adj2 = adj | views::transform(ranges::to<unordered_set>()) | ranges::to<vector>();
		for (ll i = 0; i < n - 1; ++i) {
			for (ll j = i + 1; j < n; ++j) {
				if (!adj2[i].contains(j) && ssize(adj[i]) + ssize(adj[j]) < n) {
					return false;
				}
			}
		}
		return true;
	}

	vector<ll> construction(const vector<vector<ll>>& adj) {
		ll n = ssize(adj);
		vector<ll> adj2(adj.size());
		for (ll i = 0; i < n; ++i) {
			for (ll j : adj[i]) {
				adj2[i] |= 1ll << j;
			}
		}
		vector<ll> dp(1ll << n);
		for (ll s = 1; s < 1ll << n; ++s) {
			if ((s & (s - 1)) == 0)
				dp[s] = s;
			else {
				for (ll i = s; i != 0; i &= i - 1) {
					ll j = i & -i;
					if (dp[s ^ j] & adj2[bit_width(ull(j)) - 1])
						dp[s] |= j;
				}
			}
		}
		ll s = (1ll << n) - 1;
		vector<ll> ret;
		while (s) {
			ll i = dp[s] & -dp[s];
			ret.push_back(bit_width(ull(i)) - 1);
			s ^= i;
		}
		return ret;
	}
}

TEST(C192HamiltonianPath, ore) {
	EXPECT_TRUE(ore({}));
	EXPECT_FALSE(ore({ {1,3},{0,2,4},{1,4},{0,4},{1,2,3} }));
}

TEST(C192HamiltonianPath, construction) {
	EXPECT_EQ(construction({}), vector<ll>{});
	EXPECT_EQ(construction({ {1,3},{0,2,4},{1,4},{0,4},{1,2,3} }), (vector<ll>{ 0,1,2,3,4 }));
}
