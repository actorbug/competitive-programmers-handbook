#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	ll method1(const vector<ll>& array, ll x) {
		ll n = ssize(array);
		ll a = 0, b = n - 1;
		while (a <= b) {
			ll k = (a + b) / 2;
			if (array[k] == x) {
				// x found at index k
				return k;
			}
			if (array[k] > x) b = k - 1;
			else a = k + 1;
		}
		return -1;
	}

	ll method2(const vector<ll>& array, ll x) {
		ll n = ssize(array);
		ll k = 0;
		for (ll b = n / 2; b >= 1; b /= 2) {
			while (k + b < n && array[k + b] <= x) k += b;
		}
		if (k < ssize(array) && array[k] == x) {
			// x found at index k
			return k;
		}
		return -1;
	}

	ll smallest(ll z, auto ok) {
		ll x = -1;
		for (ll b = z; b >= 1; b /= 2) {
			while (!ok(x + b)) x += b;
		}
		return x + 1;
	}

	ll maximum(ll z, auto f) {
		ll x = -1;
		for (ll b = z; b >= 1; b /= 2) {
			while (f(x + b) < f(x + b + 1)) x += b;
		}
		return x + 1;
	}

	void test(auto f) {
		EXPECT_EQ(f({}, 5), -1);
		EXPECT_EQ(f({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, 5), 5);
		EXPECT_EQ(f({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, 10), -1);
	}
}

TEST(C033BinarySearch, method1) {
	test(method1);
}

TEST(C033BinarySearch, method2) {
	test(method2);
}

TEST(C033BinarySearch, smallest) {
	EXPECT_EQ(smallest(10, [](ll x) { return x > 4; }), 5);
}

TEST(C033BinarySearch, maximum) {
	EXPECT_EQ(maximum(10, [](ll x) { return -abs(5 - x); }), 5);
}
