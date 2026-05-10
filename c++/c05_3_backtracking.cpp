#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	ll nqueen(ll n) {
		ll count = 0;
		vector<bool> column(n, 0), diag1(2 * n - 1, 0), diag2(2 * n - 1, 0);
		auto search = [&](this auto self, ll y) {
			if (y == n) {
				++count;
				return;
			}
			for (ll x = 0; x < n; ++x) {
				if (column[x] || diag1[x + y] || diag2[x - y + n - 1]) continue;
				column[x] = diag1[x + y] = diag2[x - y + n - 1] = 1;
				self(y + 1);
				column[x] = diag1[x + y] = diag2[x - y + n - 1] = 0;
			}
			};
		search(0);
		return count;
	}
}

TEST(C053Backtracking, nqueen) {
	EXPECT_EQ(nqueen(1), 1);
	EXPECT_EQ(nqueen(2), 0);
	EXPECT_EQ(nqueen(3), 0);
	EXPECT_EQ(nqueen(4), 2);
}
