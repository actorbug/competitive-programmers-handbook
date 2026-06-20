#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

namespace {
	ll checkbit(ll x, ll k) {
		return x & (1ll << k);
	}
	ll setbit(ll x, ll k, bool b) {
		return b ? x | (1ll << k) : x & ~(1ll << k);
	}
	ll invertbit(ll x, ll k) {
		return x ^ (1ll << k);
	}
	ll resetlastbit(ll x) {
		return x & (x - 1);
	}
	ll getlastbit(ll x) {
		return x & -x;
	}
	ll invertafterlastbit(ll x) {
		return x | (x - 1);
	}
	bool is2n(ll x) {
		return resetlastbit(x) == 0;
	}
	ll parity(ull x) {
		return popcount(x) % 2;
	}
}

TEST(C102BitOperations, checkbit) {
	EXPECT_TRUE(checkbit(0b1100, 2));
	EXPECT_FALSE(checkbit(0b1000, 2));
}

TEST(C102BitOperations, setbit) {
	EXPECT_EQ(setbit(0b1000, 2, true), 0b1100);
	EXPECT_EQ(setbit(0b1100, 2, false), 0b1000);
}

TEST(C102BitOperations, invertbit) {
	EXPECT_EQ(invertbit(0b1100, 2), 0b1000);
	EXPECT_EQ(invertbit(0b1000, 2), 0b1100);
}

TEST(C102BitOperations, resetlastbit) {
	EXPECT_EQ(resetlastbit(0b0), 0b0);
	EXPECT_EQ(resetlastbit(0b1100), 0b1000);
}

TEST(C102BitOperations, getlastbit) {
	EXPECT_EQ(getlastbit(0b0), 0b0);
	EXPECT_EQ(getlastbit(0b1100), 0b100);
}

TEST(C102BitOperations, invertafterlastbit) {
	EXPECT_EQ(invertafterlastbit(0b0), ~0b0);
	EXPECT_EQ(invertafterlastbit(0b1100), 0b1111);
}

TEST(C102BitOperations, is2n) {
	EXPECT_TRUE(is2n(0b1000));
	EXPECT_FALSE(is2n(0b1100));
}

TEST(C102BitOperations, parity) {
	ull x = 0b0000'0000'0000'0000'0001'0100'1101'0000;
	EXPECT_EQ(parity(x), 1);
}
