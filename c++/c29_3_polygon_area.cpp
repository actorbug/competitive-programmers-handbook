#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c29_2_points_and_lines.h"

namespace {
	long double shoelace_formula(const vector<P>& p) {
		return abs(ranges::fold_left(views::adjacent_transform<2>(p, [](P a, P b) { return cross_product(a, b); }), 0, plus())) / 2;
	}

	bool polygon_border(const vector<P>& p, P a) {
		for (auto [s1, s2] : views::pairwise(p)) {
			if (abs(point_location(s1, s2, a)) < 1e-9l) {
				auto i = inner_product(s2 - s1, a - s1);
				if (0 <= i && i <= inner_product(s2 - s1, s2 - s1)) {
					return true;
				}
			}
		}
		return false;
	}

	long double picks_theorem(const vector<P>& p) {
		ll a = 0, b = 0;
		auto ymin = numeric_limits<long double>::infinity(), ymax = -numeric_limits<long double>::infinity();
		auto xmin = numeric_limits<long double>::infinity(), xmax = -numeric_limits<long double>::infinity();
		for (P i : p) {
			ymin = min(ymin, i.imag());
			ymax = max(ymax, i.imag());
			xmin = min(xmin, i.real());
			xmax = max(xmax, i.real());
		}
		for (auto y = ymin; y <= ymax; ++y) {
			for (auto x = xmin; x <= xmax; ++x) {
				if (polygon_border(p, { x, y }))
					++b;
				else if (point_inside_a_polygon(p, { x, y }))
					++a;
			}
		}
		return a + b / 2. - 1;
	}
}

TEST(C293PolygonArea, shoelaceFormula) {
	EXPECT_EQ(shoelace_formula({ {2,4},{5,5},{7,3},{4,1},{4,3},{2,4} }), 17 / 2.);
}

TEST(C293PolygonArea, picksTheorem) {
	EXPECT_EQ(picks_theorem({ {2,4},{5,5},{7,3},{4,1},{4,3},{2,4} }), 17 / 2.);
}
