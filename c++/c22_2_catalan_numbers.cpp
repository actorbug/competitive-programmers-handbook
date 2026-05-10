#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "util.h"

namespace {
	ll cataran(ll n) {
		return comb(2 * n, n) / (n + 1);
	}
}

TEST(C222CatalanNumbers, cataran) {
	EXPECT_EQ(cataran(3), 5);
}
