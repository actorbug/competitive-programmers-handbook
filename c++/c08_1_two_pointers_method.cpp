#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	pair<ll, ll> subarray_sum(const vector<ll>& a, ll x) {
		if (x == 0)
			return { 0, 0 };
		ll i = 0, s = 0;
		for (ll j = 0; j < ssize(a); ++j) {
			s += a[j];
			while (i <= j && s > x)
				s -= a[i++];
			if (s == x)
				return { i, j + 1 };
		}
		return { -1, -1 };
	}

	pair<ll, ll> two_sum_problem(vector<ll> a, ll x) {
		ranges::sort(a);
		ll i = 0, j = ssize(a) - 1;
		while (i < j) {
			if (a[i] + a[j] < x)
				++i;
			else if (a[i] + a[j] > x)
				--j;
			else
				return { a[i], a[j] };
		}
		return { -1, -1 };
	}

	tuple<ll, ll, ll> three_sum_problem(vector<ll> a, ll x) {
		ranges::sort(a);
		ll n = ssize(a);
		for (ll i = 0; i < n - 2; ++i) {
			ll j = i + 1, k = n - 1;
			while (j < k) {
				if (a[i] + a[j] + a[k] < x)
					++j;
				else if (a[i] + a[j] + a[k] > x)
					--k;
				else
					return { a[i], a[j], a[k] };
			}
		}
		return { -1, -1, -1 };
	}
}

TEST(C081TwoPointersMethod, subarraySum) {
	EXPECT_EQ(subarray_sum({}, 0), make_pair(0, 0));
	EXPECT_EQ(subarray_sum({}, 1), make_pair(-1, -1));
	EXPECT_EQ(subarray_sum({ 1,3,2,5,1,1,2,3 }, 8), make_pair(2, 5));
	EXPECT_EQ(subarray_sum({ 1,3,2,5,1,1,2,3 }, 2), make_pair(2, 3));
}

TEST(C081TwoPointersMethod, twoSumProblem) {
	EXPECT_EQ(two_sum_problem({}, 0), make_pair(-1, -1));
	EXPECT_EQ(two_sum_problem({ 1,4 }, 5), make_pair(1, 4));
	EXPECT_EQ(two_sum_problem({ 1,4 }, 12), make_pair(-1, -1));
	EXPECT_EQ(two_sum_problem({ 1,4,5,6,7,9,9,10 }, 12), make_pair(5, 7));
}

TEST(C081TwoPointersMethod, threeSumProblem) {
	EXPECT_EQ(three_sum_problem({}, 0), make_tuple(-1, -1, -1));
	EXPECT_EQ(three_sum_problem({ 1,4,5 }, 10), make_tuple(1, 4, 5));
	EXPECT_EQ(three_sum_problem({ 1,4,5 }, 12), make_tuple(-1, -1, -1));
	EXPECT_EQ(three_sum_problem({ 1,4,5,6,7,9,9,10 }, 12), make_tuple(1, 4, 7));
}
