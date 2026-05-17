#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "util.h"

ll ipow(ll x, ll n) {
	if (n == 0) return 1;
	ll u = ipow(x, n / 2);
	u *= u;
	if (n % 2 == 1) u *= x;
	return u;
}

ll isqrt(ll x) {
	if (x <= 1)
		return x;
	ll k = bit_width(ull(x - 1)) / 2, s = 1ll << k, t = (s + (x >> k)) / 2;
	while (t < s) {
		s = t;
		t = (s + (x / s)) / 2;
	}
	return s;
}

ll comb(ll n, ll r) {
	r = min(r, n - r);
	ll ret = 1;
	for (ll i = 1; i <= r; ++i)
		ret = ret * (n - r + i) / i;
	return ret;
}

bool next_product(vector<ll>& vec, ll n) {
	ll i;
	for (i = ssize(vec) - 1; i >= 0; --i) {
		ll j = (vec[i] + 1) % n;
		vec[i] = j;
		if (j > 0)
			break;
	}
	return i >= 0;
}

vector<vector<ll>> reversed_adj(const vector<vector<ll>>& adj) {
	vector<vector<ll>> radj(adj.size());
	for (ll i = 0; i < ssize(adj); ++i) {
		for (ll j : adj[i]) {
			radj[j].push_back(i);
		}
	}
	return radj;
}

vector<vector<ll>> delweight(const vector<vector<pair<ll, ll>>>& adj) {
	vector<vector<ll>> ret(adj.size());
	for (ll i = 0; i < ssize(adj); ++i)
		for (auto [v, _] : adj[i])
			ret[i].push_back(v);
	return ret;
}
