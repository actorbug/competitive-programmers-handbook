#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c17_1_kosarajus_algorithm.h"
#include "util.h"

vector<ll> kosaraju(const vector<vector<ll>>& adj) {
	ll n = ssize(adj);
	vector<bool> visited(n);
	auto dfs = [&](this auto self, const vector<vector<ll>>& adj, ll x, auto f) {
		if (visited[x])
			return;
		visited[x] = true;
		for (ll u : adj[x])
			self(adj, u, f);
		f(x);
		};
	vector<ll> nodes;
	for (ll x = 0; x < n; ++x) {
		if (!visited[x]) {
			dfs(adj, x, [&](ll u) { nodes.push_back(u); });
		}
	}
	auto radj = reversedAdj(adj);
	visited.assign(n, false);
	vector<ll> ret(n);
	for (ll count = 0; ll x : nodes | views::reverse) {
		if (!visited[x]) {
			dfs(radj, x, [&](ll u) { ret[u] = count; });
			++count;
		}
	}
	return ret;
}

TEST(C171KosarajusAlgorithm, kosaraju) {
	EXPECT_EQ(kosaraju({}), vector<ll>{});
	EXPECT_EQ(kosaraju({ {1,3},{0,4},{1,6},{},{3},{2,4},{5} }), (vector<ll>{ 1, 1, 0, 3, 2, 0, 0 }));
}
