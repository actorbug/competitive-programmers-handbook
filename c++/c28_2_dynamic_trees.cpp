#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

namespace {
	struct Sparse {
		struct Node {
			ll value;
			ll x, y;
			shared_ptr<Node> left, right;
			ll sum(ll a, ll b) const {
				if (b < x || a > y) return 0;
				if (a <= x && y <= b) return value;
				return (left ? left->sum(a, b) : 0) + (right ? right->sum(a, b) : 0);
			}
			void add(ll k, ll v) {
				value += v;
				if (x < y) {
					ll d = (x + y) / 2;
					if (k <= d)
						make_add(left, k, v, x, d);
					else
						make_add(right, k, v, d + 1, y);
				}
			}
			static void make_add(shared_ptr<Node>& node, ll k, ll v, ll x, ll y) {
				if (!node)
					node = make_shared<Node>(0, x, y);
				node->add(k, v);
			}
		};
		Sparse(size_t n) : root(make_shared<Node>(0, 0, (1ll << bit_width(n ? n - 1 : 0)) - 1)) {}
		Sparse(const Sparse& other) = delete;
		ll sum(ll a, ll b) const {
			return root->sum(a, b);
		}
		void add(ll k, ll v) {
			root->add(k, v);
		}
		shared_ptr<Node> root;
	};

	struct Persistent {
		struct Node {
			ll value;
			ll x, y;
			shared_ptr<Node> left, right;
			ll sum(ll a, ll b) const {
				if (b < x || a > y) return 0;
				if (a <= x && y <= b) return value;
				return (left ? left->sum(a, b) : 0) + (right ? right->sum(a, b) : 0);
			}
			void add(ll k, ll v) {
				value += v;
				if (x < y) {
					ll d = (x + y) / 2;
					if (k <= d)
						copy_add(left, k, v, x, d);
					else
						copy_add(right, k, v, d + 1, y);
				}
			}
			static void copy_add(shared_ptr<Node>& node, ll k, ll v, ll x, ll y) {
				if (node)
					node = make_shared<Node>(*node);
				else
					node = make_shared<Node>(0, x, y);
				node->add(k, v);
			}
		};
		Persistent(size_t n) : hist{ make_shared<Node>(0, 0, (1ll << bit_width(n ? n - 1 : 0)) - 1) } {}
		Persistent(const Persistent& other) = delete;
		ll sum(ll a, ll b, ll h = 0) const {
			return hist[hist.size() - h - 1]->sum(a, b);
		}
		void add(ll k, ll v) {
			hist.push_back(make_shared<Node>(*hist.back()));
			hist.back()->add(k, v);
		}
		vector<shared_ptr<Node>> hist;
	};
}


TEST(C282DynamicTrees, Sparse) {
	Sparse s(1);
	EXPECT_EQ(s.sum(0, -1), 0);
	s = Sparse(16);
	EXPECT_EQ(s.sum(2, 7), 0);
	s.add(3, 2);
	s.add(10, 3);
	EXPECT_EQ(s.sum(2, 7), 2);
}

TEST(C282DynamicTrees, Persistent) {
	Persistent s(1);
	EXPECT_EQ(s.sum(0, -1), 0);
	s = Persistent(16);
	EXPECT_EQ(s.sum(2, 7), 0);
	s.add(3, 2);
	s.add(10, 3);
	EXPECT_EQ(s.sum(2, 7), 2);
	EXPECT_EQ(s.sum(2, 7, 2), 0);
}
