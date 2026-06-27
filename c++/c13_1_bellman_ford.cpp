#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 2;

namespace {
	vector<ll> bellman_ford(const vector<vector<pair<ll, ll>>>& adj, ll x) {
		ll n = ssize(adj);
		vector<ll> distance(n, INF);
		distance[x] = 0;
		for (ll i = 1; i < n; ++i) {
			bool changed = false;
			for (ll a = 1; a < n; ++a) {
				for (auto [b, w] : adj[a]) {
					if (distance[b] > distance[a] + w) {
						distance[b] = distance[a] + w;
						changed = true;
					}
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
					if (len[b] >= n - 1)
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
	EXPECT_EQ(bellman_ford({ {},{} }, 1), (vector<ll>{INF,0}));
	EXPECT_EQ(bellman_ford({ {},{{2,5},{3,3},{4,7}},{{1,5},{4,3},{5,2}},{{1,3},{4,1}},{{1,7},{2,3},{3,1},{5,2}},{{2,2},{4,2}} }, 1), (vector<ll>{ INF,0,5,3,4,6 }));
	EXPECT_EQ(bellman_ford({ {},{{2,3},{3,5}},{{1,3},{3,2},{4,1}},{{1,5},{2,2},{4,-7}},{{2,1},{3,-7}} }, 1), vector<ll>{});
}

TEST(C131BellmanFord, spfa) {
	EXPECT_EQ(spfa({ {},{} }, 1), (vector<ll>{INF, 0}));
	EXPECT_EQ(spfa({ {},{{2,5},{3,3},{4,7}},{{1,5},{4,3},{5,2}},{{1,3},{4,1}},{{1,7},{2,3},{3,1},{5,2}},{{2,2},{4,2}} }, 1), (vector<ll>{ INF, 0, 5, 3, 4, 6 }));
	EXPECT_EQ(spfa({ {},{{2,3},{3,5}},{{1,3},{3,2},{4,1}},{{1,5},{2,2},{4,-7}},{{2,1},{3,-7}} }, 1), vector<ll>{});
}
