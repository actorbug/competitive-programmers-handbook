#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	void bfs(const vector<vector<ll>>& adj, ll x, auto f) {
		ll n = ssize(adj);
		queue<ll> q({ x });
		vector<ll> distance(n, -1);
		distance[x] = 0;
		while (!q.empty()) {
			ll s = q.front(); q.pop();
			// process node s
			f(s, distance[s]);
			for (auto u : adj[s]) {
				if (distance[u] >= 0) continue;
				distance[u] = distance[s] + 1;
				q.push(u);
			}
		}
	}
}

TEST(C122BreadthFirstSearch, bfs) {
	vector<pair<ll, ll>> ret;
	bfs({ {} }, 0, [&](ll s, ll d) { ret.emplace_back(s, d); });
	EXPECT_EQ(ret, (vector<pair<ll, ll>>{{0, 0}}));
	ret.clear();
	bfs({ {1,3},{0,2,4},{1,5},{0},{1,5},{2,4} }, 0, [&](ll s, ll d) { ret.emplace_back(s, d); });
	EXPECT_EQ(ret, (vector<pair<ll, ll>>{{0, 0}, {1, 1}, {3, 1}, {2, 2}, {4, 2}, {5, 3}}));
}
