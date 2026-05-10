#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "c09_2_binary_indexed_tree.h"
#include "c09_4_additional_techniques.h"

namespace {
	using P = complex<long double>;

	ll count(const vector<pair<P, P>>& ls) {
		vector<long double> ys;
		for (auto [p1, p2] : ls) {
			ys.push_back(p1.imag());
			ys.push_back(p2.imag());
		}
		auto d = index_compression(ys);
		BIT b(ssize(d));
		ll c = 0;
		vector<tuple<long double, ll, ll, ll>> s;
		for (auto [p1, p2] : ls) {
			if (p1.real() == p2.real()) {
				auto [y1, y2] = minmax({ p1.imag(), p2.imag() });
				s.emplace_back(p1.real(), 1, d[y1], d[y2]);
			}
			else {
				auto [x1, x2] = minmax({ p1.real(), p2.real() });
				s.emplace_back(x1, 0, d[p1.imag()], 1);
				s.emplace_back(x2, 2, d[p1.imag()], -1);
			}
		}
		ranges::sort(s);
		for (auto [_, k, i1, i2] : s) {
			if (k == 1)
				c += b.sum(i2 + 1) - b.sum(i1);
			else
				b.add(i1, i2);
		}
		return c;
	}
}

TEST(C301IntersectionPoints, count) {
	EXPECT_EQ(count({}), 0);
	EXPECT_EQ(count({ {{0,1},{3,1}},{{1,3},{4,3}},{{4,2},{6,2}},{{2,0},{2,5}},{{5,1},{5,4}} }), 3);
}
