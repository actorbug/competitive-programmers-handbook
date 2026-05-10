#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	ll count(const vector<pair<ll, ll>>& r) {
		vector<pair<ll, ll>> s;
		for (auto [i, j] : r) {
			s.emplace_back(i, 1);
			s.emplace_back(j, -1);
		}
		ranges::sort(s);
		vector<ll> t(s.size());
		transform_inclusive_scan(s.begin(), s.end(), t.begin(), plus(), [](const auto& p) { return p.second; });
		return t.empty() ? 0 : ranges::max(t);
	}
}

TEST(C300SweepLineAlgorithms, count) {
	EXPECT_EQ(count({}), 0);
	EXPECT_EQ(count({ {10,15}, {6,12}, {14,16}, {5,13} }), 3);
}
