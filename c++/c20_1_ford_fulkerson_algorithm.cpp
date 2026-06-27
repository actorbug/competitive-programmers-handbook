#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c20_1_ford_fulkerson_algorithm.h"

namespace {
	vector<ll> prev2rroute(const vector<ll>& prev, ll e) {
		vector<ll> ret = { e };
		while (e != prev[e])
			ret.push_back(e = prev[e]);
		return ret;
	}

	vector<unordered_map<ll, ll>> ford_fulkerson(const vector<vector<pair<ll, ll>>>& adj, ll s, ll e, auto find) {
		vector<unordered_map<ll, ll>> adj2(adj.size());
		for (ll i = 1; i < ssize(adj); ++i) {
			for (auto [j, c] : adj[i]) {
				adj2[i][j] = c;
				adj2[j][i] = 0;
			}
		}
		while (true) {
			auto prev = find(adj2, s, e);
			if (prev[e] < 0)
				return adj2;
			auto rroute = prev2rroute(prev, e);
			ll mc = ranges::min(views::adjacent_transform<2>(rroute, [&](ll j, ll i) { return adj2[i][j]; }));
			for (auto [j, i] : rroute | views::pairwise) {
				adj2[i][j] -= mc;
				adj2[j][i] += mc;
			}
		}
	}

	vector<unordered_map<ll, ll>> scaling(const vector<vector<pair<ll, ll>>>& adj, ll s, ll e) {
		ll m = 0;
		for (ll i = 1; i < ssize(adj); ++i) {
			for (auto [_, c] : adj[i]) {
				m = max(m, c);
			}
		}
		auto find = [&m](const vector<unordered_map<ll, ll>>& adj2, ll s, ll e) {
			vector<ll> prev(adj2.size(), -1);
			auto dfs = [&](this auto self, ll i, ll p) {
				if (prev[i] >= 0)
					return false;
				prev[i] = p;
				if (i == e)
					return true;
				for (auto [u, c] : adj2[i])
					if (c >= m && self(u, i))
						return true;
				return false;
				};
			while (m && !dfs(s, s)) {
				m /= 2;
				prev.assign(adj2.size(), -1);
			}
			return prev;
			};
		return ford_fulkerson(adj, s, e, find);
	}

	vector<pair<ll, ll>> minimum_cuts(const vector<unordered_map<ll, ll>>& adj, ll s) {
		unordered_set<ll> visited;
		auto dfs = [&](this auto self, ll s) {
			if (visited.contains(s))
				return;
			visited.insert(s);
			for (auto [u, c] : adj[s]) {
				if (c > 0) {
					self(u);
				}
			}
			};
		dfs(s);
		vector<pair<ll, ll>> ret;
		for (ll i : visited) {
			for (auto [j, c] : adj[i]) {
				if (!visited.contains(j)) {
					ret.emplace_back(i, j);
				}
			}
		}
		return ret;
	}

	void test(const vector<vector<pair<ll, ll>>>& adj, ll s, ll e, ll tc) {
		auto ret = edmonds_karp(adj, s, e);
		ll sum = 0;
		for (auto [i, j] : minimum_cuts(ret, s)) {
			sum += ret[i][j] + ret[j][i];
		}
		EXPECT_EQ(sum, tc);
	}
}

vector<unordered_map<ll, ll>> edmonds_karp(const vector<vector<pair<ll, ll>>>& adj, ll s, ll e) {
	auto bfs = [](const vector<unordered_map<ll, ll>>& adj2, ll s, ll e) {
		queue<ll> q({ s });
		vector<ll> prev(adj2.size(), -1);
		prev[s] = s;
		while (!q.empty() && prev[e] < 0) {
			ll i = q.front(); q.pop();
			for (auto [j, c] : adj2[i]) {
				if (c > 0 && prev[j] < 0) {
					prev[j] = i;
					q.push(j);
				}
			}
		}
		return prev;
		};
	return ford_fulkerson(adj, s, e, bfs);
}

ll adj2tc(const vector<unordered_map<ll, ll>>& adj, ll e) {
	ll tc = 0;
	for (auto [_, c] : adj[e])
		tc += c;
	return tc;
}

TEST(C201FordFulkersonAlgorithm, edmondsKarp) {
	EXPECT_EQ(adj2tc(edmonds_karp({{},{{2,2}},{}}, 1, 2), 2), 2);
	EXPECT_EQ(adj2tc(edmonds_karp({{},{{2,5},{4,4}},{{3,6}},{{5,8},{6,5}},{{2,3},{5,1}},{{6,2}},{}}, 1, 6), 6), 7);
}

TEST(C201FordFulkersonAlgorithm, scaling) {
	EXPECT_EQ(adj2tc(scaling({{},{{2,2}},{}}, 1, 2), 2), 2);
	EXPECT_EQ(adj2tc(scaling({{},{{2,5},{4,4}},{{3,6}},{{5,8},{6,5}},{{2,3},{5,1}},{{6,2}},{}}, 1, 6), 6), 7);
}

TEST(C201FordFulkersonAlgorithm, minimunCuts) {
	test({{},{{2,2}},{}}, 1, 2, 2);
	test({{},{{2,5},{4,4}},{{3,6}},{{5,8},{6,5}},{{2,3},{5,1}},{{6,2}},{}}, 1, 6, 7);
}
