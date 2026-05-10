#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "util.h"

namespace {
	double expected_empty(double n) {
		return n * pow((n - 1) / n, n);
	}

	double expected_uniform(double a, double b) {
		return (a + b) / 2;
	}

	double probability_binomial(double p, ll n, ll x) {
		return pow(p, x) * pow(1 - p, n - x) * comb(n, x);
	}

	double expected_binomial(double p, ll n) {
		return p * n;
	}

	double probability_geometric(double p, ll x) {
		return pow(1 - p, x - 1) * p;
	}

	double expected_geometric(double p) {
		return 1 / p;
	}
}

TEST(C243RandomVariables, expectedEmpty) {
	EXPECT_DOUBLE_EQ(expected_empty(2), 0.5);
}

TEST(C243RandomVariables, expectedUniform) {
	EXPECT_DOUBLE_EQ(expected_uniform(1, 6), 3.5);
}

TEST(C243RandomVariables, probabilityBinomial) {
	EXPECT_DOUBLE_EQ(probability_binomial(1./6, 10, 3), 390625./2519424);
}

TEST(C243RandomVariables, expectedBinomial) {
	EXPECT_DOUBLE_EQ(expected_binomial(1./6, 10), 5./3);
}

TEST(C243RandomVariables, probabilityGeometric) {
	EXPECT_DOUBLE_EQ(probability_geometric(1./6, 4), 125./1296);
}

TEST(C243RandomVariables, expectedGeometric) {
	EXPECT_DOUBLE_EQ(expected_geometric(1. / 6), 6);
}
