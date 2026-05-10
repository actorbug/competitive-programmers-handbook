#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "c09_2_binary_indexed_tree.h"
#include "c09_4_additional_techniques.h"

namespace {
	vector<ll> traversal(const vector<vector<ll>>& adj, ll x) {
		vector<ll> ret;
		auto dfs = [&](this auto self, ll s, ll e) -> void {
			ret.push_back(s);
			for (ll u : adj[s]) {
				if (u != e) {
					self(u, s);
				}
			}
			};
		dfs(x, -1);
		return ret;
	}

	struct SubtreeQueries {
		SubtreeQueries(const vector<vector<ll>>& adj, const vector<ll>& val, ll x)
			: pos(adj.size()), size(adj.size()), value(adj.size()) {
			ll cur = 0;
			auto& pos_ = pos;
			auto& size_ = size;
			auto dfs = [&](this auto self, ll s, ll e) -> ll {
				pos_[s] = cur++;
				ll sz = 1;
				for (ll u : adj[s]) {
					if (u != e) {
						sz += self(u, s);
					}
				}
				return size_[pos_[s]] = sz;
				};
			dfs(x, -1);
			for (ll i = 0; i < ssize(adj); ++i)
				value.add(pos[i] + 1, val[i]);
		}
		ll sum(ll k) const {
			ll p = pos[k];
			return value.sum(p + size[p]) - value.sum(p);
		}
		void set(ll k, ll x) {
			value.set(pos[k] + 1, x);
		}
	private:
		vector<ll> pos, size;
		BIT value;
	};

	struct PathQueries {
		PathQueries(const vector<vector<ll>>& adj, const vector<ll>& val, ll x)
			: pos(adj.size()), size(adj.size()), value(adj.size()) {
			ll cur = 0;
			auto& pos_ = pos;
			auto& size_ = size;
			auto& value_ = value;
			auto dfs = [&](this auto self, ll s, ll e, ll v) -> ll {
				pos_[s] = cur;
				v += val[s];
				value_.add(cur, cur, v);
				++cur;
				ll sz = 1;
				for (ll u : adj[s]) {
					if (u != e) {
						sz += self(u, s, v);
					}
				}
				return size_[pos_[s]] = sz;
				};
			dfs(x, -1, 0);
		}
		ll sum(ll k) const {
			return value[pos[k]];
		}
		void add(ll k, ll x) {
			ll p = pos[k];
			value.add(p, p + size[p], x);
		}
	private:
		vector<ll> pos, size;
		RangeUpdates value;
	};
}

TEST(C182SubtreesAndPaths, traversal) {
	EXPECT_EQ(traversal({ {} }, 0), vector<ll>{0});
	EXPECT_EQ(traversal({ {1,2,3,4},{0,5},{0},{0,6,7,8},{0},{1},{3},{3},{3} }, 0), (vector<ll>{0,1,5,2,3,6,7,8,4}));
}

TEST(C182SubtreesAndPaths, SubtreeQueries) {
	EXPECT_EQ(SubtreeQueries({ {} }, { 3 }, 0).sum(0), 3);
	SubtreeQueries sq({ {1,2,3,4},{0,5},{0},{0,6,7,8},{0},{1},{3},{3},{3} }, { 2,3,5,3,1,4,4,3,1 }, 0);
	EXPECT_EQ(sq.sum(3), 11);
	sq.set(6, 2);
	EXPECT_EQ(sq.sum(3), 9);
}

TEST(C182SubtreesAndPaths, PathQueries) {
	EXPECT_EQ(PathQueries({ {} }, { 3 }, 0).sum(0), 3);
	PathQueries pq({ {1,2,3,4},{0,5},{0},{0,6,7,8},{0},{1},{3},{3},{3} }, { 4,5,3,5,2,3,5,3,1 }, 0);
	EXPECT_EQ(pq.sum(6), 14);
	pq.add(3, 1);
	EXPECT_EQ(pq.sum(6), 15);
}
