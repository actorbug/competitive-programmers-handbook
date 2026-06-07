#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	vector<ll> merge(const vector<ll>& l, ll d) {
		vector<ll> ret;
		ll n = ssize(l);
		ll i1 = 0, i2 = 0;
		while (i1 < n && i2 < n) {
			if (l[i1] < l[i2] + d)
				ret.push_back(l[i1++]);
			else {
				if (l[i1] == l[i2] + d)
					++i1;
				ret.push_back(l[i2++] + d);
			}
		}
		for (; i1 < n; ++i1)
			ret.push_back(l[i1]);
		for (; i2 < n; ++i2)
			ret.push_back(l[i2] + d);
		return ret;
	}

	bool solve(const vector<ll>& lst, ll x) {
		ll n = ssize(lst);
		ll m = n / 2;
		vector<ll> sa = { 0 }, sb = { 0 };
		for (ll i = 0; i < m; ++i)
			sa = merge(sa, lst[i]);
		for (ll i = m; i < n; ++i)
			sb = merge(sb, lst[i]);
		ll i = 0, j = ranges::upper_bound(sb, x) - sb.begin() - 1;
		while (i < ssize(sa) && j >= 0) {
			if (sa[i] + sb[j] < x)
				++i;
			else if (sa[i] + sb[j] > x)
				--j;
			else
				return true;
		}
		return false;
	}
}

TEST(C055MeetInTheMiddle, solve) {
	EXPECT_TRUE(solve({}, 0));
	EXPECT_FALSE(solve({}, 1));
	EXPECT_TRUE(solve({ 3,2,1 }, 1));
	EXPECT_TRUE(solve({ 2,4,5,9 }, 15));
	EXPECT_FALSE(solve({ 2,4,5,9 }, 10));
}
