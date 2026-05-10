#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c15_2_union_find_structure.h"

TEST(C152UnionFindStructure, UnionFind) {
	UnionFind uf(8);
	uf.unite(3, 0);
	uf.unite(3, 6);
	uf.unite(1, 2);
	uf.unite(2, 5);
	uf.unite(2, 7);
	EXPECT_FALSE(uf.same(3, 1));
	EXPECT_EQ(uf.find(3), 3);
	uf.unite(3, 1);
	EXPECT_TRUE(uf.same(3, 1));
	EXPECT_EQ(uf.find(3), 1);
}
