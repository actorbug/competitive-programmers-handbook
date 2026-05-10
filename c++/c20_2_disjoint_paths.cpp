#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c20_1_ford_fulkerson_algorithm.h"

namespace {
	vector<vector<ll>> edge_disjoint(const vector<vector<ll>>& adj, ll s, ll e) {
		ll n = ssize(adj);
		vector<vector<pair<ll, ll>>> adj2(n);
		for (ll i = 0; i < n; ++i) {
			for (auto j : adj[i]) {
				adj2[i].emplace_back(j, 1);
			}
		}
		auto adj3 = edmonds_karp(adj2, s, e);
		vector<vector<ll>> ret(adj2tc(adj3, e));
		for (auto& r : ret) {
			r.push_back(s);
			while (r.back() != e) {
				for (ll i : adj[r.back()]) {
					if (adj3[i][r.back()] > 0) {
						adj3[i][r.back()] = 0;
						r.push_back(i);
						break;
					}
				}
			}
		}
		return ret;
	}

	vector<vector<ll>> node_disjoint(const vector<vector<ll>>& adj, ll s, ll e) {
		ll l = ssize(adj);
		vector<vector<ll>> adj2(adj.size());
		for (ll i = 0; i < l; ++i) {
			if (i != s && i != e) {
				adj2[i].push_back(i + l);
			}
		}
		adj2.insert(adj2.end(), adj.begin(), adj.end());
		vector<vector<ll>> ret;
		for (const auto& r : edge_disjoint(adj2, s + l, e)) {
			ret.resize(ret.size() + 1);
			ret.back().push_back(s);
			for (ll i = 1; i < ssize(r); i += 2)
				ret.back().push_back(r[i]);
		}
		return ret;
	}
}

TEST(C202DisjointPaths, edgeDisjoint) {
	EXPECT_EQ(edge_disjoint({{1},{}}, 0, 1).size(), 1);
	EXPECT_EQ(edge_disjoint({{1,3},{3},{1,4,5},{2,4},{5},{}}, 0, 5).size(), 2);
}

TEST(C202DisjointPaths, nodeDisjoint) {
	EXPECT_EQ(node_disjoint({{1},{}}, 0, 1).size(), 1);
	EXPECT_EQ(node_disjoint({{1,3},{3},{1,4,5},{2,4},{5},{}}, 0, 5).size(), 1);
}
