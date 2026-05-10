#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 2;

namespace {
	ll optimal_selection(const vector<vector<ll>>& price) {
		if (price.empty())
			return 0;
		ll n = ssize(price[0]), k = ssize(price);
		if (n < k)
			return -1;
		vector<vector<ll>> total(1ll << k, vector<ll>(n, INF));
		total[0][0] = 0;
		for (ll x = 0; x < k; ++x) {
			total[1ll << x][0] = price[x][0];
		}
		for (ll d = 1; d < n; ++d) {
			for (ll s = 0; s < (1ll << k); ++s) {
				total[s][d] = total[s][d - 1];
				for (ll x = 0; x < k; ++x) {
					if (s & (1ll << x)) {
						total[s][d] = min(total[s][d],
							total[s ^ (1ll << x)][d - 1] + price[x][d]);
					}
				}
			}
		}
		return total.back().back();
	}

	ll from_permutations_to_subsets(ll x, const vector<ll>& weight) {
		if (weight.empty())
			return 0;
		if (ranges::any_of(weight, [&](ll w) { return x < w; }))
			return -1;
		ll n = ssize(weight);
		vector<pair<ll, ll>> best(1ll << n);
		best[0] = { 1,0 };
		for (ll s = 1; s < (1ll << n); ++s) {
			// initial value: n+1 rides are needed
			best[s] = { n + 1,0 };
			for (ll p = 0; p < n; ++p) {
				if (s & (1ll << p)) {
					auto option = best[s ^ (1ll << p)];
					if (option.second + weight[p] <= x) {
						// add p to an existing ride
						option.second += weight[p];
					}
					else {
						// reserve a new ride for p
						option.first++;
						option.second = weight[p];
					}
					best[s] = min(best[s], option);
				}
			}
		}
		return best.back().first;
	}

	vector<ll> counting_subsets(const vector<ll>& value) {
		ll n = bit_width(value.size()) - 1;
		vector<ll> sum = value;
		for (ll k = 0; k < n; ++k) {
			for (ll s = 0; s < (1ll << n); ++s) {
				if (s & (1ll << k)) sum[s] += sum[s ^ (1ll << k)];
			}
		}
		return sum;
	}
}

TEST(C105DynamicProgramming, optimalSelection) {
	EXPECT_EQ(optimal_selection({}), 0);
	EXPECT_EQ(optimal_selection({ {} }), -1);
	EXPECT_EQ(optimal_selection({ {6,9,5,2,8,9,1,6} ,{8,2,6,2,7,5,7,2},{5,3,9,7,3,5,1,4} }), 5);
}

TEST(C105DynamicProgramming, fromPermutationsToSubsets) {
	EXPECT_EQ(from_permutations_to_subsets(10, {}), 0);
	EXPECT_EQ(from_permutations_to_subsets(10, {0}), 1);
	EXPECT_EQ(from_permutations_to_subsets(2, {3}), -1);
	EXPECT_EQ(from_permutations_to_subsets(10, { 2,3,3,5,6 }), 2);
}

TEST(C105DynamicProgramming, countingSubsets) {
	EXPECT_EQ(counting_subsets({ 1 }), vector<ll>{ 1 });
	EXPECT_EQ(counting_subsets({ 3,1,4,5,5,1,3,3 }), (vector<ll>{ 3,4,7,13,8,10,15,25 }));
}
