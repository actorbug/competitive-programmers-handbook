#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c26_3_string_hashing.h"

namespace {
	vector<bool> knapsack(const vector<ll>& w) {
		ll s = reduce(w.begin(), w.end());
		unordered_map<ll, ll> w2;
		for (ll i : w)
			++w2[i];
		vector<bool> possible(s + 1);
		possible[0] = true;
		for (auto [k, v] : w2) {
			for (ll x = s - k; x >= 0; --x) {
				if (possible[x]) {
					for (ll y = x + k, z = min(x + k * v, s); y <= z; y += k) {
						if (possible[y])
							break;
						possible[y] = true;
					}
				}
			}
		}
		return possible;
	}

	ll string_construction(const string& s, const unordered_set<string>& d) {
		vector<ll> count(ssize(s) + 1);
		count[0] = 1;
		Preprocessing sh(s);
		auto dh = d | views::transform(Preprocessing<>::hash) | ranges::to<unordered_set>();
		auto dp = d | views::transform([](const auto& i) { return ssize(i); }) | ranges::to<unordered_set>();
		for (ll i = 1; i <= ssize(s); ++i) {
			for (ll j : dp) {
				if (i >= j && dh.contains(sh.subhash(i - j, i)) && d.contains(s.substr(i - j, j))) {
					count[i] += count[i - j];
				}
			}
		}
		return count.back();
	}
}

TEST(C272IntegerPartitions, knapsack) {
	EXPECT_EQ(knapsack({}), vector<bool>{true});
	EXPECT_EQ(knapsack({1,3,3}), (vector<bool>{true,true,false,true,true,false,true,true}));
}

TEST(C272IntegerPartitions, stringConstruction) {
	EXPECT_EQ(string_construction("", {}), 1);
	EXPECT_EQ(string_construction("ABAB", {"A","B","AB"}), 4);
	EXPECT_EQ(string_construction("ABAB", {"A","BA"}), 0);
}
