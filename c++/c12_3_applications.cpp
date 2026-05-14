#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c12_3_applications.h"

namespace {
	bool finding_cycles(const vector<vector<ll>>& adj) {
		ll n = ssize(adj);
		vector<bool> visited(n);
		auto dfs = [&](this auto self, ll s, ll e) {
			if (visited[s])
				return true;
			visited[s] = true;
			for (ll u : adj[s]) {
				if (u != e && self(u, s)) {
					return true;
				}
			}
			return false;
			};
		for (ll i = 0; i < n; ++i) {
			if (!visited[i] && dfs(i, -1)) {
				return true;
			}
		}
		return false;
	}

	bool finding_cycles2(const vector<vector<ll>>& adj) {
		for (const auto& c : connected(adj)) {
			ll sum = 0;
			for (ll i : c)
				sum += ssize(adj[i]);
			if (sum != 2 * ssize(c) - 2)
				return true;
		}
		return false;
	}

	optional<vector<ll>> bipartiteness_check(const vector<vector<ll>>& adj) {
		ll n = ssize(adj);
		vector<ll> color(n, -1);
		auto dfs = [&](this auto self, ll s, ll c) {
			if (color[s] >= 0)
				return color[s] == c;
			color[s] = c;
			for (ll u : adj[s]) {
				if (!self(u, 1 - c)) {
					return false;
				}
			}
			return true;
			};
		for (ll i = 0; i < n; ++i) {
			if (color[i] < 0 && !dfs(i, 0)) {
				return nullopt;
			}
		}
		return color;
	}
}

vector<vector<ll>> connected(const vector<vector<ll>>& adj) {
	ll n = ssize(adj);
	vector<bool> visited(n);
	vector<vector<ll>> ret;
	auto dfs = [&](this auto self, ll s) {
		if (visited[s]) return;
		visited[s] = true;
		ret.back().push_back(s);
		for (ll u : adj[s])
			self(u);
		};
	for (ll i = 0; i < n; ++i)
		if (!visited[i]) {
			ret.resize(ret.size() + 1);
			dfs(i);
		}
	return ret;
}

TEST(C123Applications, connected) {
	EXPECT_EQ(connected({}), vector<vector<ll>>{});
	EXPECT_EQ(connected({ {} }), vector<vector<ll>>{{0}});
	EXPECT_EQ(connected({ {2,3},{4},{0,3},{0,2},{1} }), (vector<vector<ll>>{{0,2,3},{1,4}}));
}

TEST(C123Applications, findingCycles) {
	EXPECT_FALSE(finding_cycles({ {} }));
	EXPECT_TRUE(finding_cycles({ {2,3},{2,4},{0,1,3,4},{0,2},{1,2} }));
	EXPECT_TRUE(finding_cycles({ {},{2,3},{3,1},{1,2} }));
}

TEST(C123Applications, findingCycles2) {
	EXPECT_FALSE(finding_cycles2({ {} }));
	EXPECT_TRUE(finding_cycles2({ {2,3},{2,4},{0,1,3,4},{0,2},{1,2} }));
	EXPECT_TRUE(finding_cycles2({ {},{2,3},{3,1},{1,2} }));
}

TEST(C123Applications, bipartitenessCheck) {
	EXPECT_EQ(bipartiteness_check({}), vector<ll>{});
	EXPECT_EQ(bipartiteness_check({ {} }), vector<ll>{{0}});
	EXPECT_EQ(bipartiteness_check({ {1,3},{0,2,4},{1,4},{0,4},{1,2,3} }), nullopt);
	EXPECT_EQ(bipartiteness_check({ {},{2,3},{3,1},{1,2} }), nullopt);
}
