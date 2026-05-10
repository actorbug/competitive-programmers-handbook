#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

namespace {
	ll hamming(const string& a, const string& b) {
		ll k = min(ssize(a), ssize(b));
		ll d = 0;
		for (ll i = 0; i < k; ++i) {
			if (a[i] != b[i]) ++d;
		}
		return d;
	}

	ll hamming2(ull a, ull b) {
		return popcount(a ^ b);
	}

	ll subgrids(const vector<vector<bool>>& color) {
		ll n = color.empty() ? 0 : ssize(color[0]), total = 0;
		for (ll a = 0; a < ssize(color) - 1; ++a) {
			for (ll b = a + 1; b < ssize(color); ++b) {
				ll count = 0;
				for (int i = 0; i < n; ++i) {
					if (color[a][i] == 1 && color[b][i] == 1) ++count;
				}
				total += count * (count - 1) / 2;
			}
		}
		return total;
	}
	ll subgrids2(const vector<vector<ull>>& color) {
		ll n = color.empty() ? 0 : ssize(color[0]), total = 0;
		for (ll a = 0; a < ssize(color) - 1; ++a) {
			for (ll b = a + 1; b < ssize(color); ++b) {
				ll count = 0;
				for (int i = 0; i < n; ++i)
					count += popcount(color[a][i] & color[b][i]);
				total += count * (count - 1) / 2;
			}
		}
		return total;
	}
}

TEST(C104BitOptimizations, hamming) {
	EXPECT_EQ(hamming("", ""), 0);
	EXPECT_EQ(hamming("00111", "01101"), 2);
	EXPECT_EQ(hamming("00111", "11110"), 3);
	EXPECT_EQ(hamming("01101", "11110"), 3);
}

TEST(C104BitOptimizations, hamming2) {
	EXPECT_EQ(hamming2(0b0, 0b0), 0);
	EXPECT_EQ(hamming2(0b00111, 0b01101), 2);
	EXPECT_EQ(hamming2(0b00111, 0b11110), 3);
	EXPECT_EQ(hamming2(0b01101, 0b11110), 3);
}

TEST(C104BitOptimizations, subgrids) {
	EXPECT_EQ(subgrids({}), 0);
	EXPECT_EQ(subgrids({ {0,1,0,0,1},{0,1,1,0,0},{1,0,0,0,0},{0,1,1,0,1},{0,0,0,0,0} }), 2);
}

TEST(C104BitOptimizations, subgrids2) {
	EXPECT_EQ(subgrids2({}), 0);
	EXPECT_EQ(subgrids2({ {0b01001},{0b01100},{0b10000},{0b01101},{0b00000} }), 2);
}
