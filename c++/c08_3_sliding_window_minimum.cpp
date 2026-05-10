#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	vector<ll> solve(const vector<ll>& a, ll n) {
		deque<ll> s;
		vector<ll> ret;
		for (ll i = 0; i < ssize(a); ++i) {
			while (!s.empty() && a[s.back()] >= a[i])
				s.pop_back();
			s.push_back(i);
			if (i >= n - 1) {
				if (s.front() == i - n)
					s.pop_front();
				ret.push_back(s.front());
			}
		}
		return ret;
	}
}

TEST(C083SlidingWindowMinimum, solve) {
	EXPECT_EQ(solve({}, 1), vector<ll>{});
	EXPECT_EQ(solve({ 1,2 }, 1), (vector<ll>{ 0,1 }));
	EXPECT_EQ(solve({ 2,1,4,5,3,4,1,2 }, 4), (vector<ll>{ 1,1,4,6,6 }));
}
