#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

TEST(C291ComplexNumbers, ComplexNumbers) {
	using P = complex<long double>;
	EXPECT_EQ(P(3, 1) + P(2, 2), P(5, 3));
	EXPECT_NEAR(abs(P(3, -1) - P(4, 2)), 3.16228l, 1e-5l);
	P v(4, 2);
	EXPECT_NEAR(arg(v), 0.463648l, 1e-6l);
	v *= polar(1.0l, 0.5l);
	EXPECT_NEAR(arg(v), 0.963648l, 1e-6l);
}