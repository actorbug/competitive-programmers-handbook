#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c23_1_operations.h"

namespace {
	constexpr double inf = numeric_limits<double>::infinity();

	M count(const M& m, ll n) {
		return m.pow(n);
	}

	M shortest(const M& x, ll n) {
		M id(vector<vector<double>>(x.v.size(), vector<double>(x.v.size(), inf)));
		for (ll i = 0; i < ssize(x.v); ++i)
			id.v[i][i] = 0;
		auto mul = [](const M& s, const M& o) {
			vector<vector<double>> ret(s.v.size(), vector<double>(o.v[0].size(), inf));
			for (ll i = 0; i < ssize(s.v); ++i) {
				for (ll j = 0; j < ssize(o.v[0]); ++j) {
					for (ll k = 0; k < ssize(s.v[0]); ++k) {
						ret[i][j] = min(ret[i][j], s.v[i][k] + o.v[k][j]);
					}
				}
			}
			return M(move(ret));
			};
		auto rec = [&](this auto self, ll n) -> M {
			if (n == 0) return id;
			M u = self(n / 2);
			u = mul(u, u);
			if (n % 2 == 1) u = mul(u, x);
			return u;
			};
		return rec(n);
	}

	ll kirchhoff(const vector<vector<ll>>& adj) {
		ll n = ssize(adj);
		vector<vector<double>> ret(n, vector<double>(n));
		for (ll i = 0; i < n; ++i)
			ret[i][i] = double(adj[i].size());
		for (ll i = 0; i < n; ++i) {
			for (ll j : adj[i]) {
				ret[i][j] = -1;
			}
		}
		return ll(M(move(ret)).submatrix(0, 0).det());
	}
}

TEST(C233GraphsAndMatrices, count) {
	EXPECT_EQ(count(M({{0,0,0,1,0,0},{1,0,0,0,1,1},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,0,0,0,0,0},{0,0,1,0,1,0}}),4),M({{0,0,1,1,1,0},{2,0,0,0,2,2},{0,2,0,0,0,0},{0,2,0,0,0,0},{0,0,0,0,0,0},{0,0,1,1,1,0}}));
}

TEST(C233GraphsAndMatrices, shortest) {
	EXPECT_EQ(shortest(M({{inf,inf,inf,4,inf,inf},{2,inf,inf,inf,1,2},{inf,4,inf,inf,inf,inf},{inf,1,inf,inf,inf,inf},{inf,inf,inf,inf,inf,inf},{inf,inf,3,inf,2,inf}}),4),M({{inf,inf,10,11,9,inf},{9,inf,inf,inf,8,9},{inf,11,inf,inf,inf,inf},{inf,8,inf,inf,inf,inf},{inf,inf,inf,inf,inf,inf},{inf,inf,12,13,11,inf}}));
}

TEST(C233GraphsAndMatrices, kirchhoff) {
	EXPECT_EQ(kirchhoff({{1,2,3},{0},{0,3},{0,2}}),3);
}
