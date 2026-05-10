#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 2;

namespace {
	vector<ll> bellman_ford(ll n, const vector<tuple<ll, ll, ll>>& edges, ll x) {
		vector<ll> distance(n, INF);
		distance[x] = 0;
		for (ll i = 1; i <= n; ++i) {
			bool changed = false;
			for (auto [a, b, w] : edges) {
				if (distance[b] > distance[a] + w) {
					distance[b] = distance[a] + w;
					changed = true;
				}
			}
			if (!changed)
				return distance;
		}
		return {};
	}
	vector<ll> spfa(const vector<vector<pair<ll, ll>>>& adj, ll x) {
		ll n = ssize(adj);
		vector<ll> len(n), distance(n, INF);
		queue<ll> q({ x });
		vector<bool> inq(n);
		distance[x] = 0;
		inq[x] = true;
		while (!q.empty()) {
			ll a = q.front(); q.pop(); inq[a] = false;
			for (auto [b, w] : adj[a]) {
				if (distance[b] > distance[a] + w) {
					len[b] = len[a] + 1;
					if (len[b] >= n)
						return {};
					distance[b] = distance[a] + w;
					if (!inq[b]) {
						q.push(b);
						inq[b] = true;
					}
				}
			}
		}
		return distance;
	}
}

TEST(C131BellmanFord, bellmanFord) {
	EXPECT_EQ(bellman_ford(1, {}, 0), vector<ll>{0});
	EXPECT_EQ(bellman_ford(5, { {0,1,5},{0,2,3},{0,3,7},{1,0,5},{1,3,3},{1,4,2},{2,0,3},{2,3,1},{3,0,7},{3,1,3},{3,2,1},{3,4,2},{4,1,2},{4,3,2} }, 0), (vector<ll>{0, 5, 3, 4, 6}));
	EXPECT_EQ(bellman_ford(4, { {0,1,3},{0,2,5},{1,0,3},{1,2,2},{1,3,1},{2,0,5},{2,1,2},{2,3,-7},{3,1,1},{3,2,-7} }, 0), vector<ll>{});
}

TEST(C131BellmanFord, spfa) {
	EXPECT_EQ(spfa({ {} }, 0), vector<ll>{0});
	EXPECT_EQ(spfa({ {{1,5},{2,3},{3,7}},{{0,5},{3,3},{4,2}},{{0,3},{3,1}},{{0,7},{1,3},{2,1},{4,2}},{{1,2},{3,2}} }, 0), (vector<ll>{0, 5, 3, 4, 6}));
	EXPECT_EQ(spfa({ {{1,3},{2,5}},{{0,3},{2,2},{3,1}},{{0,5},{1,2},{3,-7}},{{1,1},{2,-7}} }, 0), vector<ll>{});
}
