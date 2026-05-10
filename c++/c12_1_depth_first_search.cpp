#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	void search(const vector<vector<ll>>& adj, ll s, auto f) {
		vector<bool> visited(adj.size());
		auto dfs = [&](this auto self, ll s) {
			if (visited[s]) return;
			visited[s] = true;
			// process node s
			f(s);
			for (auto u : adj[s]) {
				self(u);
			}
			};
		dfs(s);
	}
}

TEST(C121DepthFirstSearch, dfs) {
	vector<ll> ret;
	search({ {} }, 0, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, vector<ll>{0});
	ret.clear();
	search({ {1,3},{0,2,4},{1,4},{0},{1,2} }, 0, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, (vector<ll>{0, 1, 2, 4, 3}));
}
