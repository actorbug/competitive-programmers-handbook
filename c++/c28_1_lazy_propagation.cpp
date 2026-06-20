#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct LazySegTree {
		LazySegTree(const vector<ll>& ary) : n(1ll << bit_width(max(ary.size(), 1uz) - 1)), s(n * 2), z(n * 2) {
			ranges::copy(ary, s.begin() + n);
			for (ll i = n - 1; i > 0; --i)
				s[i] = s[2 * i] + s[2 * i + 1];
		}
		void apply(ll k, ll x, ll y) const {
			if (z[k]) {
				s[k] += z[k] * (y - x + 1);
				if (x < y) {
					z[2 * k] += z[k];
					z[2 * k + 1] += z[k];
				}
				z[k] = 0;
			}
		}
		ll sum_rec(ll a, ll b, ll k, ll x, ll y) const {
			apply(k, x, y);
			if (b < x || a > y) return 0;
			if (a <= x && y <= b) return s[k];
			ll d = (x + y) / 2;
			return sum_rec(a, b, 2 * k, x, d) + sum_rec(a, b, 2 * k + 1, d + 1, y);
		}
		ll sum(ll a, ll b) const {
			return sum_rec(a, b, 1, 0, n - 1);
		}
		void add_rec(ll a, ll b, ll u, ll k, ll x, ll y) {
			apply(k, x, y);
			if (b < x || a > y) return;
			if (a <= x && y <= b) {
				z[k] += u;
				return;
			}
			ll d = (x + y) / 2;
			s[k] += u * (min(b, y) - max(a, x) + 1);
			add_rec(a, b, u, 2 * k, x, d);
			add_rec(a, b, u, 2 * k + 1, d + 1, y);
		}
		void add(ll a, ll b, ll u) {
			add_rec(a, b, u, 1, 0, n - 1);
		}
	private:
		ll n;
		mutable vector<ll> s, z;
	};

	vector<ll> add_poly(const vector<ll>& a, const vector<ll>& b) {
		ll m = max(ssize(a), ssize(b));
		vector<ll> ret(m);
		for (ll i = 0; i < m; ++i) {
			ret[i] = ((i < ssize(a)) ? a[i] : 0) + ((i < ssize(b)) ? b[i] : 0);
		}
		return ret;
	}

	vector<ll> shift_poly(vector<ll> t, ll h) {
		t.resize(3);
		vector<ll> r = { t[0] + h * (t[1] + h * t[2]), t[1] + h * t[2] * 2, t[2] };
		while (!r.empty() && r.back() == 0)
			r.pop_back();
		return r;
	}

	ll ind_sum_poly(const vector<ll>& z, ll n) {
		ll ret = 0;
		if (z.size() > 0) {
			ret += z[0] * n;
			if (z.size() > 1) {
				ret += z[1] * n * (n - 1) / 2;
			}
		}
		return ret;
	}

	struct PolyLazySegTree {
		PolyLazySegTree(const vector<ll>& ary) : n(1ll << bit_width(max(ary.size(), 1uz) - 1)), s(n * 2), z(n * 2) {
			ranges::copy(ary, s.begin() + n);
			for (ll i = n - 1; i > 0; --i)
				s[i] = s[2 * i] + s[2 * i + 1];
		}
		void apply(ll k, ll x, ll y) const {
			if (!z[k].empty()) {
				s[k] += ind_sum_poly(z[k], y - x + 1);
				if (x < y) {
					z[2 * k] = add_poly(z[2 * k], z[k]);
					z[2 * k + 1] = add_poly(z[2 * k + 1], shift_poly(z[k], (y - x + 1) / 2));
				}
				z[k].clear();
			}
		}
		ll sum_rec(ll a, ll b, ll k, ll x, ll y) const {
			apply(k, x, y);
			if (b < x || a > y) return 0;
			if (a <= x && y <= b) return s[k];
			ll d = (x + y) / 2;
			return sum_rec(a, b, 2 * k, x, d) + sum_rec(a, b, 2 * k + 1, d + 1, y);
		}
		ll sum(ll a, ll b) const {
			return sum_rec(a, b, 1, 0, n - 1);
		}
		void add_rec(ll a, ll b, const vector<ll>& u, ll k, ll x, ll y) {
			apply(k, x, y);
			if (b < x || a > y) return;
			if (a <= x && y <= b) {
				z[k] = add_poly(z[k], shift_poly(u, x - a));
				return;
			}
			ll d = (x + y) / 2;
			s[k] += ind_sum_poly(u ,min(b, y) - a + 1) - ind_sum_poly(u, max(0ll, x - a));
			add_rec(a, b, u, 2 * k, x, d);
			add_rec(a, b, u, 2 * k + 1, d + 1, y);
		}
		void add(ll a, ll b, const vector<ll>& u) {
			add_rec(a, b, u, 1, 0, n - 1);
		}
	private:
		ll n;
		mutable vector<ll> s;
		mutable vector<vector<ll>> z;
	};
}

TEST(C281LazyPropagation, LazySegTree) {
	LazySegTree s({});
	EXPECT_EQ(s.sum(0, -1), 0);
	s = LazySegTree({ 5,8,6,3,2,7,2,6 });
	EXPECT_EQ(s.sum(2, 7), 26);
	s.add(5, 5, 7);
	EXPECT_EQ(s.sum(2, 7), 33);
	s = LazySegTree({ 5,8,6,3,2,7,2,6,7,1,7,5,6,2,3,2 });
	s.add(5, 13, 2);
	EXPECT_EQ(s.sum(10, 13), 28);
}

TEST(C281LazyPropagation, PolyLazySegTree) {
	PolyLazySegTree s({});
	EXPECT_EQ(s.sum(0, -1), 0);
	s = PolyLazySegTree({ 5,8,6,3,2,7,2,6 });
	EXPECT_EQ(s.sum(2, 7), 26);
	s.add(5, 5, { 7 });
	EXPECT_EQ(s.sum(2, 7), 33);
	s = PolyLazySegTree({ 5,8,6,3,2,7,2,6,7,1,7,5,6,2,3,2 });
	s.add(5, 13, { 2 });
	EXPECT_EQ(s.sum(10, 13), 28);
	s = PolyLazySegTree({ 5,8,6,3,2,7,2,6,7,1,7,5,6,2,3,2 });
	s.add(5, 13, { 1, 1 });
	EXPECT_EQ(s.sum(10, 13), 50);
}
