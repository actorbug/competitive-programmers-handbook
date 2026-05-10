#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c21_1_primes_and_factors.h"
#include "c21_2_modular_arithmetic.h"

namespace {
	ll modpow(ll x, ll n, ll m) {
		if (n == 0) return 1 % m;
		ll u = modpow(x, n / 2, m);
		u = (u * u) % m;
		if (n % 2 == 1) u = (u * x) % m;
		return u;
	}
}

ll modinv(ll x, ll m) {
	return modpow(x, totient(m) - 1, m);
}

TEST(C212ModularArithmetic, modpow) {
	EXPECT_EQ(modpow(2, 3, 7), 1);
}

TEST(C212ModularArithmetic, modinv) {
	EXPECT_EQ(modinv(6, 17), 3);
}
