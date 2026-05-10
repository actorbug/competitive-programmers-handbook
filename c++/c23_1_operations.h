#pragma once

struct M {
	M(vector<vector<double>> v);
	bool operator==(const M& other) const = default;
	M& operator+=(const M& other);
	M& operator-=(const M& other);
	M& operator*=(double x);
	M& operator*=(const M& other);
	M& operator/=(double x);
	M pow(ll n) const;
	M submatrix(ll i, ll j) const;
	double adj(ll i, ll j) const;
	double det() const;
	M inv() const;
	M transpose() const;
	static M identity(ll n);
	vector<vector<double>> v;
};

M operator+(const M& a, const M& b);
M operator-(const M& a, const M& b);
M operator*(const M& a, double x);
M operator*(double x, const M& a);
M operator*(const M& a, const M& b);
M operator/(const M& a, double x);
