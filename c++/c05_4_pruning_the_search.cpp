#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	const vector<pair<ll, ll>> dv = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

	bool can_move(ll y, ll x, ll n, const vector<vector<bool>>& visited) {
		return 0 <= y && y < n && 0 <= x && x < n && !visited[y][x];
	}

	ll basic(ll n) {
		ll count = 0;
		vector<vector<bool>> visited(n, vector<bool>(n));
		auto rec = [&](this auto self, ll k, ll y, ll x) {
			if (!can_move(y, x, n, visited))
				return;
			if (k >= n * n && y == n - 1 && x == n - 1)
				++count;
			visited[y][x] = true;
			for (auto [dy, dx] : dv)
				self(k + 1, y + dy, x + dx);
			visited[y][x] = false;
			};
		rec(1, 0, 0);
		return count;
	}

	ll optimize1(ll n) {
		if (n < 2)
			return max(n, 0ll);
		ll count = 0;
		vector<vector<bool>> visited(n, vector<bool>(n));
		visited[0][0] = true;
		auto rec = [&](this auto self, ll k, ll y, ll x) {
			if (!can_move(y, x, n, visited))
				return;
			if (k >= n * n && y == n - 1 && x == n - 1)
				++count;
			visited[y][x] = true;
			for (auto [dy, dx] : dv)
				self(k + 1, y + dy, x + dx);
			visited[y][x] = false;
			};
		rec(2, 1, 0);
		return count * 2;
	}

	ll optimize2(ll n) {
		if (n < 2)
			return max(n, 0ll);
		ll count = 0;
		vector<vector<bool>> visited(n, vector<bool>(n));
		visited[0][0] = true;
		auto rec = [&](this auto self, ll k, ll y, ll x) {
			if (!can_move(y, x, n, visited))
				return;
			if (y == n - 1 && x == n - 1) {
				if (k >= n * n)
					++count;
				return;
			}
			visited[y][x] = true;
			for (auto [dy, dx] : dv)
				self(k + 1, y + dy, x + dx);
			visited[y][x] = false;
			};
		rec(2, 1, 0);
		return count * 2;
	}

	ll optimize3(ll n) {
		if (n < 2)
			return max(n, 0ll);
		ll count = 0;
		vector<vector<bool>> visited(n, vector<bool>(n));
		visited[0][0] = true;
		auto rec = [&](this auto self, ll k, ll y, ll x) {
			if (!can_move(y, x, n, visited))
				return;
			if (y == n - 1 && x == n - 1) {
				if (k >= n * n)
					++count;
				return;
			}
			if ((y == 0 || y == n - 1) && can_move(y, x - 1, n, visited) && can_move(y, x + 1, n, visited))
				return;
			if ((x == 0 || x == n - 1) && can_move(y - 1, x, n, visited) && can_move(y + 1, x, n, visited))
				return;
			visited[y][x] = true;
			for (auto [dy, dx] : dv)
				self(k + 1, y + dy, x + dx);
			visited[y][x] = false;
			};
		rec(2, 1, 0);
		return count * 2;
	}

	ll optimize4(ll n) {
		if (n < 2)
			return max(n, 0ll);
		ll count = 0;
		vector<vector<bool>> visited(n, vector<bool>(n));
		visited[0][0] = true;
		auto rec = [&](this auto self, ll k, ll y, ll x) {
			if (!can_move(y, x, n, visited))
				return;
			if (y == n - 1 && x == n - 1) {
				if (k >= n * n)
					++count;
				return;
			}
			if (can_move(y + 1, x, n, visited) == can_move(y - 1, x, n, visited) && can_move(y, x + 1, n, visited) == can_move(y, x - 1, n, visited))
				return;
			visited[y][x] = true;
			for (auto [dy, dx] : dv)
				self(k + 1, y + dy, x + dx);
			visited[y][x] = false;
			};
		rec(2, 1, 0);
		return count * 2;
	}

	void test(auto f) {
		EXPECT_EQ(f(1), 1);
		EXPECT_EQ(f(5), 104);
	}
}

TEST(C054PruningTheSearch, basic) {
	test(basic);
}

TEST(C054PruningTheSearch, optimize1) {
	test(optimize1);
}

TEST(C054PruningTheSearch, optimize2) {
	test(optimize2);
}

TEST(C054PruningTheSearch, optimize3) {
	test(optimize3);
}

TEST(C054PruningTheSearch, optimize4) {
	test(optimize4);
}
