#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 2;

namespace {
	vector<ll> dijkstra(const vector<vector<pair<ll,ll>>>& adj, ll x) {
		ll n = ssize(adj);
		vector<ll> distance(n, INF);
		priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> q({}, { {0,x} });
		distance[x] = 0;
		while (!q.empty()) {
			auto [d, a] = q.top(); q.pop();
			if (distance[a] < d) continue;
			for (auto [b, w] : adj[a]) {
				if (distance[a] + w < distance[b]) {
					distance[b] = distance[a] + w;
					q.emplace(distance[b], b);
				}
			}
		}
		return distance;
	}
}

TEST(C132DijkstrasAlgorithm, dijkstra) {
	EXPECT_EQ(dijkstra({ {} }, 0), vector<ll>{0});
	EXPECT_EQ(dijkstra({ {{1,5},{3,9},{4,1}},{{0,5},{2,2}},{{1,2},{3,6}},{{0,9},{2,6},{4,2}},{{0,1},{3,2}} }, 0), (vector<ll>{0, 5, 7, 3, 1}));
}
