#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c21_1_primes_and_factors.h"
#include "util.h"

namespace {
	bool prime(ll n) {
		if (n < 2) return false;
		for (ll x = 2; x * x <= n; ++x) {
			if (n % x == 0) return false;
		}
		return true;
	}

	vector<ll> factors(ll n) {
		vector<ll> f;
		for (ll x = 2; x * x <= n; ++x) {
			while (n % x == 0) {
				f.push_back(x);
				n /= x;
			}
		}
		if (n > 1) f.push_back(n);
		return f;
	}

	vector<pair<ll, ll>> factors_e(ll n) {
		vector<pair<ll, ll>> ret;
		for (const auto& v : factors(n) | views::chunk_by(equal_to()))
			ret.emplace_back(v[0], ssize(v));
		return ret;
	}

	ll factor_count(ll n) {
		ll ret = 1;
		for (auto [_, a] : factors_e(n))
			ret *= a + 1;
		return ret;
	}

	ll factor_sum(ll n) {
		ll ret = 1;
		for (auto [p, a] : factors_e(n))
			ret *= (ipow(p, a + 1) - 1) / (p - 1);
		return ret;
	}

	ll factor_product(ll n) {
		ll c = factor_count(n);
		return ipow(n, c / 2) * ((c % 2) ? isqrt(n) : 1);
	}

	bool is_perfect(ll n) {
		return n == factor_sum(n) - n;
	}

	double density(ll n) {
		return n / log(n);
	}

	vector<ll> eratosthenes(ll n) {
		vector<ll> sieve(n + 1);
		sieve[0] = sieve[1] = 1;
		for (int x = 2; x <= n; x++) {
			if (sieve[x]) continue;
			for (int u = 2 * x; u <= n; u += x)
				sieve[u] = x;
		}
		return sieve;
	}

	ll gcd_(ll a, ll b) {
		if (b == 0) return a;
		return gcd_(b, a % b);
	}
}

ll totient(ll n) {
	ll ret = 1;
	for (auto [p, a] : factors_e(n))
		ret *= (p - 1) * ipow(p, a - 1);
	return ret;
}

TEST(C211PrimesAndFactors, prime) {
	EXPECT_FALSE(prime(1));
	EXPECT_FALSE(prime(35));
	EXPECT_TRUE(prime(7));
	EXPECT_TRUE(prime(19));
	EXPECT_TRUE(prime(41));
}

TEST(C211PrimesAndFactors, factors) {
	EXPECT_EQ(factors(1) | ranges::to<multiset>(), multiset<ll>{});
	EXPECT_EQ(factors(84) | ranges::to<multiset>(), (multiset<ll>{2, 2, 3, 7}));
}

TEST(C211PrimesAndFactors, factorsE) {
	EXPECT_EQ(factors_e(1) | ranges::to<multiset>(), (multiset<pair<ll, ll>>{}));
	EXPECT_EQ(factors_e(84) | ranges::to<multiset>(), (multiset<pair<ll, ll>>{{2, 2}, {3,1}, {7,1}}));
}

TEST(C211PrimesAndFactors, factorCount) {
	EXPECT_EQ(factor_count(1), 1);
	EXPECT_EQ(factor_count(84), 12);
}

TEST(C211PrimesAndFactors, factorSum) {
	EXPECT_EQ(factor_sum(84), 224);
}

TEST(C211PrimesAndFactors, factorProduct) {
	EXPECT_EQ(factor_product(84), 351298031616);
}

TEST(C211PrimesAndFactors, isPerfect) {
	EXPECT_FALSE(is_perfect(1));
	EXPECT_TRUE(is_perfect(28));
}

TEST(C211PrimesAndFactors, density) {
	EXPECT_NEAR(density(1'000'000), 72382, 0.5);
}

TEST(C211PrimesAndFactors, eratosthenes) {
	EXPECT_EQ(eratosthenes(20), (vector<ll>{1,1,0,0,2,0,3,0,2,3,5,0,3,0,7,5,2,0,3,0,5}));
}

TEST(C211PrimesAndFactors, gcd) {
	EXPECT_EQ(gcd_(24, 36), 12);
	EXPECT_EQ(gcd_(13, 8), 1);
}

TEST(C211PrimesAndFactors, totient) {
	EXPECT_EQ(totient(12), 4);
	EXPECT_EQ(totient(2), 1);
}
