#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct Ancestor {
		Ancestor(const vector<vector<ll>>& adj, ll x)
			: a(bit_width(adj.size() - 1), vector<ll>(adj.size() + 1)) {
			if (a.empty())
				return;
			auto& b = a;
			auto dfs = [&](this auto self, ll s, ll e) -> void {
				b[0][s + 1] = e + 1;
				for (ll u : adj[s]) {
					if (u != e) {
						self(u, s);
					}
				}
				};
			dfs(x, -1);
			for (ll i = 1; i < ssize(a); ++i) {
				for (ll j = 0; j < ssize(a[i - 1]); ++j) {
					a[i][j] = a[i - 1][a[i - 1][j]];
				}
			}
		}
		ll operator()(ll x, ll k) const {
			++x;
			for (const auto& f : a) {
				if (k & 1)
					x = f[x];
				k >>= 1;
			}
			return (k <= 0) ? x - 1 : -1;
		}
	private:
		vector<vector<ll>> a;
	};
}

TEST(C181FindingAncestors, Ancestor) {
	EXPECT_EQ(Ancestor({ {} }, 0)(0, 0), 0);
	Ancestor ancestor({ {3,4,1},{0,5},{3},{0,2,6},{0},{1},{3,7},{6} }, 0);
	EXPECT_EQ(ancestor(1, 1), 0);
	EXPECT_EQ(ancestor(7, 2), 3);
	EXPECT_EQ(ancestor(7, 17), -1);
}
