#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c17_1_kosarajus_algorithm.h"
#include "util.h"

namespace {
	void test(const vector<vector<ll>>& adj, const vector<vector<ll>>& expected) {
		auto ret = kosaraju(adj);
		for (auto& r : ret)
			ranges::sort(r);
		ranges::sort(ret);
		EXPECT_EQ(ret, expected);
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
	test({}, {});
	test({ {1,3},{0,4},{1,6},{},{3},{2,4},{5} }, { {0,1},{2,5,6},{3},{4} });
}
