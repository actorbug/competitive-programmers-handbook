#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c17_1_kosarajus_algorithm.h"

namespace {
	struct TwoSatProblem {
		TwoSatProblem(ll n) : adj(n * 2 + 1) {}
		void add(ll i, bool f, ll j, bool g) {
			ll v0 = i * 2 - f, v1 = j * 2 - g;
			adj[(v0 + 1 ^ 1) - 1].push_back(v1);
			adj[(v1 + 1 ^ 1) - 1].push_back(v0);
		}
		vector<bool> solve() const {
			vector<ll> connect(adj.size());
			for (ll count = 0; const auto& nodes : kosaraju(adj)) {
				for (ll x : nodes)
					connect[x] = count;
				++count;
			}
			vector<bool> ret(adj.size() / 2 + 1);
			for (ll i = 1; i < ssize(ret); ++i) {
				if (connect[i * 2] == connect[i * 2 - 1])
					return {};
				ret[i] = connect[i * 2 - 1] > connect[i * 2];
			}
			return ret;
		}
	private:
		vector<vector<ll>> adj;
	};
}

TEST(C172TwoSatProblem, TwoSatProblem) {
	TwoSatProblem ts(1);
	ts.add(1, true, 1, true);
	EXPECT_EQ(ts.solve(), (vector<bool>{false, true}));
	ts = TwoSatProblem(4);
	ts.add(2, true, 1, false);
	ts.add(1, false, 2, false);
	ts.add(1, true, 3, true);
	ts.add(2, false, 3, false);
	ts.add(1, true, 4, true);
	EXPECT_EQ(ts.solve(), (vector<bool>{false, false, false, true, true}));
	ts = TwoSatProblem(3);
	ts.add(1, true, 2, true);
	ts.add(1, true, 2, false);
	ts.add(1, false, 3, true);
	ts.add(1, false, 3, false);
	EXPECT_EQ(ts.solve(), vector<bool>{});
}
