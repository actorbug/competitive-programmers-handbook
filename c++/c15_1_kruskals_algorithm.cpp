#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c15_2_union_find_structure.h"

namespace {
	vector<tuple<ll, ll, ll>> kruskal(ll n, vector<tuple<ll, ll, ll>> edges) {
		ranges::sort(edges, {}, [](const auto& t) { return get<2>(t); });
		UnionFind uf(n);
		vector<tuple<ll, ll, ll>> ret;
		for (auto [a, b, w] : edges) {
			if (!uf.same(a, b)) {
				uf.unite(a, b);
				ret.emplace_back(a, b, w);
				ret.emplace_back(b, a, w);
			}
		}
		return ret;
	}
}

TEST(C151KruskalsAlgorithm, kruskal) {
	EXPECT_EQ(kruskal(0, {}), (vector<tuple<ll, ll, ll>>{}));
	auto ret = kruskal(6, { {0,1,3},{0,4,5},{1,0,3},{1,2,5},{1,4,6},{2,1,5},{2,3,9},{2,5,3},{3,2,9},{3,5,7},{4,0,5},{4,1,6},{4,5,2},{5,2,3},{5,3,7},{5,4,2} });
	ranges::sort(ret);
	EXPECT_EQ(ret, (vector<tuple<ll, ll, ll>>{ {0,1,3},{0,4,5},{1,0,3},{2,5,3},{3,5,7},{4,0,5},{4,5,2},{5,2,3},{5,3,7},{5,4,2} }));
}
