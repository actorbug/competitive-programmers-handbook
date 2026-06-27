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
	search({ {},{} }, 1, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, vector<ll>{1});
	ret.clear();
	search({ {},{2,4},{1,3,5},{2,5},{1},{2,3} }, 1, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, (vector<ll>{1, 2, 3, 5, 4}));
}
