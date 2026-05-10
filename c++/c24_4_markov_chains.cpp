#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c23_1_operations.h"

namespace {
	vector<double> markov(const M& mat, const vector<double>& init, ll m) {
		return (mat.pow(m)* M({ init }).transpose()).transpose().v[0];
	}
}
TEST(C244MarkovChains, markov) {
	M m({{0,0.5,0,0,0},{1,0,0.5,0,0},{0,0.5,0,0.5,0},{0,0,0.5,0,1},{0,0,0,0.5,0}});
	EXPECT_EQ(markov(m,{1,0,0,0,0},0),(vector<double>{1,0,0,0,0}));
	EXPECT_EQ(markov(m,{1,0,0,0,0},1),(vector<double>{0,1,0,0,0}));
	EXPECT_EQ(markov(m,{1,0,0,0,0},2),(vector<double>{0.5,0,0.5,0,0}));
}
