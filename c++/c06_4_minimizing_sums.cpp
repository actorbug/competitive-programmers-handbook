#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	double min1(vector<double> ary) {
		if (ary.empty()) return 0;
		ll idx = ssize(ary) / 2;
		ranges::nth_element(ary, ary.begin() + idx);
		return ary[idx];
	}

	double sum1(const vector<double>& ary, double x) {
		return ranges::fold_left(ary | views::transform([x](double d) { return abs(d - x); }), 0, plus());
	}

	double min2(const vector<double>& ary) {
		return ary.empty() ? 0 : ranges::fold_left(ary, 0, plus()) / ary.size();
	}

	double sum2(const vector<double>& ary, double x) {
		return ranges::fold_left(ary | views::transform([x](double d) { return (d - x) * (d - x); }), 0, plus());
	}
}

TEST(C064MinimizingSums, min1sum1) {
	EXPECT_DOUBLE_EQ(sum1({}, min1({})), 0);
	EXPECT_DOUBLE_EQ(sum1({ 1, 2 }, min1({ 1, 2 })), 1);
	EXPECT_DOUBLE_EQ(sum1({ 1, 2, 9, 2, 6 }, min1({ 1, 2, 9, 2, 6 })), 12);
}

TEST(C064MinimizingSums, min2sum2) {
	EXPECT_DOUBLE_EQ(sum2({}, min2({})), 0);
	EXPECT_DOUBLE_EQ(sum2({ 1, 2, 9, 2, 6 }, min2({ 1, 2, 9, 2, 6 })), 46);
}
