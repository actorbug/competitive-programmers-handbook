#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "util.h"
#include "c12_3_applications.h"
#include "c15_2_union_find_structure.h"

namespace {
	vector<vector<pair<ll, ll>>> kruskal(const vector<vector<pair<ll, ll>>>& adj) {
		ll n = ssize(adj);
		vector<tuple<ll, ll, ll>> edges;
		for (ll a = 1; a < n; ++a)
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
	EXPECT_EQ(kruskal({ {} }), (vector<vector<pair<ll, ll>>>{ {} }));
	auto ret = kruskal({ {},{{2,3},{5,5}},{{1,3},{3,5},{5,6}},{{2,5},{4,9},{6,3}},{{3,9},{6,7}},{{1,5},{2,6},{6,2}},{{3,3},{4,7},{5,2}} });
	ll sum = 0;
	for (const auto& v : ret)
		for (auto [_, w] : v)
			sum += w;
	EXPECT_EQ(sum, 20 * 2);
	auto adj = delweight(ret);
	EXPECT_EQ(connected(adj).size(), 1);
	EXPECT_FALSE(finding_cycles(adj));
}
