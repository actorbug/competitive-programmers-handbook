#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	pair<ll, ll> floyd(const vector<ll>& succ, ll x) {
		ll a = succ[x], b = succ[succ[x]];
		while (a != b) {
			a = succ[a]; b = succ[succ[b]];
		}
		a = x;
		while (a != b) {
			a = succ[a]; b = succ[b];
		}
		b = succ[a];
		ll length = 1;
		while (a != b) {
			b = succ[b];
			++length;
		}
		return { a, length };
	}
}

TEST(C164CycleDetection, floyd) {
	EXPECT_EQ(floyd({ 0 }, 0), (pair<ll, ll>{0, 1}));
	EXPECT_EQ(floyd({ 1,2,3,4,5,3 }, 0), (pair<ll, ll>{3, 3}));
}
