#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "c09_2_binary_indexed_tree.h"

TEST(C092BinaryIndexedTree, BIT) {
	BIT b(0);
	EXPECT_EQ(b.sum(0), 0);
	b = BIT({ 1,3,4,8,6,1,4,2 });
	EXPECT_EQ(b.sum(7), 27);
	b.add(3, 7);
	EXPECT_EQ(b.sum(7), 34);
}
