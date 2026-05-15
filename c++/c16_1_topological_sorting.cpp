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
	vector<vector<ll>> adj = { {1},{2},{5},{0,4},{1,2},{} };
	unordered_map<ll, ll> pos;
	for (auto [i, a] : topological(adj) | views::enumerate)
		pos[a] = i;
	for (ll a = 0; a < ssize(adj); ++a) {
		for (ll b : adj[a]) {
			EXPECT_LT(pos[a], pos[b]);
		}
	}
	EXPECT_EQ(topological({ {1},{2},{4,5},{0,4},{1},{} }), vector<ll>{});
}
