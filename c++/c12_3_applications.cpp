#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c12_3_applications.h"

namespace {
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

	optional<vector<bool>> bipartiteness_check(const vector<vector<ll>>& adj) {
		ll n = ssize(adj);
		vector<bool> visited(n);
		vector<bool> color(n);
		auto dfs = [&](this auto self, ll s, bool c) {
			if (visited[s])
				return color[s] == c;
			visited[s] = true;
			color[s] = c;
			for (ll u : adj[s]) {
				if (!self(u, !c)) {
					return false;
				}
			}
			return true;
			};
		for (ll i = 1; i < n; ++i) {
			if (!visited[i] && !dfs(i, false)) {
				return nullopt;
			}
		}
		return color;
	}

	multiset<multiset<ll>> convert(const vector<vector<ll>>& vec) {
		return vec | views::transform(ranges::to<multiset>()) | ranges::to<multiset>();
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
	for (ll i = 1; i < n; ++i)
		if (!visited[i]) {
			ret.resize(ret.size() + 1);
			dfs(i);
		}
	return ret;
}

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
	for (ll i = 1; i < n; ++i) {
		if (!visited[i] && dfs(i, 0)) {
			return true;
		}
	}
	return false;
}

TEST(C123Applications, connected) {
	EXPECT_EQ(convert(connected({ {} })), multiset<multiset<ll>>{});
	EXPECT_EQ(convert(connected({ {},{} })), multiset<multiset<ll>>{{1}});
	EXPECT_EQ(convert(connected({ {},{3,4},{5},{1,4},{1,3},{2} })), (multiset<multiset<ll>>{ {1,3,4},{2,5} }));
}

TEST(C123Applications, findingCycles) {
	EXPECT_FALSE(finding_cycles({ {},{} }));
	EXPECT_TRUE(finding_cycles({ {},{3,4},{3,5},{1,2,4,5},{1,3},{2,3} }));
	EXPECT_TRUE(finding_cycles({ {},{},{3,4},{4,2},{2,3} }));
}

TEST(C123Applications, findingCycles2) {
	EXPECT_FALSE(finding_cycles2({ {},{} }));
	EXPECT_TRUE(finding_cycles2({ {},{3,4},{3,5},{1,2,4,5},{1,3},{2,3} }));
	EXPECT_TRUE(finding_cycles2({ {},{},{3,4},{4,2},{2,3} }));
}

TEST(C123Applications, bipartitenessCheck) {
	EXPECT_EQ(bipartiteness_check({ {} }), vector<bool>{false});
	EXPECT_EQ(bipartiteness_check({ {},{} }), (vector<bool>{false,false}));
	EXPECT_EQ(bipartiteness_check({ {},{2,4},{1,3,5},{2,5},{1,5},{2,3,4} }), nullopt);
	EXPECT_EQ(bipartiteness_check({ {},{},{3,4},{4,2},{2,3} }), nullopt);
}
