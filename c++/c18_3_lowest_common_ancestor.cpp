#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "c09_1_static_array_queries.h"

namespace {
	struct Doubling {
		Doubling(const vector<vector<ll>>& adj, ll x)
			: depth(adj.size()), anc(bit_width(adj.size() - 2), vector<ll>(adj.size())) {
			if (anc.empty())
				return;
			auto& anc_ = anc;
			auto& depth_ = depth;
			auto dfs = [&](this auto self, ll s, ll e, ll d) -> void {
				anc_[0][s] = e;
				depth_[s] = d;
				for (ll u : adj[s]) {
					if (u != e) {
						self(u, s, d + 1);
					}
				}
				};
			dfs(x, 0, 1);
			for (ll i = 1; i < ssize(anc); ++i) {
				for (ll j = 1; j < ssize(anc[i - 1]); ++j) {
					anc[i][j] = anc[i - 1][anc[i - 1][j]];
				}
			}
		}
		ll ancestor(ll x, ll k) const {
			for (const auto& f : anc) {
				if (k & 1)
					x = f[x];
				k >>= 1;
			}
			return (k <= 0) ? x : 0;
		}
		ll operator()(ll a, ll b) const {
			if (depth[a] < depth[b])
				swap(a, b);
			a = ancestor(a, depth[a] - depth[b]);
			if (a == b)
				return a;
			for (const auto& f : anc | views::reverse) {
				if (f[a] != f[b]) {
					a = f[a]; b = f[b];
				}
			}
			return anc[0][a];
		}
		ll distance(ll a, ll b) const {
			return depth[a] + depth[b] - 2 * depth[(*this)(a, b)];
		}
	private:
		vector<ll> depth;
		vector<vector<ll>> anc;
	};

	struct Euler {
		Euler(const vector<vector<ll>>& adj, ll x) : p(adj.size()), d(init(adj, x, p)) {}
		ll operator()(ll a, ll b) const {
			if (p[a] > p[b])
				swap(a, b);
			return d(p[a], p[b]).second;
		}
		ll distance(ll a, ll b) const {
			ll pa = p[a], pb = p[b], pc = p[(*this)(a, b)];
			return d(pa, pa).first + d(pb, pb).first - 2 * d(pc, pc).first;
		}
	private:
		static vector<pair<ll, ll>> init(const vector<vector<ll>>& adj, ll x, vector<ll>& p) {
			vector<pair<ll, ll>> depth;
			auto dfs = [&](this auto self, ll s, ll t, ll d) -> void {
				p[s] = ssize(depth);
				depth.emplace_back(d, s);
				for (ll u : adj[s]) {
					if (u != t) {
						self(u, s, d + 1);
						depth.emplace_back(d, s);
					}
				}
				};
			dfs(x, 0, 1);
			return depth;
		}
		vector<ll> p;
		MinimumQueries<pair<ll, ll>> d;
	};

	template<class T>
	void test() {
		T a({ {},{} }, 1);
		EXPECT_EQ(a(1, 1), 1);
		EXPECT_EQ(a.distance(1, 1), 0);
		a = T({ {},{2,3,4},{1,5,6},{1},{1,7},{2},{2,8},{4},{6} }, 1);
		EXPECT_EQ(a(5, 8), 2);
		EXPECT_EQ(a.distance(5, 8), 3);
	}
}

TEST(C183LowestCommonAncestor, Doubling) {
	test<Doubling>();
}

TEST(C183LowestCommonAncestor, Euler) {
	test<Euler>();
}
