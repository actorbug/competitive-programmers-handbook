#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c17_1_kosarajus_algorithm.h"

namespace {
	struct TwoSatProblem {
		TwoSatProblem(ll n) : adj(n * 2) {}
		void add(ll i, bool f, ll j, bool g) {
			ll v0 = i * 2 + f, v1 = j * 2 + g;
			adj[v0 ^ 1].push_back(v1);
			adj[v1 ^ 1].push_back(v0);
		}
		vector<bool> solve() const {
			auto connect = kosaraju(adj);
			vector<bool> ret(adj.size() / 2);
			for (ll i = 0; i < ssize(ret); ++i) {
				if (connect[i * 2] == connect[i * 2 + 1])
					return {};
				ret[i] = connect[i * 2 + 1] > connect[i * 2];
			}
			return ret;
		}
	private:
		vector<vector<ll>> adj;
	};
}

TEST(C172TwoSatProblem, TwoSatProblem) {
	TwoSatProblem ts(1);
	ts.add(0, true, 0, true);
	EXPECT_EQ(ts.solve(), vector<bool>{true});
	ts = TwoSatProblem(4);
	ts.add(1, true, 0, false);
	ts.add(0, false, 1, false);
	ts.add(0, true, 2, true);
	ts.add(1, false, 2, false);
	ts.add(0, true, 3, true);
	EXPECT_EQ(ts.solve(), (vector<bool>{false, false, true, true}));
	ts = TwoSatProblem(3);
	ts.add(0, true, 1, true);
	ts.add(0, true, 1, false);
	ts.add(0, false, 2, true);
	ts.add(0, false, 2, false);
	EXPECT_EQ(ts.solve(), vector<bool>{});
}
