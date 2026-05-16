#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c19_1_eulerian_paths.h"
#include "util.h"

namespace {
	optional<pair<ll, ll>> existence(const vector<vector<ll>>& adj) {
		vector<ll> odd;
		for (ll i = 0; i < ssize(adj); ++i) {
			if (adj[i].size() % 2 == 1) {
				odd.push_back(i);
			}
		}
		if (odd.size() == 2)
			return make_pair(odd[0], odd[1]);
		else if (odd.size() == 0)
			return make_pair(-1, -1);
		else
			return nullopt;
	}

	optional<pair<ll, ll>> existence2(const vector<vector<ll>>& adj) {
		auto rev = reversed_adj(adj);
		unordered_map<ll, vector<ll>> d;
		for (ll i = 0; i < ssize(adj); ++i)
			d[ssize(rev[i]) - ssize(adj[i])].push_back(i);
		if (d[0].size() == adj.size() - 2 && d.contains(1) && d.contains(-1))
			return make_pair(d[-1][0], d[1][0]);
		else if (d[0].size() == adj.size())
			return make_pair(-1, -1);
		else
			return nullopt;
	}

	vector<ll> hierholzer(const vector<vector<ll>>& adj) {
		auto e = existence(adj);
		if (!e || adj.empty())
			return {};
		auto adj2 = adj | views::transform(ranges::to<unordered_set>()) | ranges::to<vector>();
		vector<ll> ret;
		auto dfs = [&](this auto self, ll s) -> void {
			while (!adj2[s].empty()) {
				ll u = *adj2[s].begin();
				adj2[s].erase(u);
				adj2[u].erase(s);
				self(u);
			}
			ret.push_back(s);
			};
		dfs(max(0ll, e->second));
		return ret;
	}

	void test_hierholzer(const vector<vector<ll>>& adj) {
		vector<vector<ll>> adj2(adj.size());
		for (auto [i, j] : hierholzer(adj) | views::pairwise) {
			adj2[i].push_back(j);
			adj2[j].push_back(i);
		}
		for (ll i = 0; i < ssize(adj); ++i)
			EXPECT_EQ(adj[i] | ranges::to<unordered_multiset>(), adj2[i] | ranges::to<unordered_multiset>());
	}

	void test_hierholzer2(const vector<vector<ll>>& adj) {
		vector<vector<ll>> adj2(adj.size());
		for (auto [i, j] : hierholzer2(adj) | views::pairwise) {
			adj2[i].push_back(j);
		}
		for (ll i = 0; i < ssize(adj); ++i)
			EXPECT_EQ(adj[i] | ranges::to<unordered_multiset>(), adj2[i] | ranges::to<unordered_multiset>());
	}

	optional<pair<ll, ll>> convert(optional<pair<ll, ll>> p) {
		if (!p || p->first <= p->second)
			return p;
		else
			return make_pair(p->second, p->first);
	}
}

vector<ll> hierholzer2(vector<vector<ll>> adj) {
	auto e = existence2(adj);
	if (!e || adj.empty())
		return {};
	vector<ll> ret;
	auto dfs = [&](this auto self, ll s) -> void {
		while (!adj[s].empty()) {
			ll u = adj[s].back();
			adj[s].pop_back();
			self(u);
		}
		ret.push_back(s);
		};
	dfs(max(0ll, e->first));
	ranges::reverse(ret);
	return ret;
}

TEST(C191EulerianPaths, existence) {
	EXPECT_EQ(convert(existence({})), make_pair(-1, -1));
	EXPECT_EQ(convert(existence({ {1,3},{0,2,4},{1,4},{0,4},{1,2,3} })), make_pair(1, 4));
	EXPECT_EQ(convert(existence({ {1,3},{0,2,3,4},{1,4},{0,1},{1,2} })), make_pair(-1, -1));
	EXPECT_EQ(convert(existence({ {1,2,3},{0,2,3},{0,1,3},{0,1,2} })), nullopt);
}

TEST(C191EulerianPaths, existence2) {
	EXPECT_EQ(existence2({}), make_pair(-1, -1));
	EXPECT_EQ(existence2({ {1},{2,4},{4},{0},{3} }), make_pair(1, 4));
	EXPECT_EQ(existence2({ {3},{0,4},{1},{1},{2} }), make_pair(-1, -1));
	EXPECT_EQ(existence2({ {1,2,3},{2,3},{3},{} }), nullopt);
}

TEST(C191EulerianPaths, hierholzer) {
	test_hierholzer({});
	test_hierholzer({ {1,3},{0,2,4},{1,4},{0,4},{1,2,3} });
	test_hierholzer({ {1,3},{0,2,3,4},{1,4},{0,1},{1,2} });
	test_hierholzer({ {1,2},{0,2,4,5},{0,1,3,5},{2,6},{1,5},{1,2,4,6},{3,5} });
}

TEST(C191EulerianPaths, hierholzer2) {
	test_hierholzer2({});
	test_hierholzer2({ {1},{2,4},{4},{0},{3} });
	test_hierholzer2({ {3},{0,4},{1},{1},{2} });
	test_hierholzer2({ {1},{2,4},{0,3},{6},{5},{1,2},{5} });
}
