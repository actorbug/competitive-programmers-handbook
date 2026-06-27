#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c15_2_union_find_structure.h"

namespace {
	vector<ll> merging(const vector<vector<ll>>& adj, const vector<ll>& val, ll x, const vector<pair<ll, ll>>& q) {
		vector<ll> a(q.size());
		vector<vector<ll>> r(adj.size());
		for (ll i = 0; i < ssize(q); ++i)
			r[q[i].first].push_back(i);
		vector<unordered_map<ll, ll>> d(adj.size());
		for (ll i = 1; i < ssize(adj); ++i)
			d[i][val[i]] = 1;
		auto dfs = [&](this auto self, ll s, ll e) -> void {
			for (ll u : adj[s]) {
				if (u != e) {
					self(u, s);
					if (d[u].size() > d[s].size())
						swap(d[u], d[s]);
					for (auto [i, j] : d[u])
						d[s][i] += j;
				}
			}
			for (ll i : r[s])
				a[i] = d[s][q[i].second];
			};
		dfs(x, 0);
		return a;
	}

	vector<ll> lca(const vector<vector<ll>>& adj, ll x, const vector<pair<ll, ll>>& q) {
		ll n = ssize(adj);
		vector<ll> a(q.size());
		vector<vector<pair<ll, ll>>> r(n);
		for (ll i = 0; i < ssize(q); ++i) {
			auto [j, k] = q[i];
			r[j].emplace_back(i, k);
			r[k].emplace_back(i, j);
		}
		UnionFind uf(n);
		vector<ll> value(n);
		vector<bool> visited(n);
		auto dfs = [&](this auto self, ll s, ll e) -> void {
			for (auto [i, k] : r[s]) {
				if (visited[k]) {
					a[i] = value[uf.find(k)];
				}
			}
			visited[s] = true;
			for (ll u : adj[s]) {
				if (u != e) {
					self(u, s);
					uf.unite(u, s);
					value[uf.find(s)] = s;
				}
			}
			};
		dfs(x, 0);
		return a;
	}
}

TEST(C184OfflineAlgorithms, merging) {
	EXPECT_EQ(merging({ {},{} }, { 0,3 }, 1, {}), vector<ll>{});
	EXPECT_EQ(merging({ {},{2,3,4,5},{1,6},{1},{1,7,8,9},{1},{2},{4},{4},{4} }, { 0,2,3,5,3,1,4,4,3,1 }, 1, { {4,3} }), vector<ll>{2});
}

TEST(C184OfflineAlgorithms, lca) {
	EXPECT_EQ(lca({ {},{} }, 1, {}), vector<ll>{});
	EXPECT_EQ(lca({ {},{2,3,4},{1,5,6},{1},{1,7},{2},{2,8},{4},{6} }, 1, { {5,8},{2,7} }), (vector<ll>{2,1}));
}
