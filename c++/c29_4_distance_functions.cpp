#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	using P = complex<long double>;

	tuple<P, P, long double> max_distance(const vector<P>& p) {
		auto x = p | views::transform([](P i) { return i.real() + i.imag(); }) | ranges::to<vector>();
		auto y = p | views::transform([](P i) { return i.imag() - i.real(); }) | ranges::to<vector>();
		auto [minx, maxx] = ranges::minmax_element(x);
		auto [miny, maxy] = ranges::minmax_element(y);
		if (*maxx - *minx >= *maxy - *miny)
			return { p[minx - x.begin()], p[maxx - x.begin()], *maxx - *minx };
		else
			return { p[miny - y.begin()], p[maxy - y.begin()], *maxy - *miny };
	}
}

TEST(C294DistanceFunctions, maxDistance) {
	EXPECT_EQ(max_distance({ {0,2}, {1,0}, {3,3}, {3,1} }), (make_tuple<P, P, long double>({1,0}, {3,3}, 5)));
	EXPECT_EQ(max_distance({ {2,0}, {0,1}, {3,3}, {1,3} }), (make_tuple<P, P, long double>({0,1}, {3,3}, 5)));
}
