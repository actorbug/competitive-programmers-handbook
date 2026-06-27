#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 2;
#include "util.h"
#include "c16_1_topological_sorting.h"

namespace {
	ll count_path(const vector<vector<ll>>& adj, ll a, ll b) {
		vector<ll> paths(adj.size());
		paths[a] = 1;
		for (ll s : topological(adj)) {
			for (ll u : adj[s]) {
				paths[u] += paths[s];
			}
		}
		return paths[b];
	}

	vector<vector<pair<ll, ll>>> dijkstra(const vector<vector<pair<ll, ll>>>& adj, ll x) {
		ll n = ssize(adj);
		vector<bool> processed(n);
		vector<ll> distance(n, INF);
		priority_queue<tuple<ll, ll, ll, ll>, vector<tuple<ll, ll, ll, ll>>, greater<>> q;
		vector<vector<pair<ll, ll>>> ret(n);
		distance[x] = 0;
		q.emplace(-1, 0, x, -1);
		while (!q.empty()) {
			auto [d, a, b, w] = q.top(); q.pop();
			if (d == distance[b])
				ret[a].emplace_back(b, w);
			if (processed[b]) continue;
			processed[b] = true;
			for (auto [c, w] : adj[b]) {
				if (distance[b] + w <= distance[c]) {
					distance[c] = distance[b] + w;
					q.emplace(distance[c], b, c, w);
				}
			}
		}
		return ret;
	}

	vector<vector<ll>> coin_problem(const vector<ll>& coins, ll x) {
		vector<vector<ll>> ret(x + 2);
		for (ll i = 1; i <= x + 1; ++i) {
			for (ll c : coins) {
				if (i + c <= x + 1) {
					ret[i].push_back(i + c);
				}
			}
		}
		return ret;
	}

	ll bfs(const vector<vector<ll>>& adj, ll x, ll y) {
		ll n = ssize(adj);
		queue<ll> q({ x });
		vector<ll> distance(n, -1);
		distance[x] = 0;
		while (!q.empty()) {
			ll s = q.front(); q.pop();
			if (s == y)
				return distance[s];
			for (auto u : adj[s]) {
				if (distance[u] >= 0) continue;
				distance[u] = distance[s] + 1;
				q.push(u);
			}
		}
		return INF;
	}
}

TEST(C162DynamicProgramming, countPath) {
	EXPECT_EQ(count_path({ {},{} }, 1, 1), 1);
	EXPECT_EQ(count_path({ {},{2,4},{3},{6},{5},{2,3},{} }, 1, 6), 3);
}

TEST(C162DynamicProgramming, dijkstra) {
	EXPECT_EQ(count_path(delweight(dijkstra({ {},{} }, 1)), 1, 1), 1);
	EXPECT_EQ(count_path(delweight(dijkstra({ {},{{2,3},{3,5}},{{1,3},{3,2},{4,4},{5,8}},{{1,5},{2,2},{4,2}},{{2,4},{3,2},{5,1}},{{2,8},{4,1}} }, 1)), 1, 5), 3);
}

TEST(C162DynamicProgramming, coinProblem) {
	auto cp = coin_problem({}, 0);
	EXPECT_EQ(bfs(cp, 1, 1), 0);
	EXPECT_EQ(count_path(cp, 1, 1), 1);
	cp = coin_problem({ 1, 3, 4 }, 6);
	EXPECT_EQ(bfs(cp, 1, 7), 2);
	EXPECT_EQ(count_path(cp, 1, 7), 9);
}
