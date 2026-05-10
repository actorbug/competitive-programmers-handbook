#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	vector<bool> solve1(const vector<ll>& w) {
		ll n = ssize(w), W = ranges::fold_left(w, 0, plus());
		vector<vector<bool>> possible(n + 1, vector<bool>(W + 1));
		possible[0][0] = true;
		for (ll k = 1; k <= n; ++k) {
			for (ll x = 0; x <= W; ++x) {
				if (x - w[k - 1] >= 0) possible[k][x] = possible[k][x] || possible[k - 1][x - w[k - 1]];
				possible[k][x] = possible[k][x] || possible[k - 1][x];
			}
		}
		return possible[n];
	}

	vector<bool> solve2(const vector<ll>& w) {
		ll n = ssize(w), W = ranges::fold_left(w, 0, plus());
		vector<bool> possible(W + 1);
		possible[0] = true;
		for (ll k = 1; k <= n; ++k) {
			for (ll x = W; x >= 0; x--) {
				if (possible[x]) possible[x + w[k - 1]] = true;
			}
		}
		return possible;
	}

	void test(auto f) {
		EXPECT_EQ(f({}), vector<bool>{true});
		EXPECT_EQ(f({ 1,3,3,5 }), (vector<bool>{true, true, false, true, true, true, true, true, true, true, false, true, true}));
	}
}

TEST(C074KnapsackProblems, solve1) {
	test(solve1);
}

TEST(C074KnapsackProblems, solve2) {
	test(solve2);
}
