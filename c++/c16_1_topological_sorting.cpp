#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c16_1_topological_sorting.h"

vector<ll> topological(const vector<vector<ll>>& adj) {
	ll n = ssize(adj);
	vector<ll> visited(n), ret;
	auto dfs = [&](this auto self, ll s) {
		if (visited[s])
			return visited[s] != 1;
		visited[s] = 1;
		if (!ranges::all_of(adj[s], self))
			return false;
		ret.push_back(s);
		visited[s] = 2;
		return true;
		};
	for (ll x = 0; x < n; ++x) {
		if (!visited[x] && !dfs(x)) {
			return {};
		}
	}
	ranges::reverse(ret);
	return ret;
}

TEST(C161TopologicalSorting, topological) {
	EXPECT_EQ(topological({}), vector<ll>{});
	EXPECT_EQ(topological({ {1},{2},{5},{0,4},{1,2},{} }), (vector<ll>{ 3,4,0,1,2,5}));
	EXPECT_EQ(topological({ {1},{2},{4,5},{0,4},{1},{} }), vector<ll>{});
}
