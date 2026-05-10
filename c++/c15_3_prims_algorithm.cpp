#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	vector<vector<pair<ll, ll>>> prim(const vector<vector<pair<ll, ll>>>& adj) {
		if (adj.empty()) return {};
		vector<bool> processed(adj.size());
		vector<vector<pair<ll, ll>>> ret(adj.size());
		processed[0] = true;
		priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> q;
		for (auto [c, w] : adj[0])
			q.emplace(w, 0, c);
		while (!q.empty()) {
			auto [w, a, b] = q.top(); q.pop();
			if (processed[b])
				continue;
			processed[b] = true;
			ret[a].emplace_back(b, w);
			ret[b].emplace_back(a, w);
			for (auto [c, w] : adj[b])
				q.emplace(w, b, c);
		}
		return ret;
	}
}

TEST(C153PrimsAlgorithm, prim) {
	EXPECT_EQ(prim({}), (vector<vector<pair<ll, ll>>>{}));
	auto ret = prim({ {{1,3},{4,5}},{{0,3},{2,5},{4,6}},{{1,5},{3,9},{5,3}},{{2,9},{5,7}},{{0,5},{1,6},{5,2}},{{2,3},{3,7},{4,2}} });
	for (auto& r : ret)
		ranges::sort(r);
	EXPECT_EQ(ret, (vector<vector<pair<ll, ll>>>{ {{1,3},{4,5}},{{0,3}},{{5,3}},{{5,7}},{{0,5},{5,2}},{{2,3},{3,7},{4,2}} }));
}
