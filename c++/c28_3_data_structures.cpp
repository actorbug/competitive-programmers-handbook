#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct SegTree {
		SegTree(size_t n) : tree(1ll << (bit_width(max(n, 1uz) - 1) + 1)) {}
		SegTree(const vector<ll>& ary) : SegTree(ary.size()) {
			ll n = ssize(tree) / 2;
			for (ll i = 0; i < ssize(ary); ++i)
				++tree[n + i][ary[i]];
			for (ll i = n - 1; i > 0; --i) {
				tree[i] = tree[2 * i];
				for (auto [k, v] : tree[2 * i + 1])
					tree[i][k] += v;
			}
		}
		ll count(ll a, ll b, ll x) const {
			ll n = ssize(tree) / 2;
			a += n; b += n;
			ll s = 0;
			while (a <= b) {
				if (a % 2 == 1) {
					if (tree[a].contains(x))
						s += tree[a].at(x);
					++a;
				}
				if (b % 2 == 0) {
					if (tree[b].contains(x))
						s += tree[b].at(x);
					--b;
				}
				a /= 2; b /= 2;
			}
			return s;
		}
		void set(ll k, ll x) {
			k += ssize(tree) / 2;
			ll y = tree[k].begin()->first;
			tree[k].clear();
			++tree[k][x];
			for (k /= 2; k >= 1; k /= 2) {
				--tree[k][y];
				if (tree[k][y] <= 0)
					tree[k].erase(y);
				++tree[k][x];
			}
		}
	private:
		vector<unordered_map<ll, ll>> tree;
	};
}

TEST(C283DataStructures, SegTree) {
	SegTree s({});
	EXPECT_EQ(s.count(1, 0, -1), 0);
	s = SegTree({ 3,1,2,3,1,1,1,2 });
	EXPECT_EQ(s.count(1, 5, 1), 3);
	s.set(5, 2);
	EXPECT_EQ(s.count(1, 5, 1), 2);
}
