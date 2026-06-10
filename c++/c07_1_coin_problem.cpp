#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 2;

namespace {
	ll solve1(const vector<ll>& coins, ll x) {
		if (x < 0) return INF;
		if (x == 0) return 0;
		ll best = INF;
		for (auto c : coins) {
			best = min(best, solve1(coins, x - c) + 1);
		}
		return best;
	}

	ll solve2(const vector<ll>& coins, ll x) {
		vector<ll> value(x + 1, -1);
		auto rec = [&](this auto self, ll x) -> ll {
			if (x < 0) return INF;
			if (x == 0) return 0;
			if (value[x] >= 0) return value[x];
			ll best = INF;
			for (auto c : coins) {
				best = min(best, self(x - c) + 1);
			}
			value[x] = best;
			return best;
			};
		return rec(x);
	}

	ll solve3(const vector<ll>& coins, ll n) {
		if (n < 0) return INF;
		vector<ll> value(n + 1, INF);
		value[0] = 0;
		for (ll x = 1; x <= n; ++x) {
			for (auto c : coins) {
				if (x - c >= 0) {
					value[x] = min(value[x], value[x - c] + 1);
				}
			}
		}
		return value[n];
	}

	vector<ll> solve4(const vector<ll>& coins, ll n) {
		if (n < 0) return {};
		vector<ll> value(n + 1), first(n + 1);
		value[0] = 0;
		for (ll x = 1; x <= n; ++x) {
			value[x] = INF;
			for (auto c : coins) {
				if (x - c >= 0 && value[x - c] + 1 < value[x]) {
					value[x] = value[x - c] + 1;
					first[x] = c;
				}
			}
		}
		vector<ll> ret;
		if (value[n] < INF) {
			while (n > 0) {
				ret.push_back(first[n]);
				n -= first[n];
			}
		}
		return ret;
	}

	ll solve5(const vector<ll>& coins, ll n, ll m) {
		if (n < 0) return 0;
		vector<ll> count(n + 1);
		count[0] = 1;
		for (ll x = 1; x <= n; ++x) {
			for (auto c : coins) {
				if (x - c >= 0) {
					count[x] += count[x - c];
					count[x] %= m;
				}
			}
		}
		return count[n];
	}

	void test(auto f) {
		EXPECT_EQ(f({}, 0), 0);
		EXPECT_EQ(f({}, 1), INF);
		EXPECT_EQ(f({ 5 }, 3), INF);
		EXPECT_EQ(f({ 1, 3, 4 }, -1), INF);
		EXPECT_EQ(f({ 1, 3, 4 }, 0), 0);
		EXPECT_EQ(f({ 1, 3, 4 }, 10), 3);
	}
}

TEST(C071CoinProblem, solve1) {
	test(solve1);
}

TEST(C071CoinProblem, solve2) {
	test(solve2);
}

TEST(C071CoinProblem, solve3) {
	test(solve3);
}

TEST(C071CoinProblem, solve4) {
	EXPECT_EQ(solve4({}, 0) | ranges::to<multiset>(), multiset<ll>{});
	EXPECT_EQ(solve4({}, 1) | ranges::to<multiset>(), multiset<ll>{});
	EXPECT_EQ(solve4({ 5 }, 3) | ranges::to<multiset>(), multiset<ll>{});
	EXPECT_EQ(solve4({ 1, 3, 4 }, -1) | ranges::to<multiset>(), multiset<ll>{});
	EXPECT_EQ(solve4({ 1, 3, 4 }, 0) | ranges::to<multiset>(), multiset<ll>{});
	EXPECT_EQ(solve4({ 1, 3, 4 }, 10) | ranges::to<multiset>(), (multiset<ll>{3, 3, 4}));
}

TEST(C071CoinProblem, solve5) {
	ll m = 1'000'000'007;
	EXPECT_EQ(solve5({}, 0, m), 1);
	EXPECT_EQ(solve5({}, 1, m), 0);
	EXPECT_EQ(solve5({ 5 }, 3, m), 0);
	EXPECT_EQ(solve5({ 1, 3, 4 }, -1, m), 0);
	EXPECT_EQ(solve5({ 1, 3, 4 }, 0, m), 1);
	EXPECT_EQ(solve5({ 1, 3, 4 }, 5, m), 6);
}
