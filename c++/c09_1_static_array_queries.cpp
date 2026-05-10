#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "c09_1_static_array_queries.h"

namespace {
	struct SumQueries {
		SumQueries(const vector<ll>& array) : s(array.size() + 1) {
			inclusive_scan(array.begin(), array.end(), s.begin() + 1);
		}
		ll operator()(ll a, ll b) const {
			return s[b + 1] - s[a];
		}
	private:
		vector<ll> s;
	};
}

TEST(C091StaticArrayQueries, SumQueries) {
	EXPECT_EQ(SumQueries({})(0, -1), 0);
	EXPECT_EQ(SumQueries({ 1,3,4,8,6,1,4,2 })(3, 6), 19);
}

TEST(C091StaticArrayQueries, MinimumQueries) {
	EXPECT_EQ(MinimumQueries<ll>({1})(0, 0), 1);
	EXPECT_EQ(MinimumQueries<ll>({ 1,3,4,8,6,1,4,2 })(1, 6), 1);
}
