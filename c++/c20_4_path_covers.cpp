#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 2;
#include "c13_3_floyd_warshall_algorithm.h"
#include "c20_3_maximum_matchings.h"

namespace {
	struct Connect {
		Connect(ll l) : adj(l), start(views::iota(0ll, l) | ranges::to<unordered_set>()) {}
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
		for (ll i = 0; i < l; ++i) {
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
		for (ll i = 0; i < l; ++i) {
			for (ll j : adj[i]) {
				adj2[i][j] = 1;
			}
		}
		auto distance = floyd_warshall(adj2);
		vector<pair<ll, ll>> edges;
		for (ll i = 0; i < l; ++i) {
			for (ll j = 0; j < l; ++j) {
				if (0 < distance[i][j] && distance[i][j] < INF) {
					edges.emplace_back(i, j + l);
				}
			}
		}
		Connect con(l);
		for (auto [i, j] : maximum_matching(edges)) {
			j -= l;
			while (distance[i][j] > 1) {
				for (ll k = 0; k < l; ++k) {
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
}

TEST(C204PathCovers, nodeDisjoint) {
	EXPECT_EQ(node_disjoint({{1},{}}).size(), 1);
	EXPECT_EQ(node_disjoint({{4},{5},{3},{},{5},{2,6},{}}).size(), 3);
}

TEST(C204PathCovers, general) {
	EXPECT_EQ(general({{1},{}}).size(), 1);
	EXPECT_EQ(general({{4},{5},{3},{},{5},{2,6},{}}).size(), 2);
}
