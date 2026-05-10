#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	using P = complex<long double>;

	pair<long double, long double> ascX(P p) {
		return { p.real(), p.imag() };
	}

	pair<long double, long double> ascY(P p) {
		return { p.imag(), p.real() };
	}

	pair<P, P> closest_pair(vector<P> points) {
		ranges::sort(points, {}, ascX);
		multiset<P, decltype([](P a, P b) { return ascY(a) < ascY(b); })> b = { points[0], points[1] };
		auto d = abs(points[0] - points[1]);
		auto r = make_pair(points[0], points[1]);
		for (ll i = 0, j = 2; j < ssize(points); ++j) {
			while (i < j && points[i].real() < points[j].real() - d)
				b.erase(points[i++]);
			for (auto l = b.lower_bound(P(points[j].real() - d, points[j].imag() - d)); l != b.end() && l->imag() <= points[j].imag() + d; ++l) {
				auto d1 = abs(*l - points[j]);
				if (d > d1) {
					d = d1;
					r = make_pair(*l, points[j]);
				}
			}
			b.insert(points[j]);
		}
		return r;
	}
}

TEST(C302ClosestPairProblem, closestPair) {
	EXPECT_EQ(closest_pair({ {0,0},{0,0} }), (make_pair<P, P>({0,0},{0,0})));
	EXPECT_EQ(closest_pair({ {0,3},{1,1},{1,6},{3,5},{4,1},{5,5},{6,2},{7,0},{8,2},{9,4},{10,3},{11,1},{14,2},{16,3} }), (make_pair<P, P>({9,4},{10,3})));
}
