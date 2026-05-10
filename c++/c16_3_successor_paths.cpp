#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct Succ {
		Succ(vector<ll> func, ll u) : succ(u + 1, vector<ll>(func.size())) {
			succ[0] = move(func);
			for (ll i = 1; i <= u; ++i) {
				for (ll j = 0; j < ssize(succ[i - 1]); ++j) {
					succ[i][j] = succ[i - 1][succ[i - 1][j]];
				}
			}
		}
		ll operator()(ll x, ll k) const {
			for (const auto& f : succ) {
				if (k & 1)
					x = f[x];
				k >>= 1;
			}
			return (k == 0) ? x : -1;
		}
	private:
		vector<vector<ll>> succ;
	};
}

TEST(C163SuccessorPaths, Succ) {
	EXPECT_EQ(Succ({ 0 }, 3)(0, 10), 0);
	Succ succ({ 2,4,6,5,1,1,0,5,2 }, 3);
	EXPECT_EQ(succ(3, 6), 1);
	EXPECT_EQ(succ(3, 11), 4);
}
