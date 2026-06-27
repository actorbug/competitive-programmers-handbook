#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c20_1_ford_fulkerson_algorithm.h"

namespace {
	vector<vector<ll>> edge_disjoint(const vector<vector<ll>>& adj, ll s, ll e) {
		ll n = ssize(adj);
		vector<vector<pair<ll, ll>>> adj2(n);
		for (ll i = 1; i < n; ++i) {
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

	void test_edge(const vector<vector<ll>>& adj, ll s, ll e, ll l) {
		set<pair<ll, ll>> edges;
		for (ll i = 0; i < ssize(adj); ++i) {
			for (ll j : adj[i]) {
				edges.emplace(i, j);
			}
		}
		auto ret = edge_disjoint(adj, s, e);
		EXPECT_EQ(ret.size(), l);
		for (const auto& r : ret) {
			for (auto p : r | views::pairwise) {
				EXPECT_TRUE(edges.contains(p));
				edges.erase(p);
			}
		}
	}

	void test_node(const vector<vector<ll>>& adj, ll s, ll e, ll l) {
		auto nodes = views::iota(1ll, ll(ssize(adj))) | ranges::to<unordered_set>();
		nodes.erase(s);
		nodes.erase(e);
		auto ret = node_disjoint(adj, s, e);
		EXPECT_EQ(ret.size(), l);
		for (const auto& r : ret) {
			for (ll i = 1; i < ssize(r) - 1; ++i) {
				EXPECT_TRUE(nodes.contains(r[i]));
				nodes.erase(r[i]);
			}
		}
		for (const auto& r : ret) {
			for (auto [a, b] : r | views::pairwise) {
				EXPECT_TRUE(ranges::find(adj[a], b) != adj[a].end());
			}
		}
	}
}

TEST(C202DisjointPaths, edgeDisjoint) {
	test_edge({{},{2},{}}, 1, 2, 1);
	test_edge({{},{2,4},{4},{2,5,6},{3,5},{6},{}}, 1, 6, 2);
}

TEST(C202DisjointPaths, nodeDisjoint) {
	test_node({{},{2},{}}, 1, 2, 1);
	test_node({{},{2,4},{4},{2,5,6},{3,5},{6},{}}, 1, 6, 1);
}
