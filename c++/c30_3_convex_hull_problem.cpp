#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c29_2_points_and_lines.h"

namespace {
	vector<P> andrew(vector<P> points) {
		if (points.size() < 2)
			return points;
		ranges::sort(points, {}, [](P p) { return make_pair(p.real(), p.imag()); });
		vector<P> upper = { points[0], points[1] };
		for (ll i = 2; i < ssize(points); ++i) {
			upper.push_back(points[i]);
			while (upper.size() > 2 && point_location(upper[upper.size() - 3], upper[upper.size() - 2], upper[upper.size() - 1]) >= 0)
				upper.erase(upper.end() - 2);
		}
		upper.pop_back();
		vector<P> lower = { points[points.size() - 1], points[points.size() - 2] };
		for (ll i = ssize(points) - 3; i >= 0; --i) {
			lower.push_back(points[i]);
			while (lower.size() > 2 && point_location(lower[lower.size() - 3], lower[lower.size() - 2], lower[lower.size() - 1]) >= 0)
				lower.erase(lower.end() - 2);
		}
		lower.pop_back();
		upper.insert(upper.end(), lower.begin(), lower.end());
		return upper;
	}
}

TEST(C303ConvexHullProblem, andrew) {
	EXPECT_EQ(andrew({}), vector<P>{});
	EXPECT_EQ(andrew({ {0,0} }), (vector<P>{ {0,0} }));
	EXPECT_EQ(andrew({ {0,0},{1,0} }), (vector<P>{ {0,0},{1,0} }));
	EXPECT_EQ(andrew({ {0,0},{1,0},{1,1} }), (vector<P>{ {0,0},{1,1},{1,0} }));
	EXPECT_EQ(andrew({ {0,0},{1,0},{2,0} }), (vector<P>{ {0,0},{2,0} }));
	EXPECT_EQ(andrew({ {0,1},{0,3},{1,2},{2,3},{2,5},{3,3},{4,0},{4,1},{4,4},{5,3},{6,2},{6,4},{7,2} }), (vector<P>{ {0,1},{0,3},{2,5},{6,4},{7,2},{4,0} }));
}
