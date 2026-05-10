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
}
TEST(C194KnightsTours, warnsdorf) {
	EXPECT_EQ(warnsdorf(1, 1), vector<vector<ll>>{{1}});
	EXPECT_EQ(warnsdorf(4, 3), (vector<vector<ll>>{{1,8,3},{4,11,6},{7,2,9},{10,5,12}}));
	EXPECT_EQ(warnsdorf(5, 5), (vector<vector<ll>>{{1,20,9,14,3},{10,15,2,19,24},{21,8,23,4,13},{16,11,6,25,18},{7,22,17,12,5}}));
}
