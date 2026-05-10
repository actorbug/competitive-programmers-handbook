#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	vector<ll> all_longest_paths(const vector<vector<ll>>& adj) {
		vector<vector<pair<ll, ll>>> maxLength(adj.size());
		auto dfs = [&](this auto self, ll s, ll e) -> ll {
			maxLength[s].assign(3, { 0, s });
			for (auto u : adj[s]) {
				if (u != e) {
					maxLength[s][2] = { self(u, s) + 1, u };
					ranges::push_heap(maxLength[s], greater());
					ranges::pop_heap(maxLength[s], greater());
				}
			}
			return maxLength[s][1].first;
			};
		dfs(0, -1);
		auto dfs2 = [&](this auto self, ll s, ll e) -> void {
			for (auto u : adj[s]) {
				if (u != e) {
					maxLength[u][2] = { maxLength[s][maxLength[s][1].second != u].first + 1, s };
					ranges::push_heap(maxLength[u], greater());
					ranges::pop_heap(maxLength[u], greater());
					self(u, s);
				}
			}
			};
		dfs2(0, -1);
		return maxLength | views::transform([&](const auto& v) { return v[1].first; }) | ranges::to<vector>();
	}
}

TEST(C143AllLongestPaths, allLongestPaths) {
	EXPECT_EQ(all_longest_paths({ {} }), vector<ll>{0});
	EXPECT_EQ(all_longest_paths({ {1,2,3},{0,4,5},{0},{0},{1},{1} }), (vector<ll>{2,2,3,3,3,3}));
}
