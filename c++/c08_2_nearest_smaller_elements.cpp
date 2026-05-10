#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	vector<ll> solve(const vector<ll>& a) {
		stack<ll> s;
		vector<ll> ret;
		for (ll i = 0; i < ssize(a); ++i) {
			while (!s.empty() && a[s.top()] >= a[i])
				s.pop();
			ret.push_back((!s.empty()) ? s.top() : -1);
			s.push(i);
		}
		return ret;
	}
}

TEST(C082NearestSmallerElements, solve) {
	EXPECT_EQ(solve({}), vector<ll>{});
	EXPECT_EQ(solve({ 1,3,4,2,5,3,4,2 }), (vector<ll>{ -1,0,1,0,3,3,5,0 }));
}
