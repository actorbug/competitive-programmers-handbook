#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c23_1_operations.h"

namespace {
	ll fib(ll n) {
		if (n <= 0)
			return 0;
		return ll(M({{0,1},{1,1}}).pow(n - 1).v[1][1]);
	}
}

TEST(C232LinearRecurrences, fib) {
	EXPECT_EQ(fib(0), 0);
	EXPECT_EQ(fib(7), 13);
}
