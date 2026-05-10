#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c23_1_operations.h"

M::M(vector<vector<double>> v) : v(move(v)) {}

M& M::operator+=(const M& other) {
	for (ll i = 0; i < ssize(v); ++i) {
		for (ll j = 0; j < ssize(v[0]); ++j) {
			v[i][j] += other.v[i][j];
		}
	}
	return *this;
}

M& M::operator-=(const M& other) {
	for (ll i = 0; i < ssize(v); ++i) {
		for (ll j = 0; j < ssize(v[0]); ++j) {
			v[i][j] -= other.v[i][j];
		}
	}
	return *this;
}

M& M::operator*=(double x) {
	for (ll i = 0; i < ssize(v); ++i) {
		for (ll j = 0; j < ssize(v[0]); ++j) {
			v[i][j] *= x;
		}
	}
	return *this;
}

M& M::operator*=(const M& other) {
	return *this = *this * other;
}

M& M::operator/=(double x) {
	for (ll i = 0; i < ssize(v); ++i) {
		for (ll j = 0; j < ssize(v[0]); ++j) {
			v[i][j] /= x;
		}
	}
	return *this;
}

M M::pow(ll n) const {
	if (n == 0) return identity(ssize(v));
	M u = pow(n / 2);
	u *= u;
	if (n % 2 == 1) u *= *this;
	return u;
}

M M::submatrix(ll i, ll j) const {
	M ret = *this;
	ret.v.erase(ret.v.begin() + i);
	for (auto& k : ret.v)
		k.erase(k.begin() + j);
	return ret;
}

double M::adj(ll i, ll j) const {
	return (((i + j) % 2) ? -1 : 1) * submatrix(i, j).det();
}

double M::det() const {
	ll n = ssize(v);
	if (n <= 1)
		return v[0][0];
	double ret = 0;
	for (ll j = 0; j < n; ++j)
		ret += v[0][j] * adj(0, j);
	return ret;
}

M M::inv() const {
	ll n = ssize(v);
	double d = det();
	vector<vector<double>> ret(n, vector<double>(n));
	for (ll i = 0; i < n; ++i) {
		for (ll j = 0; j < n; ++j) {
			ret[i][j] = adj(j, i) / d;
		}
	}
	return M(move(ret));
}

M M::transpose() const {
	vector<vector<double>> vec(v[0].size(), vector<double>(v.size()));
	for (ll i = 0; i < ssize(v); ++i) {
		for (ll j = 0; j < ssize(v[0]); ++j) {
			vec[j][i] = v[i][j];
		}
	}
	return M(move(vec));
}

M M::identity(ll n) {
	vector<vector<double>> vec(n, vector<double>(n));
	for (ll i = 0; i < n; ++i)
		vec[i][i] = 1;
	return M(move(vec));
}

M operator+(const M& a, const M& b) {
	return M(a) += b;
}

M operator-(const M& a, const M& b) {
	return M(a) -= b;
}

M operator*(const M& a, double x) {
	return M(a) *= x;
}

M operator*(double x, const M& a) {
	return M(a) *= x;
}

M operator*(const M& a, const M& b) {
	vector<vector<double>> ret(a.v.size(), vector<double>(b.v[0].size()));
	for (ll i = 0; i < ssize(a.v); ++i) {
		for (ll j = 0; j < ssize(b.v[0]); ++j) {
			for (ll k = 0; k < ssize(a.v[0]); ++k) {
				ret[i][j] += a.v[i][k] * b.v[k][j];
			}
		}
	}
	return M(move(ret));
}

M operator/(const M& a, double x) {
	return M(a) /= x;
}

TEST(C231Operations, add) {
	EXPECT_EQ(M({{6,1,4},{3,9,2}})+M({{4,9,3},{8,1,3}}),M({{10,10,7},{11,10,5}}));
}

TEST(C231Operations, mul1) {
	EXPECT_EQ(2ll * M({{6,1,4},{3,9,2}}),M({{12,2,8},{6,18,4}}));
}

TEST(C231Operations, mul2) {
	EXPECT_EQ(M({{1,4},{3,9},{8,6}})*M({{1,6},{2,9}}),M({{9,42},{21,99},{20,102}}));
}

TEST(C231Operations, identity) {
	EXPECT_EQ(M::identity(3),M({{1,0,0},{0,1,0},{0,0,1}}));
}

TEST(C231Operations, pow) {
	EXPECT_EQ(M({{2,5},{1,4}}).pow(3), M({{48,165},{33,114}}));
}

TEST(C231Operations, det) {
	EXPECT_EQ(M({{3,4},{1,6}}).det(),14);
	EXPECT_EQ(M({{2,4,3},{5,1,6},{7,2,4}}).det(),81);
}

TEST(C231Operations, inv) {
	EXPECT_EQ(M({{2,4,3},{5,1,6},{7,2,4}}).inv(), M({{-8./81,-10./81,7./27},{22./81,-13./81,1./27},{1./27,8./27,-2./9}}));
}

TEST(C231Operations, transpose) {
	EXPECT_EQ(M({{6,1,4},{3,9,2}}).transpose(), M({{6,3},{1,9},{4,2}}));
}
