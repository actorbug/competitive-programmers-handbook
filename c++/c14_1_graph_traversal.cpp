#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	void graph_traversal(const vector<vector<ll>>& adj, ll x, auto f) {
		auto dfs = [&](this auto self, ll s, ll e) -> void {
			// process node s
			f(s);
			for (auto u : adj[s]) {
				if (u != e) self(u, s);
			}
			};
		dfs(x, 0);
	}
	vector<ll> dynamic_programming(const vector<vector<ll>>& adj, ll x) {
		vector<ll> count(adj.size(), 1);
		auto dfs = [&](this auto self, ll s, ll e) -> void {
			for (auto u : adj[s]) {
				if (u == e) continue;
				self(u, s);
				count[s] += count[u];
			}
			};
		dfs(x, 0);
		return count;
	}
}

TEST(C141GraphTraversal, graphTraversal) {
	vector<ll> ret;
	graph_traversal({ {},{} }, 1, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, vector<ll>{1});
	ret.clear();
	graph_traversal({ {},{2,3,4},{1,5,6},{1},{1,7},{2},{2,8},{4},{6} }, 1, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, (vector<ll>{1,2,5,6,8,3,4,7}));
}

TEST(C141GraphTraversal, dynamicProgramming) {
	EXPECT_EQ(dynamic_programming({ {},{} }, 1), (vector<ll>{ 1,1 }));
	EXPECT_EQ(dynamic_programming({ {},{2,3,4},{1,5,6},{1},{1,7},{2},{2,8},{4},{6} }, 1), (vector<ll>{ 1,8,4,1,2,1,2,1,1 }));
}
