#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "c09_4_additional_techniques.h"

TEST(C094AdditionalTechniques, indexCompression) {
	EXPECT_EQ(index_compression<ll>({}, 1), (unordered_map<ll, ll>{}));
	EXPECT_EQ(index_compression<ll>({ 555, 1'000'000'000, 8 }, 1), (unordered_map<ll, ll>{{ 8, 1 }, { 555, 2 }, { 1'000'000'000, 3 }}));
}

TEST(C094AdditionalTechniques, RangeUpdates) {
	RangeUpdates ru(vector<ll>{3});
	ru.add(0, 0, 5);
	EXPECT_EQ(ru[0], 8);

	ru = RangeUpdates({ 3,3,1,1,1,5,2,2 });
	ru.add(1, 4, 5);
	EXPECT_EQ(ru[0], 3);
	EXPECT_EQ(ru[1], 8);
	EXPECT_EQ(ru[4], 6);
	EXPECT_EQ(ru[5], 5);
}
