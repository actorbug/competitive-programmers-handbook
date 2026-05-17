#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c17_1_kosarajus_algorithm.h"
#include "util.h"

namespace {
	multiset<multiset<ll>> convert(const vector<vector<ll>>& vec) {
		return vec | views::transform(ranges::to<multiset>()) | ranges::to<multiset>();
	}
}

vector<vector<ll>> kosaraju(const vector<vector<ll>>& adj) {
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
	auto radj = reversed_adj(adj);
	visited.assign(n, false);
	vector<vector<ll>> ret;
	for (ll x : nodes | views::reverse) {
		if (!visited[x]) {
			ret.resize(ret.size() + 1);
			dfs(radj, x, [&](ll u) { ret.back().push_back(u); });
		}
	}
	return ret;
}

TEST(C171KosarajusAlgorithm, kosaraju) {
	EXPECT_EQ(convert(kosaraju({})), multiset<multiset<ll>>{});
	EXPECT_EQ(convert(kosaraju({ {1,3},{0,4},{1,6},{},{3},{2,4},{5} })), (multiset<multiset<ll>>{ {0,1},{2,5,6},{3},{4} }));
}
