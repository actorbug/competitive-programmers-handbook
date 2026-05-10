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
		dfs(x, -1);
	}
	vector<ll> dynamic_programming(const vector<vector<ll>>& adj, ll x) {
		vector<ll> count(adj.size());
		auto dfs = [&](this auto self, ll s, ll e) -> void {
			count[s] = 1;
			for (auto u : adj[s]) {
				if (u == e) continue;
				self(u, s);
				count[s] += count[u];
			}
			};
		dfs(x, -1);
		return count;
	}
}

TEST(C141GraphTraversal, graphTraversal) {
	vector<ll> ret;
	graph_traversal({ {} }, 0, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, vector<ll>{0});
	ret.clear();
	graph_traversal({ {1,2,3},{0,4,5},{0},{0,6},{1},{1,7},{3},{5} }, 0, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, (vector<ll>{0, 1, 4, 5, 7, 2, 3, 6}));
}

TEST(C141GraphTraversal, dynamicProgramming) {
	EXPECT_EQ(dynamic_programming({ {} }, 0), vector<ll>{1});
	EXPECT_EQ(dynamic_programming({ {1,2,3},{0,4,5},{0},{0,6},{1},{1,7},{3},{5} }, 0), (vector<ll>{8, 4, 1, 2, 1, 2, 1, 1}));
}
