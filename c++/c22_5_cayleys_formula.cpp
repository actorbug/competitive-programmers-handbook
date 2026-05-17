#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "util.h"

namespace {
	vector<vector<ll>> prufre2tree(const vector<ll>& a) {
		ll n = ssize(a) + 2;
		vector<vector<ll>> adj(n);
		vector<ll> degree(n, 1);
		for (ll i : a)
			++degree[i];
		priority_queue<ll, vector<ll>, greater<>> q;
		for (ll i = 0; i < n; ++i) {
			if (degree[i] == 1) {
				q.push(i);
			}
		}
		for (ll i : a) {
			ll j = q.top(); q.pop();
			adj[i].push_back(j);
			adj[j].push_back(i);
			if (--degree[i] == 1)
				q.push(i);
			if (--degree[j] == 1)
				q.push(j);
		}
		ll i = q.top(); q.pop();
		ll j = q.top(); q.pop();
		adj[i].push_back(j);
		adj[j].push_back(i);
		return adj;
	}

	vector<vector<vector<ll>>> cayley(ll n) {
		vector<ll> vec(n - 2);
		vector<vector<vector<ll>>> ret;
		do {
			ret.push_back(prufre2tree(vec));
		} while (next_product(vec, n));
		return ret;
	}

	vector<multiset<ll>> convert(const vector<vector<ll>>& adj) {
		return adj | views::transform(ranges::to<multiset>()) | ranges::to<vector>();
	}
}

TEST(C225CayleysFormula, prufre2tree) {
	EXPECT_EQ(convert(prufre2tree({ 3,3,1 })), (vector<multiset<ll>>{{3},{3,4},{3},{0,1,2},{1}}));
}

TEST(C225CayleysFormula, cayley) {
	EXPECT_EQ(cayley(4) | views::transform([](const auto& c) { return c | views::transform(ranges::to<multiset>()) | ranges::to<vector>(); }) | ranges::to<multiset>(), (multiset<vector<multiset<ll>>>{
		{{1,2,3},{0},{0},{0}},
		{{1},{0,2,3},{1},{1}},
		{{2},{2},{0,1,3},{2}},
		{{3},{3},{3},{0,1,2}},
		{{1},{0,2},{1,3},{2}},
		{{1},{0,3},{3},{1,2}},
		{{2},{2,3},{0,1},{1}},
		{{2},{3},{0,3},{1,2}},
		{{3},{2,3},{1},{0,1}},
		{{3},{2},{1,3},{0,2}},
		{{1,2},{0},{0,3},{2}},
		{{1,3},{0},{3},{0,2}},
		{{2,3},{2},{0,1},{0}},
		{{2,3},{3},{0},{0,1}},
		{{1,2},{0,3},{0},{1}},
		{{1,3},{0,2},{1},{0}}
	}));
}
