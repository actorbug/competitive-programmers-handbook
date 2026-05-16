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
		ll s = (1ll << n) - 1, prev = s;
		vector<ll> ret;
		while (s) {
			ll c = prev & dp[s], i = c & -c, j = bit_width(ull(i)) - 1;
			ret.push_back(j);
			prev = adj2[j];
			s ^= i;
		}
		return ret;
	}

	void test(const vector<vector<ll>>& adj) {
		auto ret = construction(adj);
		for (auto [i, j] : ret | views::pairwise)
			EXPECT_TRUE(ranges::find(adj[i], j) != adj[i].end());
		ranges::sort(ret);
		for (ll i = 0; i < ssize(ret); ++i)
			EXPECT_EQ(ret[i], i);
	}
}

TEST(C192HamiltonianPath, ore) {
	EXPECT_TRUE(ore({}));
	EXPECT_FALSE(ore({ {1,3},{0,2,4},{1,4},{0,4},{1,2,3} }));
}

TEST(C192HamiltonianPath, construction) {
	test({});
	test({ {1,3},{0,2,4},{1,4},{0,4},{1,2,3} });
}
