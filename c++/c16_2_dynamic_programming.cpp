#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 2;
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

	vector<vector<ll>> dijkstra(const vector<vector<pair<ll, ll>>>& adj, ll x) {
		ll n = ssize(adj);
		vector<bool> processed(n);
		vector<ll> distance(n, INF);
		priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> q;
		vector<vector<ll>> ret(n);
		distance[x] = 0;
		q.emplace(-1, -1, x);
		while (!q.empty()) {
			auto [d, a, b] = q.top(); q.pop();
			if (d == distance[b])
				ret[a].push_back(b);
			if (processed[b]) continue;
			processed[b] = true;
			for (auto [c, w] : adj[b]) {
				if (distance[b] + w <= distance[c]) {
					distance[c] = distance[b] + w;
					q.emplace(distance[c], b, c);
				}
			}
		}
		return ret;
	}

	vector<vector<ll>> coin_problem(const vector<ll>& coins, ll x) {
		vector<vector<ll>> ret(x + 1);
		for (ll i = 0; i <= x; ++i) {
			for (ll c : coins) {
				if (i + c <= x) {
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
	EXPECT_EQ(count_path({ {} }, 0, 0), 1);
	EXPECT_EQ(count_path({ {1,3},{2},{5},{4},{1,2},{} }, 0, 5), 3);
}

TEST(C162DynamicProgramming, dijkstra) {
	EXPECT_EQ(count_path(dijkstra({ {} }, 0), 0, 0), 1);
	EXPECT_EQ(count_path(dijkstra({ {{1,3},{2,5}},{{0,3},{2,2},{3,4},{4,8}},{{0,5},{1,2},{3,2}},{{1,4},{2,2},{4,1}},{{1,8},{3,1}} }, 0), 0, 4), 3);
}

TEST(C162DynamicProgramming, coinProblem) {
	auto cp = coin_problem({}, 0);
	EXPECT_EQ(bfs(cp, 0, 0), 0);
	EXPECT_EQ(count_path(cp, 0, 0), 1);
	cp = coin_problem({ 1, 3, 4 }, 6);
	EXPECT_EQ(bfs(cp, 0, 6), 2);
	EXPECT_EQ(count_path(cp, 0, 6), 9);
}
