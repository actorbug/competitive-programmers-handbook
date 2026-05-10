#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "util.h"

namespace {
    ll scenario1(ll n, ll k) {
        return comb(n, k);
    }

    ll scenario2(ll n, ll k) {
        return comb(k + n - 1, k);
    }

    ll scenario3(ll n, ll k) {
        return comb(n - k + 1, n - 2 * k + 1);
    }
}

TEST(C221BinomialCoefficients, scenario1) {
    EXPECT_EQ(scenario1(5, 2), 10);
}

TEST(C221BinomialCoefficients, scenario2) {
    EXPECT_EQ(scenario2(5, 2), 15);
}

TEST(C221BinomialCoefficients, scenario3) {
    EXPECT_EQ(scenario3(5, 2), 6);
}
