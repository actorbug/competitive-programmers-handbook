#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "util.h"

namespace {
	ll solve1(ll n, ll m) {
		if (n < m)
			swap(n, m);
		auto isvalid = [m](const string& prev, const string& curr) {
			for (ll j = 0; j < m; ++j) {
				if (prev[j] == 'A') {
					if (curr[j] != 'V' || j > 0 && curr[j - 1] == '<') {
						return false;
					}
				}
				else if (j > 0 && curr[j - 1] == '<') {
					if (curr[j] != '>') {
						return false;
					}
				}
				else if (curr[j] != 'A' && !(j < m - 1 && curr[j] == '<'))
					return false;
			}
			return true;
			};
		unordered_map<string, ll> dp;
		dp[string(m, 'V')] = 1;
		for (ll i = 0; i < n; ++i) {
			unordered_map<string, ll> ndp;
			vector<ll> vec(m);
			do {
				auto curr = vec | views::transform([](ll i) { return "V<A>"[i]; }) | ranges::to<string>();
				ll sum = 0;
				for (const auto& [prev, v] : dp) {
					if (isvalid(prev, curr)) {
						sum += v;
					}
				}
				if (sum > 0)
					ndp[curr] = sum;
			} while (next_product(vec, 4));
			dp = move(ndp);
		}
		ll ans = 0;
		for (const auto& [prev, v] : dp) {
			if (!prev.contains('A')) {
				ans += v;
			}
		}
		return ans;
	}

	ll solve2(ll n, ll m) {
		if (n < m)
			swap(n, m);
		auto isvalid = [m](const string& prev, const string& curr) {
			bool open = false;
			for (ll j = 0; j < m; ++j) {
				if (prev[j] == 'A') {
					if (curr[j] != 'O' || open) {
						return false;
					}
				}
				else if (open) {
					if (curr[j] != 'O')
						return false;
					open = false;
				}
				else if (curr[j] == 'O') {
					if (j >= m - 1)
						return false;
					open = true;
				}
			}
			return true;
			};
		unordered_map<string, ll> dp;
		dp[string(m, 'O')] = 1;
		for (ll i = 0; i < n; ++i) {
			unordered_map<string, ll> ndp;
			vector<ll> vec(m);
			do {
				auto curr = vec | views::transform([](ll i) { return "OA"[i]; }) | ranges::to<string>();
				ll sum = 0;
				for (const auto& [prev, v] : dp) {
					if (isvalid(prev, curr)) {
						sum += v;
					}
				}
				if (sum > 0)
					ndp[curr] = sum;
			} while (next_product(vec, 2));
			dp = move(ndp);
		}
		ll ans = 0;
		for (const auto& [prev, v] : dp) {
			if (!prev.contains('A')) {
				ans += v;
			}
		}
		return ans;
	}

	ll solve3(ll n, ll m) {
		double ret = 1;
		for (ll a = 1; a <= ((n + 1) / 2); ++a) {
			for (ll b = 1; b <= ((m + 1) / 2); ++b) {
				double ca = cos(numbers::pi * a / (n + 1)), cb = cos(numbers::pi * b / (m + 1));
				ret *= 4 * (ca * ca + cb * cb);
			}
		}
		return ll(round(ret));
	}

	void test(auto f) {
		EXPECT_EQ(f(0, 0), 1);
		EXPECT_EQ(f(4, 7), 781);
	}
}

TEST(C076CountingTilings, solve1) {
	test(solve1);
}

TEST(C076CountingTilings, solve2) {
	test(solve2);
}

TEST(C076CountingTilings, solve3) {
	test(solve3);
}
