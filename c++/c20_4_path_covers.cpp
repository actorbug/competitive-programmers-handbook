#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 2;
#include "c13_3_floyd_warshall_algorithm.h"
#include "c20_3_maximum_matchings.h"

namespace {
	struct Connect {
		Connect(ll l) : adj(l), start(views::iota(1ll, l) | ranges::to<unordered_set>()) {}
		void add(ll i, ll j) {
			adj[i].push_back(j);
			start.erase(j);
		}
		vector<vector<ll>> routes() {
			vector<vector<ll>> ret;
			for (ll i : start) {
				ret.resize(ret.size() + 1);
				auto& r = ret.back();
				r.push_back(i);
				while (!adj[r.back()].empty()) {
					ll j = r.back();
					r.push_back(adj[j].back());
					adj[j].pop_back();
				}
			}
			return ret;
		}
	private:
		vector<vector<ll>> adj;
		unordered_set<ll> start;
	};

	vector<vector<ll>> node_disjoint(const vector<vector<ll>>& adj) {
		ll l = ssize(adj);
		vector<pair<ll, ll>> edges;
		for (ll i = 1; i < l; ++i) {
			for (ll j : adj[i]) {
				edges.emplace_back(i, j + l);
			}
		}
		Connect con(l);
		for (auto [i, j] : maximum_matching(edges))
			con.add(i, j - l);
		return con.routes();
	}

	vector<vector<ll>> general(const vector<vector<ll>>& adj) {
		ll l = ssize(adj);
		vector<vector<ll>> adj2(l, vector<ll>(l));
		for (ll i = 1; i < l; ++i) {
			for (ll j : adj[i]) {
				adj2[i][j] = 1;
			}
		}
		auto distance = floyd_warshall(adj2);
		vector<pair<ll, ll>> edges;
		for (ll i = 1; i < l; ++i) {
			for (ll j = 1; j < l; ++j) {
				if (0 < distance[i][j] && distance[i][j] < INF) {
					edges.emplace_back(i, j + l);
				}
			}
		}
		Connect con(l);
		for (auto [i, j] : maximum_matching(edges)) {
			j -= l;
			while (distance[i][j] > 1) {
				for (ll k = 1; k < l; ++k) {
					if (distance[k][j] == distance[i][j] - 1) {
						con.add(i, k);
						i = k;
						break;
					}
				}
			}
			con.add(i, j);
		}
		return con.routes();
	}

	void test_node_disjoint(const vector<vector<ll>>& adj, ll l) {
		auto ret = node_disjoint(adj);
		EXPECT_EQ(ret.size(), l);
		unordered_multiset<ll> all;
		for (const auto& r : ret)
			all.insert(r.begin(), r.end());
		EXPECT_EQ(all, views::iota(1ll, ll(ssize(adj))) | ranges::to<unordered_multiset>());
		for (const auto& r : ret) {
			for (auto [a, b] : r | views::pairwise) {
				EXPECT_TRUE(ranges::find(adj[a], b) != adj[a].end());
			}
		}
	}

	void test_general(const vector<vector<ll>>& adj, ll l) {
		auto ret = general(adj);
		EXPECT_EQ(ret.size(), l);
		unordered_set<ll> all;
		for (const auto& r : ret)
			all.insert(r.begin(), r.end());
		EXPECT_EQ(all, views::iota(1ll, ll(ssize(adj))) | ranges::to<unordered_set>());
		for (const auto& r : ret) {
			for (auto [a, b] : r | views::pairwise) {
				EXPECT_TRUE(ranges::find(adj[a], b) != adj[a].end());
			}
		}
	}
}

TEST(C204PathCovers, nodeDisjoint) {
	test_node_disjoint({ {},{2},{} }, 1);
	test_node_disjoint({ {},{5},{6},{4},{},{6},{3,7},{} }, 3);
}

TEST(C204PathCovers, general) {
	test_general({ {},{2},{} }, 1);
	test_general({ {},{5},{6},{4},{},{6},{3,7},{} }, 2);
}
