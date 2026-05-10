#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	ll dynamic_programming(const vector<vector<ll>>& adj) {
		ll maxLength = 0;
		auto dfs = [&](this auto self, ll s, ll e) -> ll {
			vector<ll> toLeaf(3, -1);
			for (auto u : adj[s]) {
				if (u != e) {
					toLeaf[2] = self(u, s);
					ranges::push_heap(toLeaf, greater());
					ranges::pop_heap(toLeaf, greater());
				}
			}
			maxLength = max(maxLength, toLeaf[0] + toLeaf[1] + 2);
			return toLeaf[1] + 1;
			};
		dfs(0, -1);
		return maxLength;
	}

	ll depth_first_search(const vector<vector<ll>>& adj) {
		auto dfs = [&](this auto self, ll d, ll s, ll e) -> pair<ll, ll> {
			pair<ll, ll> ret{ d, s };
			for (auto u : adj[s]) {
				if (u != e) {
					ret = max(ret, self(d + 1, u, s));
				}
			}
			return ret;
			};
		return dfs(0, dfs(0, 0, -1).second, -1).first;
	}

	void test(auto f) {
		EXPECT_EQ(f({ {} }), 0);
		EXPECT_EQ(f({ {1,2,3},{0,4,5},{0},{0,6},{1},{1},{3} }), 4);
	}
}

TEST(C142Diameter, dynamicProgramming) {
	test(dynamic_programming);
}

TEST(C142Diameter, depthFirstSearch) {
	test(depth_first_search);
}
