#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct SegTree {
		SegTree(size_t n) : tree(1ll << (bit_width(n ? n - 1 : 0) + 1)) {}
		SegTree(const vector<ll>& ary) : SegTree(ary.size()) {
			ll n = ssize(tree) / 2;
			ranges::copy(ary, tree.begin() + n);
			for (ll i = n - 1; i > 0; --i)
				tree[i] = tree[2 * i] + tree[2 * i + 1];
		}
		ll sum(ll a, ll b) const {
			ll n = ssize(tree) / 2;
			a += n; b += n;
			ll s = 0;
			while (a <= b) {
				if (a % 2 == 1) s += tree[a++];
				if (b % 2 == 0) s += tree[b--];
				a /= 2; b /= 2;
			}
			return s;
		}
		void add(ll k, ll x) {
			k += ssize(tree) / 2;
			tree[k] += x;
			for (k /= 2; k >= 1; k /= 2) {
				tree[k] = tree[2 * k] + tree[2 * k + 1];
			}
		}
		vector<ll> tree;
	};

	struct SegTree2D {
		SegTree2D(const vector<vector<ll>>& ary) : tree(1ll << (bit_width(ary.empty() ? 0 : ary.size() - 1) + 1), SegTree(ary.empty() ? 0 : ary[0].size())) {
			ll n = ssize(tree) / 2;
			ranges::copy(ary, tree.begin() + n);
			for (ll i = n - 1; i > 0; --i)
				for (ll j = 0; j < ssize(tree[i].tree); ++j)
					tree[i].tree[j] = tree[2 * i].tree[j] + tree[2 * i + 1].tree[j];
		}
		ll sum(ll ya, ll yb, ll xa, ll xb) const {
			ll n = ssize(tree) / 2;
			ya += n; yb += n;
			ll s = 0;
			while (ya <= yb) {
				if (ya % 2 == 1) s += tree[ya++].sum(xa, xb);
				if (yb % 2 == 0) s += tree[yb--].sum(xa, xb);
				ya /= 2; yb /= 2;
			}
			return s;
		}
		void add(ll y, ll x, ll v) {
			y += ssize(tree) / 2;
			while (y >= 1) {
				tree[y].add(x, v);
				y /= 2;
			}
		}
	private:
		vector<SegTree> tree;
	};
}

TEST(C284TwoDimensionality, SegTree2D) {
	SegTree2D s({});
	EXPECT_EQ(s.sum(0, -1, 0, -1), 0);
	s = SegTree2D({ {7,6,1,6} ,{8,7,5,2},{3,9,7,1},{8,5,3,8} });
	EXPECT_EQ(s.sum(1, 3, 0, 1), 40);
	s.add(1, 0, 2);
	EXPECT_EQ(s.sum(1, 3, 0, 1), 42);
}