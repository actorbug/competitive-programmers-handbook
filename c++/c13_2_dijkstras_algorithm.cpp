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
	EXPECT_EQ(dijkstra({ {},{} }, 1), (vector<ll>{ INF,0 }));
	EXPECT_EQ(dijkstra({ {},{{2,5},{4,9},{5,1}},{{1,5},{3,2}},{{2,2},{4,6}},{{1,9},{3,6},{5,2}},{{1,1},{4,2}} }, 1), (vector<ll>{ INF,0,5,7,3,1 }));
}
