#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c29_2_points_and_lines.h"

namespace {
	bool line_segment_intersection(P a, P b, P c, P d) {
		auto abc = point_location(a, b, c);
		auto abd = point_location(a, b, d);
		auto cda = point_location(c, d, a);
		auto cdb = point_location(c, d, b);
		if (abs(abc) < 1e-9l && abs(abd) < 1e-9l && abs(cda) < 1e-9l && abs(cdb) < 1e-9l) {
			auto ab = inner_product(b - a, b - a);
			auto ac = inner_product(b - a, c - a);
			auto ad = inner_product(b - a, d - a);
			return !(ac < 0 && ad < 0 || ac > ab && ad > ab);
		}
		else
			return abc * abd <= 0 && cda * cdb <= 0;
	}

	long double point_distance_from_a_line(P s1, P s2, P p) {
		return cross_product(s1 - p, s2 - p) / abs(s2 - s1);
	}
}

long double inner_product(P a, P b) {
	return (conj(a) * b).real();
}

long double cross_product(P a, P b) {
	return (conj(a) * b).imag();
}

long double point_location(P s1, P s2, P p) {
	return cross_product(p - s1, p - s2);
}

bool point_inside_a_polygon(const vector<P>& p, P a) {
	P b(0, 1e9l);
	return ranges::fold_left(views::adjacent_transform<2>(p, [&](P s1, P s2) { return line_segment_intersection(a, b, s1, s2); }), 0, plus()) % 2 == 1;
}

TEST(C292PointsAndLines, innerProduct) {
	EXPECT_EQ(inner_product(P(4, 2), P(1, 2)), 8);
}

TEST(C292PointsAndLines, crossProduct) {
	EXPECT_EQ(cross_product(P(4, 2), P(1, 2)), 6);
}

TEST(C292PointsAndLines, pointLocation) {
	EXPECT_GT(point_location(P(0, 0), P(2, 2), P(0, 2)), 0);
	EXPECT_EQ(point_location(P(0, 0), P(2, 2), P(1, 1)), 0);
	EXPECT_LT(point_location(P(0, 0), P(2, 2), P(2, 0)), 0);
}

TEST(C292PointsAndLines, lineSegmentIntersection) {
	EXPECT_TRUE(line_segment_intersection(P(0, 0), P(2, 2), P(0, 2), P(2, 0)));
	EXPECT_TRUE(line_segment_intersection(P(0, 0), P(2, 2), P(2, 2), P(3, 1)));
	EXPECT_TRUE(line_segment_intersection(P(0, 0), P(2, 2), P(1, 1), P(3, 3)));
	EXPECT_FALSE(line_segment_intersection(P(0, 0), P(3, 3), P(3, 0), P(2, 1)));
	EXPECT_FALSE(line_segment_intersection(P(0, 0), P(1, 1), P(2, 2), P(3, 3)));
	EXPECT_FALSE(line_segment_intersection(P(3, 3), P(2, 2), P(1, 1), P(0, 0)));
}

TEST(C292PointsAndLines, pointDistanceFromALine) {
	EXPECT_EQ(point_distance_from_a_line(P(0, 0), P(2, 0), P(1, 1)), 1);
}

TEST(C292PointsAndLines, pointInsideAPolygon) {
	vector<P> p = { {1, 1}, {-1, 1}, {-1, -1}, {1, -1}, {1, 1} };
	EXPECT_FALSE(point_inside_a_polygon(p, P(2, 0)));
	EXPECT_TRUE(point_inside_a_polygon(p, P(0, 0)));
	EXPECT_FALSE(point_inside_a_polygon(p, P(-2, 0)));
}
