#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c12_3_applications.h"
#include "c15_2_union_find_structure.h"

namespace {
	vector<vector<pair<ll, ll>>> kruskal(const vector<vector<pair<ll, ll>>>& adj) {
		ll n = ssize(adj);
		vector<tuple<ll, ll, ll>> edges;
		for (ll a = 0; a < n; ++a)
			for (auto [b, w] : adj[a])
				edges.emplace_back(w, a, b);
		ranges::sort(edges);
		UnionFind uf(n);
		vector<vector<pair<ll, ll>>> ret(n);
		for (auto [w, a, b] : edges) {
			if (!uf.same(a, b)) {
				uf.unite(a, b);
				ret[a].emplace_back(b, w);
				ret[b].emplace_back(a, w);
			}
		}
		return ret;
	}
}

TEST(C151KruskalsAlgorithm, kruskal) {
	EXPECT_EQ(kruskal({}), (vector<vector<pair<ll, ll>>>{}));
	auto ret = kruskal({ {{1,3},{4,5}},{{0,3},{2,5},{4,6}},{{1,5},{3,9},{5,3}},{{2,9},{5,7}},{{0,5},{1,6},{5,2}},{{2,3},{3,7},{4,2}} });
	ll sum = 0;
	for (const auto& v : ret)
		for (auto [_, w] : v)
			sum += w;
	EXPECT_EQ(sum, 20 * 2);
	vector<vector<ll>> adj(ret.size());
	for (ll i = 0; i < ssize(ret); ++i)
		for (auto [u, _] : ret[i])
			adj[i].push_back(u);
	EXPECT_EQ(connected(adj).size(), 1);
}
