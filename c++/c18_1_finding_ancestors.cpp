#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct Ancestor {
		Ancestor(const vector<vector<ll>>& adj, ll x)
			: a(bit_width(adj.size() - 2), vector<ll>(adj.size())) {
			if (a.empty())
				return;
			auto& b = a;
			auto dfs = [&](this auto self, ll s, ll e) -> void {
				b[0][s] = e;
				for (ll u : adj[s]) {
					if (u != e) {
						self(u, s);
					}
				}
				};
			dfs(x, 0);
			for (ll i = 1; i < ssize(a); ++i) {
				for (ll j = 1; j < ssize(a[i - 1]); ++j) {
					a[i][j] = a[i - 1][a[i - 1][j]];
				}
			}
		}
		ll operator()(ll x, ll k) const {
			for (const auto& f : a) {
				if (k & 1)
					x = f[x];
				k >>= 1;
			}
			return (k <= 0) ? x : 0;
		}
	private:
		vector<vector<ll>> a;
	};
}

TEST(C181FindingAncestors, Ancestor) {
	EXPECT_EQ(Ancestor({ {},{} }, 1)(1, 0), 1);
	Ancestor ancestor({ {},{4,5,2},{1,6},{4},{1,3,7},{1},{2},{4,8},{7} }, 1);
	EXPECT_EQ(ancestor(2, 1), 1);
	EXPECT_EQ(ancestor(8, 2), 4);
	EXPECT_EQ(ancestor(8, 17), 0);
}
