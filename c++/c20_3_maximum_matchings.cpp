#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "c20_1_ford_fulkerson_algorithm.h"
#include "c20_3_maximum_matchings.h"

namespace {
	bool halls_theorem(const vector<pair<ll, ll>>& edges) {
		unordered_map<ll, ll> left, right;
		for (auto [s, e] : edges) {
			if (!left.contains(s))
				left[s] = ssize(left);
			if (!right.contains(e))
				right[e] = ssize(right);
		}
		vector<ull> adj(left.size());
		for (auto [s, e] : edges)
			adj[left[s]] |= 1ull << right[e];
		for (ull i = 0; i < (1ull << left.size()); ++i) {
			ull r = 0;
			for (ll j = 0; j < ssize(left); ++j) {
				if (i & (1ull << j)) {
					r |= adj[j];
				}
			}
			if (popcount(i) > popcount(r))
				return false;
		}
		return true;
	}
}

vector<pair<ll, ll>> maximum_matching(const vector<pair<ll, ll>>& edges) {
	ll m = 0;
	for (auto [s, e] : edges)
		m = max({ m, s, e });
	vector<vector<pair<ll, ll>>> adj(m + 3);
	for (auto [s, e] : edges) {
		adj[m + 1].emplace_back(s, 1);
		adj[s].emplace_back(e, 1);
		adj[e].emplace_back(m + 2, 1);
	}
	auto adj2 = edmonds_karp(adj, m + 1, m + 2);
	vector<pair<ll, ll>> ret;
	for (auto [s, e] : edges) {
		if (adj2[s][e] == 0) {
			ret.emplace_back(s, e);
		}
	}
	return ret;
}

TEST(C203MaximumMatchings, maximumMatching) {
	EXPECT_EQ(maximum_matching({{0,1}}).size(), 1);
	EXPECT_EQ(maximum_matching({{0,4},{1,6},{2,4},{2,5},{2,7},{3,6}}).size(), 3);
}

TEST(C203MaximumMatchings, hallsTheorem) {
	EXPECT_TRUE(halls_theorem({ {0,1} }));
	EXPECT_FALSE(halls_theorem({ {0,4},{1,6},{2,4},{2,5},{2,7},{3,6} }));
}
