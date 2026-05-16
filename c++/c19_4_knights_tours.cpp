#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	vector<vector<ll>> warnsdorf(ll h, ll w, ll y = 0, ll x = 0) {
		static const vector<pair<ll, ll>> dv = { {2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1} };
		vector<vector<ll>> board(h, vector<ll>(w));
		auto npos = [&](ll y, ll x) {
			vector<pair<ll, ll>> ret;
			for (auto [dy, dx] : dv) {
				ll ny = y + dy, nx = x + dx;
				if (0 <= ny && ny < h && 0 <= nx && nx < w && board[ny][nx] == 0)
					ret.emplace_back(ny, nx);
			}
			return ret;
			};
		auto dfs = [&](this auto self, ll y, ll x, ll d) {
			board[y][x] = d;
			if (d == h * w)
				return true;
			vector<tuple<ll, ll, ll>> c;
			for (auto [ny, nx] : npos(y, x))
				c.emplace_back(ssize(npos(ny, nx)), ny, nx);
			ranges::sort(c);
			for (auto [_, ny, nx] : c) {
				if (self(ny, nx, d + 1)) {
					return true;
				}
			}
			board[y][x] = 0;
			return false;
			};
		dfs(y, x, 1);
		return board;
	}

	void test(ll h, ll w, ll y = 0, ll x = 0) {
		auto ret = warnsdorf(h, w, y, x);
		vector<pair<ll, ll>> route(h * w, { -2, -2 });
		for (ll i = 0; i < h; ++i) {
			for (ll j = 0; j < w; ++j) {
				EXPECT_GE(ret[i][j], 1);
				EXPECT_LE(ret[i][j], h * w);
				route[ret[i][j] - 1] = { i, j };
			}
		}
		EXPECT_EQ(route[0], make_pair(y, x));
		for (const auto& [p, n] : route | views::pairwise) {
			ll i = abs(p.first - n.first), j = abs(p.second - n.second);
			EXPECT_TRUE(i == 1 && j == 2 || i == 2 && j == 1);
		}
	}
}
TEST(C194KnightsTours, warnsdorf) {
	test(1, 1);
	test(4, 3);
	test(5, 5);
}
