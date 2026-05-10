#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	ll algorithm1(const vector<ll>& array) {
		ll n = ssize(array);
		ll best = 0;
		for (ll a = 0; a < n; ++a) {
			for (ll b = a; b < n; ++b) {
				ll sum = 0;
				for (ll k = a; k <= b; ++k) {
					sum += array[k];
				}
				best = max(best, sum);
			}
		}
		return best;
	}

	ll algorithm2(const vector<ll>& array) {
		ll n = ssize(array);
		ll best = 0;
		for (ll a = 0; a < n; ++a) {
			ll sum = 0;
			for (ll b = a; b < n; ++b) {
				sum += array[b];
				best = max(best, sum);
			}
		}
		return best;
	}

	ll algorithm3(const vector<ll>& array) {
		ll n = ssize(array);
		ll best = 0, sum = 0;
		for (ll k = 0; k < n; ++k) {
			sum = max(array[k], sum + array[k]);
			best = max(best, sum);
		}
		return best;
	}

	void test(auto f) {
		EXPECT_EQ(f({}), 0);
		EXPECT_EQ(f({ -1 }), 0);
		EXPECT_EQ(f({ -1,2,4,-3,5,2,-5,2 }), 10);
	}
}

TEST(C024MaximumSubarraySum, algorithm1) {
	test(algorithm1);
}

TEST(C024MaximumSubarraySum, algorithm2) {
	test(algorithm2);
}

TEST(C024MaximumSubarraySum, algorithm3) {
	test(algorithm3);
}
