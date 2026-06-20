#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct SegTree {
		SegTree(size_t n) : tree(1ll << (bit_width(max(n, 1uz) - 1) + 1)) {}
		SegTree(const vector<ll>& ary) : SegTree(ary.size()) {
			ll n = ssize(tree) / 2;
			ranges::copy(ary, tree.begin() + n);
			for (ll i = n - 1; i > 0; --i)
				tree[i] = tree[2 * i] + tree[2 * i + 1];
		}
		ll sum_rec(ll a, ll b, ll k, ll x, ll y) const {
			if (b < x || a > y) return 0;
			if (a <= x && y <= b) return tree[k];
			ll d = (x + y) / 2;
			return sum_rec(a, b, 2 * k, x, d) + sum_rec(a, b, 2 * k + 1, d + 1, y);
		}
		ll sum(ll a, ll b) const {
			return sum_rec(a, b, 1, 0, ssize(tree) / 2 - 1);
		}
		void add(ll k, ll x) {
			k += ssize(tree) / 2;
			tree[k] += x;
			for (k /= 2; k >= 1; k /= 2)
				tree[k] = tree[2 * k] + tree[2 * k + 1];
		}
	private:
		vector<ll> tree;
	};
}

TEST(C280SegmentTreeRevisited, SegTree) {
	SegTree s({});
	EXPECT_EQ(s.sum(0, -1), 0);
	s = SegTree({ 5,8,6,3,2,7,2,6 });
	EXPECT_EQ(s.sum(2, 7), 26);
	s.add(5, 7);
	EXPECT_EQ(s.sum(2, 7), 33);
}
