#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c26_3_string_hashing.h"

TEST(C263StringHashing, Preprocessing) {
	Preprocessing<3, 97> p("ALLEY");
	EXPECT_EQ(p.h, (vector<ll>{0,65,77,16,20,52}));
	EXPECT_EQ(p.p, (vector<ll>{96,94,88,70,16,48}));
	EXPECT_EQ(p.subhash(0, 1), 65);
	EXPECT_EQ(p.subhash(0, 2), 77);
	EXPECT_EQ((Preprocessing<3, 97>("").find("")), 0);
	EXPECT_EQ((Preprocessing<3, 97>("ABABCBABC").find("ABC")), 2);
	EXPECT_EQ((Preprocessing<3, 97>("ABABCBABC").find("XXX")), -1);
	Preprocessing<3, 97> abc("ABC");
	Preprocessing<3, 97> abcd("ABCD");
	Preprocessing<3, 97> abd("ABD");
	EXPECT_GE(abc, abc);
	EXPECT_GE(abcd, abc);
	EXPECT_LT(abc, abcd);
	EXPECT_LT(abc, abd);
	EXPECT_GE(abd, abc);
}
